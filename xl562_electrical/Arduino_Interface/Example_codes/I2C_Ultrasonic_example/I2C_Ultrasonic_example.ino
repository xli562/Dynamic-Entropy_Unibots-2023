#include <Unit_Sonic.h>

#define PCA_ADDR 0x70

SONIC_I2C sonic;

void pcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(PCA_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission(true);   //Sends the data, then releases the bus because of the true argument
}

// standard Arduino setup()
void setup()
{
    while (!Serial);
    delay(1000);

    Wire.begin();

    sonic.begin();
    
    Serial.begin(115200);
    Serial.println("\nMultiSensor PCA9548");
      
}

void loop() 
{
  pcaselect(0);
  Serial.println(sonic.reading());
}
