#include <Arduino.h>
#include <WiFi.h>
#include "net/WifiManager.h"
#include "net/WifiStore.h"
#include <ESPmDNS.h>
#include "lwip/dns.h"

void WifiManager::begin(WifiStore* store) {
    startedMs = millis();
    this->store = store;
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(false);
    WiFi.setSleep(false);
    WiFi.setMinSecurity(WIFI_AUTH_WPA2_PSK);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
        log_w("disconnect reason=%d", info.wifi_sta_disconnected.reason);
    }, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    connect();
}

void WifiManager::connect() {
    WiFi.begin(store->ssid.c_str(), store->pass.c_str());
    lastAttemptMs = millis();
}

WifiManager::Status WifiManager::update() {
    bool isConnected = (WiFi.status() == WL_CONNECTED);

    if (isConnected && !wasConnected) {
        everConnected = true;
        log_i("connected, IP: %s", WiFi.localIP().toString().c_str());
        log_i("gw=%s dns=%s", WiFi.gatewayIP().toString().c_str(), WiFi.dnsIP().toString().c_str());
        if (!mdnsStarted && MDNS.begin("smartstop")) {
            MDNS.addService("http", "tcp", 80);
            mdnsStarted = true;
            log_i("mDNS: http://smartstop.local");
        }
    }
    if (!isConnected && wasConnected) {
        log_w("connection lost");
        lastAttemptMs = millis();
    }

    if (!isConnected && millis() - lastAttemptMs >= RETRY_INTERVAL_MS) {
        log_d("retry: full re-begin");
        WiFi.disconnect(true, true);
        WiFi.mode(WIFI_OFF);
        WiFi.mode(WIFI_STA);
        connect();
        connect();
    }

    wasConnected = isConnected;

    if (isConnected) return Status::Connected;
    if (!everConnected && millis() - startedMs >= GIVE_UP_MS) return Status::GaveUp;
    return Status::Connecting;
}

void WifiManager::end() {
    if (mdnsStarted) {
        MDNS.end();
        mdnsStarted = false;
    }
    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);
    wasConnected = false;
}
