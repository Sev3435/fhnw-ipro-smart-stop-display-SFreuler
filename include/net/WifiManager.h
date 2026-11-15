#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H

#include <cstdint>

class WifiStore;

class WifiManager {
public:
    enum class Status { Connecting, Connected, GaveUp };

    void begin(WifiStore* store);
    void end();
    Status update();
private:
    void connect();

    static const uint32_t RETRY_INTERVAL_MS = 5000;
    static const uint32_t GIVE_UP_MS = 30000;

    WifiStore* store = nullptr;
    uint32_t lastAttemptMs = 0;
    uint32_t startedMs = 0;
    bool wasConnected = false;
    bool everConnected = false;
    bool mdnsStarted = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H