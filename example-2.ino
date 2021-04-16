// File: example-2.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"

#define LED_PIN (p25) // use on-board LED (GP25 pin)

mbed::DigitalOut led(LED_PIN);

void setup() {
   SerialUSB.begin( 115200 );
}

String sbuf;

void loop() {
   led = !led; // toggle and update the LED output
   sbuf = "LED state: ";
   sbuf += led.read();
   SerialUSB.println( sbuf.c_str() ); // send a string 
   rtos::ThisThread::sleep_for( std::chrono::milliseconds(100) );
}
