#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTAPI_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTAPI_H

#include <Arduino.h>
#include "Config.h"

class TransportApi {
    public:
        void begin(Config* cfg) { config = cfg; }
        bool fetch(String& body) const;
    private:
        Config* config = nullptr;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TRANSPORTAPI_H
