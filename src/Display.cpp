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
