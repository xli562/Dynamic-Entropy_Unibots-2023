#include "Wire.h"

#define PCA_ADDR 0x70             // Address of the multiplexer

void setup() {
  // Join the I2C bus as a master device
  Wire.begin();
  
  Serial.begin(115200);
  // Waits for serial communication to establish
  while (!Serial);
  delay(10);
  Serial.println("\nPCAScanner ready!");
  
  for (uint8_t i=0; i<8; i++) {
    pca_select(i);
    Serial.print("PCA Port #"); Serial.println(i);

    for (uint8_t addr = 0; addr<=127; addr++) {
      if (addr == PCA_ADDR) continue;

      Wire.beginTransmission(addr);
      if (!Wire.endTransmission()) {
        Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
      }
    }
  }
  Serial.println("\ndone");
}

void loop() {
}

void pca_select(uint8_t i) {
  if (i <= 7) {
    Wire.beginTransmission(PCA_ADDR);
    // The number one shifted left i times, i.e. 1*2^i. Shifting left is faster than performing the n^i operation.
    Wire.write(1 << i);           
    Wire.endTransmission();
  }
}