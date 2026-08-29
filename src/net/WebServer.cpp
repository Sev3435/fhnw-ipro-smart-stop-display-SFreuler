#include "net/WebServer.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <AsyncJson.h>
#include "Config.h"

static AsyncWebServer server(80);

void WebServer::begin(Config* config) {
    if (!LittleFS.begin()) {
        log_e("LittleFS mount failed");
        return;
    }

    server.on("/config", HTTP_GET, [config](AsyncWebServerRequest* request) {
        JsonDocument doc;
        doc["stopId"] = config->stopId;
        doc["line"] = config->line;
        doc["category"] = config->category;
        doc["nextStop"] = config->nextStop;
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });
    auto* saveHandler = new AsyncCallbackJsonWebHandler("/save",[config](AsyncWebServerRequest* request, JsonVariant& json) {
        JsonObject obj = json.as<JsonObject>();
        if (!obj["stopId"].is<uint32_t>() || !obj["line"].is<const char *>() || !obj["nextStop"].is<const char*>()) {
            request->send(400, "application/json", R"({"error":"missing fields"})");
            return;
        }
        config->stopId = obj["stopId"];
        config->line = (const char*)obj["line"];
        config->nextStop = (const char*)obj["nextStop"];
        config->category = obj["category"].is<const char*>() ? (const char*)obj["category"] : "";
        config->save();
        log_i("config saved: stop=%u line=%s nextStop=%s", config->stopId, config->line.c_str(), config->nextStop.c_str());
        request->send(200, "application/json", R"({"ok":true})");
        });

    saveHandler->setMethod(HTTP_POST);
    server.addHandler(saveHandler);

    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.begin();
    log_i("web server started");
}