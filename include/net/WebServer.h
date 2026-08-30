#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WEBSERVER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WEBSERVER_H

#include <ESPAsyncWebServer.h>

class WebServer {
public:
    bool mount();
    void start();
    AsyncWebServer& http() { return server; }
private:
    AsyncWebServer server{80};
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WEBSERVER_H
