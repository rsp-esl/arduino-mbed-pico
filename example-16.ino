// File: example-16.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

// LM75a digital temperature sensor (I2C)
// vcc: 2.8 V to 5.5 V
// 11-bit t 2's complement data (resolution: 0.125 °C)
// accuracy:
//  - ±2 °C from −25 °C to +100 °C
//  - ±3 °C from −55 °C to +125 °C
// Datasheet: https://www.nxp.com/docs/en/data-sheet/LM75A.pdf

#include "mbed.h"
#include "I2C.h"
using namespace mbed;

// The Arduino-mbed-Pico board uses a fixed i2c-1 assignment for SDA and SCL.
// GP6=SDA and GP7=SCL.

#define I2C_ADDR  (0x48)  // 7-bit addresss
const int addr8bit = (I2C_ADDR << 1);

I2C i2c_bus( p6, p7 ); // sda and scl pins
uint8_t buf[2]; // data buffer for I2C read/write operations

boolean lm75a_init( I2C &i2c ) {
    buf[0] = 0x01; // configuration register
    buf[1] = 0x00; // value (default 0)
    int result = i2c.write( addr8bit, (const char*)buf, 2 );
    return (result==0);
}

boolean lm75a_read( I2C &i2c, float *value ) {
    *value = 0.0;
    buf[0] = 0x00; 
    if ( i2c.write( addr8bit, (const char*) buf, 1 ) != 0 ) {
        return false;
    }
    if ( i2c.read( addr8bit, (char*)buf, 2 ) != 0 ) {
        return false;
    }
    uint8_t h = buf[0];   // high byte
    uint8_t l = buf[1];   // low byte
    uint16_t temp = (h << 8) | l ;
    *value = ((int16_t)temp)/256.0;
    return true;
}

void setup() {
    SerialUSB.begin( 115200 ); 
    while(!SerialUSB){}
    SerialUSB.println("LM75a I2C Temperature Sensor...");
    i2c_bus.frequency(100000);
    if ( !lm75a_init(i2c_bus) ) {
       SerialUSB.println("LM75a initialization error!");
       while(1) {}
    }
}

char sbuf[64];
float temp;

void loop() {
    if ( lm75a_read( i2c_bus, &temp) ) {
       sprintf( sbuf, "Temperature: %.2f deg.C", temp );
    } else {
       sprintf( sbuf, "Temperature: --.-- deg.C" );
    }
    SerialUSB.println( sbuf );
    delay(500);
}
