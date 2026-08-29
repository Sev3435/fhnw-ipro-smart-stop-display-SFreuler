#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H

#include <cstdint>

class WifiManager {
    public:
        void init();
        void update();
    private:
        static const uint32_t RETRY_INTERVAL_MS = 5000;
        uint32_t lastAttemptMs = 0;
        bool wasConnected = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFIMANAGER_H
