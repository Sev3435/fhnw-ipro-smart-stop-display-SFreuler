#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H

#include <ctime>

class TimeService {
    public:
        void update();                                    // starts NTP once the radio is up
        bool isSynced() const;
        int  minutesUntilDeparture(time_t departure) const;
        static time_t parseIso8601(const char* iso);      // "2026-09-06T14:23:00+0200" -> UTC
    private:
        bool ntpStarted = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_TIMESERVICE_H
