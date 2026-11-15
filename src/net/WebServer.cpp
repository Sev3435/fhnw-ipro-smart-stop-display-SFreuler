#include "net/WebServer.h"
#include <Arduino.h>
#include <LittleFS.h>

bool WebServer::mount() {
    if (!LittleFS.begin()) {
        log_e("LittleFS mount failed");
        return false;
    }
    return true;
}

void WebServer::start() {
    // registered last: the catch-all must not shadow the route modules
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.begin();
    log_i("web server started");
}