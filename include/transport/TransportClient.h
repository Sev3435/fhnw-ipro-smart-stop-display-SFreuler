#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H

#include <Arduino.h>
#include <cstdint>
#include "Config.h"
#include "hardware/Display.h"
#include "transport/DepartureParser.h"
#include "transport/TimeService.h"
#include "transport/TransportApi.h"

class TransportClient {
    public:
        void begin(Config* cfg, Display* disp, TimeService* time);
        void update();
    private:
        Config* config = nullptr;
        Display* display = nullptr;
        TimeService* timeService = nullptr;
        TransportApi api;
        DepartureParser parser;
        uint32_t lastFetchMs = 0;
        bool wasConnected = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTCLIENT_H
