#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTUREPARSER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTUREPARSER_H

#include <Arduino.h>
#include "Config.h"
#include "transport/Departure.h"

class DepartureParser {
    public:
        void begin(Config* cfg) { config = cfg; }
        Departure parse(const String& body) const;
    private:
        Config* config = nullptr;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTUREPARSER_H
