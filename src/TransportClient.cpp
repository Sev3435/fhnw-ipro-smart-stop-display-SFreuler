#include "TransportClient.h"
#include <cstdint>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "TimeService.h"

void TransportClient::update() {
    if (WiFi.status() != WL_CONNECTED) return;
    uint32_t millisSinceBoot = millis();
    if (lastFetchMs != 0 && millisSinceBoot - lastFetchMs < config->refreshSec * 1000UL) return;
    lastFetchMs = millisSinceBoot;

    String body;
    if (!fetch(body)) return;
    Departure departure = parse(body);
    if (!departure.valid) return;

    if (!timeService.isSynced()) {
        log_w("Time not synced yet");
        return;
    }

    int minutes = timeService.minutesUntilDeparture(departure.departsAt);
    log_i("line %s to %s in %d min", departure.line.c_str(), departure.destination.c_str(), minutes);
}

bool TransportClient::fetch(String& body) {
    String url = "http://transport.opendata.ch/v1/stationboard?id=" + String(config->stopId) +
                 "&limit=" + String(config->limit) +
                 "&fields[]=stationboard/stop/departure"
                 "&fields[]=stationboard/number"
                 "&fields[]=stationboard/to"
                 "&fields[]=stationboard/passList/station/name";
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode != 200) {
        log_w("http %d", httpCode);
        http.end();
        return false;
    }
    body = http.getString();
    log_i("http 200, body %d bytes", body.length());
    http.end();
    return true;
}

static time_t parseIsoToDepartureTime(const char* departureIso) {
    struct tm timeField = {};
    strptime(departureIso, "%Y-%m-%dT%H:%M:%S", &timeField);
    time_t departureTime = mktime(&timeField);

    const char* offset = strchr(departureIso, 'T') + 9;
    char sign = offset[0];
    int hours = 0;
    int minutes = 0;
    sscanf(offset + 1, "%2d%2d", &hours, &minutes);
    int shift = hours * 3600 + minutes * 60;

    if (sign == '+') departureTime -= shift;
    else departureTime += shift;

    return departureTime;
}

Departure TransportClient::parse(const String& body) {
    Departure departure;

    JsonDocument filter;
    filter["stationboard"][0]["number"] = true;
    filter["stationboard"][0]["to"] = true;
    filter["stationboard"][0]["stop"]["departure"] = true;
    filter["stationboard"][0]["passList"][0]["station"]["name"] = true;

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, body, DeserializationOption::Filter(filter));
    if (err) { log_w("json: %s", err.c_str()); return departure; }

    for (JsonObject obj : doc["stationboard"].as<JsonArray>()) {
        const char* number = obj["number"];
        if (!number || config->line != number) {
            log_d("skip: line '%s' != '%s'", number ? number : "(null)", config->line.c_str());
            continue;
        }

        const char* next = obj["passList"][1]["station"]["name"];
        if (!next || config->nextStop != next) {
            log_d("skip: nextStop '%s' != '%s'", next ? next : "(null)", config->nextStop.c_str());
            continue;
        }

        const char* departureIso = obj["stop"]["departure"];
        if (!departureIso) {
            log_d("skip: no departure time");
            continue;
        }

        departure.departsAt = parseIsoToDepartureTime(departureIso);
        departure.line = number;
        departure.destination =(const char*)obj["to"];
        departure.valid = true;

        if (departure.departsAt - time(nullptr) < 60) continue;
        
        return departure;
    }

    log_w("no departure matched line %s / next stop %s", config->line.c_str(), config->nextStop.c_str());
    return departure;
}

