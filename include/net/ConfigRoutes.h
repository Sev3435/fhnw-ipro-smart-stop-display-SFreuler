#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIGROUTES_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIGROUTES_H

class AsyncWebServer;
class Config;

namespace ConfigRoutes {
    void attach(AsyncWebServer& server, Config* config);
}

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIGROUTES_H
