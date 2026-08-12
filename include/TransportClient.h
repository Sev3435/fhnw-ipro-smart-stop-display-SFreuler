#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H

#include <Arduino.h>
#include "Config.h"
#include <cstdint>
#include "TimeService.h"
#include "Display.h"

struct Departure {
    time_t departsAt = 0;
    String line;
    String destination;
    bool valid = false;
};

class TransportClient {
    public:
        void begin(Config* cfg, Display* disp) { config = cfg; display = disp; }
        void update();
    private:
        bool fetch(String& body);
        Departure parse(const String& body);
        Config* config = nullptr;
        Display* display = nullptr;
        uint32_t lastFetchMs = 0;
        TimeService timeService;
};


#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
