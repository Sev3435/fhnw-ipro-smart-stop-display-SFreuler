#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIROUTES_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIROUTES_H

class AsyncWebServer;
class WifiStore;

namespace WifiRoutes {
    void attach(AsyncWebServer& server, WifiStore* store);
    bool restartPending();
}

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIROUTES_H