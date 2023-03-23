#include "Unit_Sonic.h"

/* Initialize the Sonic. */
void SONIC_I2C::begin(TwoWire* wire, uint8_t addr, uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _speed = speed;
    _wire->begin();
}

/* Get distance data. */
float SONIC_I2C::reading() {
    uint32_t data;
    _wire->beginTransmission(_addr);  // Transfer data to the sensor at 0x57.
    _wire->write(0x01);
    _wire->endTransmission();  // Stop data transmission with the sensor
    delay(80);                      // Allow time for sensor to collect data. Original value was 120.
    _wire->requestFrom(_addr, 3);   // Request 3 bytes from Ultrasonic Unit.
    data = _wire->read();
    data <<= 8;
    data |= _wire->read();
    data <<= 8;
    data |= _wire->read();
    float Distance = float(data) / 1000;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
}