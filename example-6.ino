// File: example-6.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed;
using namespace rtos;

#define LED_PIN (p25) // use on-board LED (GP25 pin)

DigitalOut  led(LED_PIN);
Thread      threadA(osPriorityNormal), threadB(osPriorityNormal);
Mutex       mutex;

typedef struct _thread_arg {
  DigitalOut *pin;
  uint32_t   id;
  uint32_t   sleep_ms;
} thread_arg_t;

// used to pass thread's arguments
 thread_arg_t thread_args[] = {
  { .pin = &led, .id = 0, .sleep_ms = 100 },
  { .pin = &led, .id = 1, .sleep_ms = 100 },
};

void led_update( thread_arg_t *args ) {
  String s;
  auto sleep_ms = std::chrono::milliseconds( args->sleep_ms );
  while(1) {
    mutex.lock();
    *args->pin = !(args->id == 0);
    s = "thread id ";
    s += args->id;
    SerialUSB.println( s.c_str() );
    ThisThread::sleep_for( sleep_ms );
    mutex.unlock();
  }
}

void setup() {
  SerialUSB.begin(115200);
  threadA.start( callback(led_update, &thread_args[0]) );
  threadB.start( callback(led_update, &thread_args[1]) );
  osDelay( osWaitForever ); // the main thread will wait forever
}

void loop() {}