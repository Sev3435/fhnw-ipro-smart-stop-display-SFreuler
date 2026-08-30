#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H

#include <cstdint>

class WifiStore;

class WifiManager {
public:
    void begin(WifiStore* store);
    void update();
private:
    void connect();

    static const uint32_t RETRY_INTERVAL_MS = 5000;
    WifiStore* store = nullptr;
    uint32_t lastAttemptMs = 0;
    bool wasConnected = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H