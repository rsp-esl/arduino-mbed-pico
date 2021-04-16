// File: example-11.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed;

#define ADC_VREF (3.3) 

// The GPIO29 pin on the Pico board is used 
// in ADC mode (ADC3) to measure VSYS/3.
AnalogIn  ain(p29); // GP25 = ADC3

void setup() {
   SerialUSB.begin(115200); 
   while(!SerialUSB){}
}

float read_adc_vsys() {
   uint32_t value = ain.read_u16(); // 16-bit value
   float volt = ADC_VREF*value/65536;
   return 3*volt;  
}

std::string sbuf;

void loop() {
   sbuf = "Voltage at VSYS Pin: ";
   sbuf += std::to_string( read_adc_vsys() );
   sbuf += " V";
   SerialUSB.println( sbuf.c_str() );
   delay(500);
}
