#include <Wire.h>
#include "hardware/Display.h"

void Display::init() {
    lcd.begin(16, 2);

    lcd.setRGB(COLOR_R, COLOR_G, COLOR_B);

    lcd.print("Next Departure:");
    showMessage("searching...");
}

void Display::showMessage(const String& text) {
    if (text == lastShown) return;
    lastShown = text;
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(text);
}

void Display::showDeparture(const String& line, int minutes) {
    char buffer[17];
    if (minutes < 60) {
        snprintf(buffer, sizeof(buffer), "Line %-4s%3d min", line.c_str(), minutes);
    } else {
        snprintf(buffer, sizeof(buffer), "Line %-4s%dh %02dm",
                 line.c_str(), minutes / 60, minutes % 60);
    }
    showMessage(buffer);
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
