// File: example-7.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed;
using namespace rtos;

#define LED_PIN (p25) // use on-board LED (GP25 pin)

DigitalOut  led(LED_PIN);
Ticker      ticker;

void toggle( DigitalOut *pin ) { // ISR callback function
  *pin = !*pin;  // toggle LED pin
}

void setup() {
  SerialUSB.begin(115200);
  while(!SerialUSB){}
  SerialUSB.println("Start the ticker...");
  ticker.attach( callback(toggle, &led),
         std::chrono::milliseconds(100) );
  osDelay( osWaitForever ); // block the main thread
}

void loop() { }