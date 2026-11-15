#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIG_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIG_H

#include <Arduino.h>
#include <Preferences.h>
#include <cstdint>

class Config {
    public:
        uint32_t stopId     = 8576646;
        String line = "10";
        String category = "";
        String nextStop = "Bern, Bundesplatz";
        uint8_t  limit      = 30;
        uint32_t refreshSec = 30;
        uint8_t  r = 64, g = 224, b = 208;

        void load();
        void save();
    private:
        Preferences preferences;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_CONFIG_H
