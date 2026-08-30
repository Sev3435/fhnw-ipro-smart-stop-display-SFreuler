#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISTORE_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISTORE_H

#include <Arduino.h>
#include <Preferences.h>

class WifiStore {
public:
    String ssid;
    String pass;

    void load();
    void save();
    void clear();
    bool hasCredentials() const { return ssid.length() > 0; }
private:
    Preferences preferences;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_WIFISTORE_H
