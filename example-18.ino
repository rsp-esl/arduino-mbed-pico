// File: example-18.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
#include "I2C.h"
using namespace mbed;

// The Arduino-mbed-Pico board uses a fixed i2c-1 assignment for SDA and SCL.
// GP6=SDA and GP7=SCL.

#define I2C_ADDR  (0x23)
const int addr8bit = (I2C_ADDR << 1);

I2C i2c_bus( p6, p7 ); // sda and scl pins
uint8_t buf[2]; // data buffer for I2C read/write operations

boolean bh1750_read( I2C &i2c, uint32_t *level ) {
    *level = 0;
    i2c_bus.lock();
    if ( i2c.read( addr8bit, (char*)buf, 2 ) != 0 ) {
        i2c_bus.unlock();
        return false;
    }
    i2c_bus.unlock();
    uint8_t h = buf[0];   // high byte
    uint8_t l = buf[1];   // low byte
    uint32_t value = (h << 8) | l ;
    *level = 5*value/6;
    return true;
}

boolean bh1750_init( I2C &i2c ) {
    uint8_t mode = 0x10;
    buf[0] = 0x10;
    i2c_bus.lock();
    int result = i2c.write( addr8bit, (const char*) buf, 1 );
    i2c_bus.unlock();
   return (result == 0);
}

void setup() {
    SerialUSB.begin( 115200 ); 
    while(!SerialUSB){}
    SerialUSB.println("BH1750 I2C Light Sensor...");
    i2c_bus.frequency(100000);
    if ( !bh1750_init(i2c_bus) ) {
       SerialUSB.println("BH1750 initialization error!");
       while(1) {}
    }
}

char sbuf[64];
uint32_t level;

void loop() {
    if ( bh1750_read(i2c_bus, &level) ) {
       sprintf( sbuf, "Light level: %5lu Lx", level );
    } else {
       sprintf( sbuf, "Light level: ----- lx" );
    }
    SerialUSB.println( sbuf );
    delay(500);
}
