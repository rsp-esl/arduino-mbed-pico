// File: example-17.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "Wire.h"

// The Arduino-mbed-Pico board uses a fixed i2c-1 assignment for SDA and SCL.
// GP6=SDA and GP7=SCL.

#define I2C_ADDR  (0x23)  // 7-bit address

boolean bh1750_init() {
    uint8_t mode = 0x10;
    Wire.beginTransmission( I2C_ADDR );
    Wire.write( mode );
    int result = Wire.endTransmission();
    return (result == 0);
}

boolean bh1750_read( uint32_t *level ) {
    *level = 0;
    Wire.requestFrom( I2C_ADDR, 2 );
    if ( Wire.available() == 2 ) {
       uint8_t h = Wire.read();
       uint8_t l = Wire.read();
       uint32_t value = (h << 8) | l;
       *level = 5*value/6;
       return true; 
    }
    return false;
}

void setup() {
    SerialUSB.begin( 115200 ); 
    while(!SerialUSB){}
    SerialUSB.println("BH1750 I2C Light Sensor...");
    Wire.begin();
    Wire.setClock( 100000 );
    if ( !bh1750_init() ) {
        SerialUSB.println("BH1750 initialization error!");
        while(1) {}
    }
}

char sbuf[64];

void loop() {
    uint32_t level;
    if ( bh1750_read(&level) ) {
        sprintf( sbuf, "Light level: %5lu Lx", level );
    } else {
        sprintf( sbuf, "Light level: ----- Lx" );
    }
    SerialUSB.println( sbuf );
    delay(200);
}
