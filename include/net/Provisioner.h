#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_PROVISIONER_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_PROVISIONER_H

#include <Arduino.h>

class Provisioner {
public:
    void begin();
    void end();
    String apIp() const;
private:
    bool running = false;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_PROVISIONER_H