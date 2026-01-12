/*
    Hello World.ino
    2013 Copyright (c) Seeed Technology Inc.  All right reserved.

    Author:Loovee
    2013-9-18

    Grove - Serial LCD RGB Backlight demo.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 64;
const int colorG = 224;
const int colorB = 208;

void setup() {
    lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);
    
    lcd.print("Next Departure:");

    delay(1000);
}

void loop() {
    
    lcd.setCursor(0, 1);
   

    delay(100);
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/