#include "transport/DepartureParser.h"
#include "transport/TimeService.h"
#include <ArduinoJson.h>

Departure DepartureParser::parse(const String& body) const {
    Departure departure;

    JsonDocument filter;
    filter["stationboard"][0]["number"] = true;
    filter["stationboard"][0]["category"] = true;
    filter["stationboard"][0]["to"] = true;
    filter["stationboard"][0]["stop"]["departure"] = true;
    filter["stationboard"][0]["passList"][0]["station"]["name"] = true;

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, body, DeserializationOption::Filter(filter));
    if (err) { log_w("json: %s", err.c_str()); return departure; }

    for (JsonObject obj : doc["stationboard"].as<JsonArray>()) {
        const char* number = obj["number"];
        if (!number || config->line != number) {
            log_v("skip: line '%s' != '%s'", number ? number : "(null)", config->line.c_str());
            continue;
        }

        const char* category = obj["category"];
        if (!config->category.isEmpty() && config->category != (category ? category : "")) {
            log_v("skip: category '%s' != '%s'", category ? category : "(null)", config->category.c_str());
            continue;
        }

        const char* next = obj["passList"][1]["station"]["name"]; // [0] is current stop defined in config, [1] is the next
        if (!next || config->nextStop != next) {
            log_d("skip: nextStop '%s' != '%s'", next ? next : "(null)", config->nextStop.c_str());
            continue;
        }

        const char* departureIso = obj["stop"]["departure"];
        if (!departureIso) {
            log_d("skip: no departure time");
            continue;
        }

        time_t departsAt = TimeService::parseIso8601(departureIso);
        if (departsAt - time(nullptr) < 60) continue; // leaving too soon, grab the next one

        departure.departsAt = departsAt;
        departure.line = number;
        departure.category = category ? category : "";
        departure.destination = (const char*)obj["to"];
        departure.valid = true;
        return departure;
    }

    log_w("no departure matched line %s / next stop %s", config->line.c_str(), config->nextStop.c_str());
    return departure;
}
