#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H

#include <Arduino.h>
#include "Config.h"
#include <cstdint>

struct Departure {
    String time;
    String line;
    String destination;
    bool valid = false;
};

class TransportClient {
    public:
        void begin(Config* cfg) { config = cfg; }
        void update();
    private:
        bool fetch(String& body);
        Departure parse(const String& body);
        Config* config = nullptr;
        uint32_t lastFetchMs = 0;
};


#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
