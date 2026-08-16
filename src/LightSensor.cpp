#include <Arduino.h>
#include "LightSensor.h"

#include <cmath>

static float rawToBrightness(int rawReading, int darkThreshold, int brightThreshold) {
    if (rawReading <= darkThreshold) return 0.0f;
    if (rawReading >= brightThreshold) return 1.0f;
    return(float)(rawReading - darkThreshold) / (brightThreshold - darkThreshold);
}

void LightSensor::init(int pin) {
    sensorPin = pin;
    pinMode(sensorPin, INPUT);
    analogSetPinAttenuation(sensorPin, ADC_6db);
    smoothedRaw = analogRead(sensorPin);
    lastReadMs = millis();
}

bool LightSensor::update() {
    if (millis() - lastReadMs < READ_INTERVAL_MS) return false;
    lastReadMs = millis();

    int rawReading = analogRead(sensorPin);
    smoothedRaw += SMOOTHING * (rawReading - smoothedRaw);  // moving average, softens flicker

    float brightnessFactor = rawToBrightness((int)smoothedRaw, DARK_THRESHOLD_RAW, BRIGHT_THRESHOLD_RAW);
    if (brightnessFactor < MIN_ON_FACTOR) brightnessFactor = 0.0f;  // too dim, turn off the backlight
    log_d("light raw=%d smooth=%.0f factor=%.2f", rawReading,smoothedRaw, brightnessFactor);

    if (fabsf(brightnessFactor - currentBrightness) < MIN_BRIGHTNESS_STEP) return false;
    currentBrightness = brightnessFactor;
    return true;
}

float LightSensor::brightness() const {
    return currentBrightness;
}