#include <Wire.h>
#include "Display.h"

void Display::init() {
    lcd.begin(16, 2);

    lcd.setRGB(COLOR_R, COLOR_G, COLOR_B);
    
    lcd.print("Next Departure:");
    showDeparture("searching...");
}

void Display::showDeparture(const String& next) {
    if (next == lastShown) return;
    lastShown = next;
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(next);
}

// TODO: extract into new class
void Display::setBrightness(float factor) {
    if (factor < 0.0f) factor = 0.0f;
    else if (factor > 1.0f) factor = 1.0f;

    if (factor == 0.0f) {
        lcd.setRGB(0, 0, 0);
        lcd.noDisplay();
    } else {
        lcd.display();
        float perceptual = MIN_ON_BRIGHTNESS + (1.0f - MIN_ON_BRIGHTNESS) * (factor * factor);
        lcd.setRGB(COLOR_R * perceptual, COLOR_G * perceptual, COLOR_B * perceptual);
    }
}
