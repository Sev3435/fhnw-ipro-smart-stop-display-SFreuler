#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H

#include <ctime>

class TimeService {
public:
    bool isSynced();
    int  minutesUntilDeparture(time_t departure);
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H
