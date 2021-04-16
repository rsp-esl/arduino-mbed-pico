// File: example-5.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed; // for mbed::DigitalOut
using namespace rtos; // for rtos::Thread

#define LED_PIN (p25) // use on-board LED (GP25 pin)

DigitalOut  led(LED_PIN); // on-board led pin
Thread      thread; // the led-blink thread

void toggle( DigitalOut *pin ) { // thread entry function
  auto sleep_ms = std::chrono::milliseconds( 100 );
  SerialUSB.println("LED-blink thread started...");
  while(1) {
    *pin = !*pin; // toggle the pin
    ThisThread::sleep_for( sleep_ms );
  }
}

void setup() {
  SerialUSB.begin(115200);
  while(!SerialUSB){} // wait until the USB serial port is open.
  thread.start( callback(toggle,&led) ); // start the thread
  osDelay( osWaitForever ); // the main thread will wait forever
}

void loop() {}
