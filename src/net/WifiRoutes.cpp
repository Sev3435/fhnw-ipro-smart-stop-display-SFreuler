#include "net/WifiRoutes.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include "net/WifiStore.h"

namespace {
    bool pendingRestart = false;
}

bool WifiRoutes::restartPending() { return pendingRestart; }

void WifiRoutes::attach(AsyncWebServer& server, WifiStore* store) {
    auto* wifiHandler = new AsyncCallbackJsonWebHandler("/wifi", [store](AsyncWebServerRequest* request, JsonVariant& json) {
        JsonObject obj = json.as<JsonObject>();
        if (!obj["ssid"].is<const char*>() || !obj["pass"].is<const char*>()) {
            request->send(400, "application/json", R"({"error":"missing fields"})");
            return;
        }
        store->ssid = (const char*)obj["ssid"];
        store->pass = (const char*)obj["pass"];
        store->save();
        log_i("credentials saved for ssid=%s", store->ssid.c_str());
        request->send(200, "application/json", R"({"ok":true,"restarting":true})");
        pendingRestart = true;   // never restart inside a handler
    });
    wifiHandler->setMethod(HTTP_POST);
    server.addHandler(wifiHandler);

    server.on("/forget", HTTP_POST, [store](AsyncWebServerRequest* request) {
        store->clear();
        log_w("credentials cleared");
        request->send(200, "application/json", R"({"ok":true,"restarting":true})");
        pendingRestart = true;
    });
}