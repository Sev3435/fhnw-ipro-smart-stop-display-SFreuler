#include <Wire.h>
#include "Display.h"

void Display::init() {
    lcd.begin(16, 2);

    lcd.setRGB(COLOR_R, COLOR_G, COLOR_B);
    
    lcd.print("Next Departure:");
}

void Display::update() {

    if (millis() - lastRefreshMs < REFRESH_INTERVAL_MS) {
        return;
    }
    lastRefreshMs = millis();

    lcd.setCursor(0, 1);

}