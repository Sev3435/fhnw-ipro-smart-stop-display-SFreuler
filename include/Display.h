#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DISPLAY_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DISPLAY_H

#include <rgb_lcd.h>
#include <cstdint>

class Display {
    public:
        void init();
        void showDeparture(const String& s);
        void update();
        void setBrightness(float factor);
    private:
        rgb_lcd lcd;
        uint32_t lastRefreshMs = 0;
        static const uint32_t REFRESH_INTERVAL_MS = 1000;
        static const int COLOR_R = 64, COLOR_G = 224, COLOR_B = 208;
        String lastShown;
        static constexpr float MIN_ON_BRIGHTNESS = 0.15f;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_DISPLAY_H

