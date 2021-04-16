// File: example-8.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "stdio.h"
#include "mbed.h"
using namespace mbed;

#define LED_PIN (p25) // use on-board LED (GP25 pin)
#define STEPS   (10)  // number of LED brightness steps

const uint32_t PWM_PERIOD_US = 2000; // frequency 500Hz

PwmOut led_pwm(LED_PIN);

void setup() {
   SerialUSB.begin( 115200 );
   led_pwm.period_us( PWM_PERIOD_US ); // set period to 2msec
   led_pwm.pulsewidth_us( 0 );  // 0% duty cycle
}

char sbuf[64];

void loop() {
  uint32_t t, pw;
   for (uint32_t i=0; i < 2*STEPS; i++) {
      t = (i*PWM_PERIOD_US/STEPS);
      pw = (t <= PWM_PERIOD_US) ? t : 2*PWM_PERIOD_US-t;   
      led_pwm.pulsewidth_us( pw );
      sprintf( sbuf, "step %2lu) pulsewidth %4lu usec", i, pw );
      SerialUSB.println( sbuf );
      delay(100);
   } 
}
