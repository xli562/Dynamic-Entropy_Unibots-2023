#ifndef _UNIT_SONIC_H_
#define _UNIT_SONIC_H_

#include "Arduino.h"
#include "Wire.h"

class SONIC_I2C {
    private:
        uint8_t _addr;
        TwoWire* _wire;
        uint8_t _speed;

    public:
        void begin(TwoWire* wire = &Wire, uint8_t addr = 0x57,
                    uint32_t speed = 200000L);
        float reading();
};


#endif