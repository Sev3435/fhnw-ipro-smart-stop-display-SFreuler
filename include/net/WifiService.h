#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISERVICE_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISERVICE_H

#include "net/WifiStore.h"
#include "net/WifiManager.h"
#include "net/Provisioner.h"

class AsyncWebServer;
class Display;

class WifiService {
public:
    void attachRoutes(AsyncWebServer& server);
    void begin(Display* display);
    void update();
    bool isProvisioning() const { return mode == Mode::Provisioning; }
private:
    enum class Mode { Provisioning, Normal };
    void enterProvisioning();

    WifiStore store;
    WifiManager wifiManager;
    Provisioner provisioner;
    Display* display = nullptr;
    Mode mode = Mode::Normal;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISERVICE_H
