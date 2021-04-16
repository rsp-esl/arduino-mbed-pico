// File: example-15.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

// LM75a digital temperature sensor (I2C)
// vcc: 2.8 V to 5.5 V
// 11-bit t 2's complement data (resolution: 0.125 °C)
// accuracy:
//  - ±2 °C from −25 °C to +100 °C
//  - ±3 °C from −55 °C to +125 °C
// Datasheet: https://www.nxp.com/docs/en/data-sheet/LM75A.pdf

#include "Wire.h"

// The Arduino-mbed-Pico board uses a fixed i2c-1 assignment for SDA and SCL.
// GP6=SDA and GP7=SCL.

#define I2C_ADDR  (0x48)

boolean lm75a_init() {
    uint8_t mode = 0x10;
    Wire.beginTransmission( I2C_ADDR );
    Wire.write( 0x01 ); // configuration register
    Wire.write( 0x00 ); // configuration value (default 0x00)
    return ( Wire.endTransmission() == 0 );
}

boolean lm75a_read( float *value ) {
    *value = 0.0;
    Wire.beginTransmission( I2C_ADDR );
    Wire.write( 0x00 ); // temperature register
    if ( Wire.endTransmission() != 0 )  {
       return false;  // error
    } 
    Wire.requestFrom( I2C_ADDR, 2 );
    if ( Wire.available() == 2 ) {
       uint8_t h = Wire.read(); // high byte
       uint8_t l = Wire.read(); // low byte
       uint16_t temp = (h << 8) | l ;
       *value = ((int16_t)temp)/256.0;
       return true; // ok
    }
    return false; // error
}

void setup() {
    SerialUSB.begin( 115200 ); 
    while(!SerialUSB){}
    SerialUSB.println("LM75a I2C Temperature Sensor...");
    Wire.begin( );
    Wire.setClock(100000);
    if ( !lm75a_init() ) {
       SerialUSB.println("LM75a initialization error!");
       while(1) {}
    }
}

char sbuf[64];
float temp;

void loop() {
    if ( lm75a_read(&temp) ) {
       sprintf( sbuf, "Temperature: %.2f deg.C", temp );
    } else {
       sprintf( sbuf, "Temperature: --.-- deg.C" );
    }
    SerialUSB.println( sbuf );
    delay(500);
}
