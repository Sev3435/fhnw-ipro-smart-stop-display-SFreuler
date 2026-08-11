#include "TimeService.h"

bool TimeService::isSynced() {
    time_t now = time(nullptr);
    return now > 1700000000;
}

int TimeService::minutesUntilDeparture(time_t departsAt) {
    time_t now = time(nullptr);
    return (departsAt - now + 30) / 60;
}
