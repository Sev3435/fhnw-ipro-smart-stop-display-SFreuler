#include <Wire.h>
#include <rgb_lcd.h>

rgb_lcd lcd;

const int colorR = 64;
const int colorG = 224;
const int colorB = 208;

void display_init() {
    lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);
    
    lcd.print("Next Departure:");

    delay(1000);
}

void display_update() {
    
    lcd.setCursor(0, 1);
   

    delay(100);
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/