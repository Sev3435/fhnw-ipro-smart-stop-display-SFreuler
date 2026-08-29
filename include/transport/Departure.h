#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTURE_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTURE_H

#include <Arduino.h>
#include <ctime>

struct Departure {
    time_t departsAt = 0;
    String line;
    String category;
    String destination;
    bool valid = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DEPARTURE_H
