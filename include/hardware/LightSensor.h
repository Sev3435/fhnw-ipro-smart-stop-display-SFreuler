#ifndef FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_LIGHTSENSOR_H
#define FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_LIGHTSENSOR_H

#include <cstdint>

class LightSensor {
        public:
                void init(int pin);
                bool update();
                float brightness() const;
        private:
                int sensorPin = 34;
                uint32_t lastReadMs = 0;
                float currentBrightness = 1.0f;
                float smoothedRaw = 0.0f;
                static const uint32_t READ_INTERVAL_MS = 50;
                static const int DARK_THRESHOLD_RAW = 20;
                static const int BRIGHT_THRESHOLD_RAW = 3000;
                static constexpr float SMOOTHING = 0.5f;
                static constexpr float MIN_BRIGHTNESS_STEP  = 0.01f;
                static constexpr float MIN_ON_FACTOR = 0.015f;
};

#endif //FHNW_IPRO_SMART_STOP_DISPLAY_SFREULER_LIGHTSENSOR_H
