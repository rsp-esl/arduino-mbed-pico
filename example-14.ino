// File: example-14.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "mbed.h"
using namespace mbed;

#define ADC_VREF       (3300)  // mV
#define NUM_ADC_INPUTS (3)

// ADC4 (internal ADC temperature sensor)
AnalogIn a0(p26), a1(p27), a2(p28); 
AnalogIn *adc_list[] = { &a0, &a1, &a2 };

void setup() {
   SerialUSB.begin( 115200 ); 
   while(!SerialUSB){}
}

std::string sbuf;

void loop() {
  sbuf = "ADC values: ";
  for ( int i=0; i < NUM_ADC_INPUTS; i++ ) {
    uint32_t value = adc_list[i]->read_u16();
    float volt = ADC_VREF*value/65536;
    sbuf += std::to_string( volt );
    if (i < NUM_ADC_INPUTS-1) {
      sbuf += ",";
    }
  }
  SerialUSB.println( sbuf.c_str() );
  delay(100);
}
