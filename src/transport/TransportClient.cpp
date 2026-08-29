#include "transport/TransportClient.h"
#include <WiFi.h>

void TransportClient::begin(Config* cfg, Display* disp, TimeService* time) {
    config = cfg;
    display = disp;
    timeService = time;
    api.begin(cfg);
    parser.begin(cfg);
}

void TransportClient::update() {
    bool isConnected = (WiFi.status() == WL_CONNECTED);
    if (!isConnected) {
        wasConnected = false;
        return;
    }
    if (!wasConnected) {
        lastFetchMs = 0;
        wasConnected = true;
    }

    uint32_t millisSinceBoot = millis();
    if (lastFetchMs != 0 && millisSinceBoot - lastFetchMs < config->refreshSec * 1000UL) return;
    lastFetchMs = millisSinceBoot;

    String body;
    if (!api.fetch(body)) return;
    Departure departure = parser.parse(body);
    if (!departure.valid) return;

    if (!timeService->isSynced()) {
        log_w("Time not synced yet");
        return;
    }

    int minutes = timeService->minutesUntilDeparture(departure.departsAt);
    log_i("line %s to %s in %d min", departure.line.c_str(), departure.destination.c_str(), minutes);
    display->showDeparture(departure.line, minutes);
}
