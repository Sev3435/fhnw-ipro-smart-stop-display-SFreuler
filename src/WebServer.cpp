#include "WebServer.h"
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

static AsyncWebServer server(80);

void WebServer::begin() {
    if (!LittleFS.begin()) {
        log_e("LittleFS mount failed");
        return;
    }
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.begin();
    log_i("web server started");
}