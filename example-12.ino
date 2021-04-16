// File: example-12.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed;

#define ADC_VREF (3.3)

// ADC4 (internal ADC temperature sensor)
AnalogIn ain(ADC_TEMP); 

void setup() {
   SerialUSB.begin(115200); 
   while(!SerialUSB){}
}

float read_adc_temp() {
   uint32_t value = ain.read_u16();
   float volt = ADC_VREF*value/65536;
   float temp = (27.0 - (volt - 0.706)/0.01721);
   return temp; 
}

std::string sbuf;

void loop() {
   sbuf = "Internal temperature: ";
   sbuf += std::to_string( read_adc_temp() );
   sbuf += " deg.C";
   SerialUSB.println( sbuf.c_str() );
   delay(500);
}
