#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial){
    delay(10);
  }

//testing pins sda 8, scl 9
  Wire.begin(8, 9);

  Serial.println("I2C scan:");
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
    }
  }
  Serial.println("Done.");
}

void loop() {}