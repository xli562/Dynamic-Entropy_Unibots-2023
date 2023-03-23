//raise warning -> 参考iPhone闹钟闪灯？
//若输出数据有卡顿，则修改库中的delay值。

#include <Unit_Sonic.h>

#define PCA_ADDR 0x70             // Address of the multiplexer

SONIC_I2C sensor;

void setup() {
  pca_select(7);
  sensor.begin();
  Serial.begin(9600);
}

void loop() {
  static float Distance = 0;
  Distance = sensor.reading(7);
  if ((Distance < 4000) && (Distance > 20)) {
      Serial.println(Distance);
  }
  delay(1);
}

void pca_select(uint8_t i) {
  if (i <= 7) {
    Wire.beginTransmission(PCA_ADDR);
    // The number one shifted left i times, i.e. 1*2^i. Shifting left is faster than performing the n^i operation.
    Wire.write(1 << i);           
    Wire.endTransmission(false);
  }
}
