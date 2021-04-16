// File: example-4.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace std::chrono;

#define LED_PIN (p25) // use on-board LED (GP25 pin)

mbed::DigitalOut led(LED_PIN);

uint32_t _millis() {
  auto now = rtos::Kernel::Clock::now();
  auto tp  = time_point_cast<microseconds>(now); 
  return (uint32_t) tp.time_since_epoch().count()/1000;
}

uint32_t start_time_ms, saved_time_ms = 0;

void setup() {
   SerialUSB.begin( 115200 );
   saved_time_ms = start_time_ms = _millis();
}

String sbuf;

void loop() {
  uint32_t now = _millis();
  if ( now - saved_time_ms >= 100 ) { // every 100 msec
    saved_time_ms = now;
    led = !led; // toggle and update the LED output
    sbuf = "LED state: ";
    sbuf += led.read();
    sbuf += " ";
    sbuf += (now - start_time_ms);
    sbuf += "ms";
    SerialUSB.println( sbuf.c_str() ); 
  }
}

