#include "transport/TimeService.h"
#include <Arduino.h>
#include <WiFi.h>

void TimeService::update() {
    if (ntpStarted || WiFi.status() != WL_CONNECTED) return;
    configTime(0, 0, "pool.ntp.org");
    ntpStarted = true;
    log_i("ntp sync started");
}

bool TimeService::isSynced() const {
    time_t now = time(nullptr);
    return now > 1700000000;
}

int TimeService::minutesUntilDeparture(time_t departsAt) const {
    time_t now = time(nullptr);
    return (departsAt - now + 30) / 60;
}

time_t TimeService::parseIso8601(const char* departureIso) {
    struct tm timeField = {};
    strptime(departureIso, "%Y-%m-%dT%H:%M:%S", &timeField);
    time_t departureTime = mktime(&timeField);

    const char* offset = strchr(departureIso, 'T') + 9;  // jump past T + HH:MM:SS
    char sign = offset[0];
    int hours = 0;
    int minutes = 0;
    sscanf(offset + 1, "%2d%2d", &hours, &minutes);
    int shift = hours * 3600 + minutes * 60;

    // mktime gave us UTC-as-if-local; back out the offset to get real UTC
    if (sign == '+') departureTime -= shift;
    else departureTime += shift;

    return departureTime;
}
