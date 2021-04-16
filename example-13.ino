// File: example-13.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#include "hardware/gpio.h"
#include "hardware/adc.h"

#define ADC_VREF (3.3) 

// The internal temperature sensor is on ADC4.
#define ADC_PIN  (30)

void setup() {
   SerialUSB.begin( 115200 );  
   adc_init();
   adc_set_temp_sensor_enabled ( true ); 
   adc_gpio_init( ADC_PIN );
   adc_select_input( ADC_PIN - 26 ); 
}

char sbuf[32];

void loop() {
   uint16_t value = adc_read(); // 12-bit value
   float volt = ADC_VREF*value/(1 << 12);
   float temp = (27.0 - (volt - 0.706)/0.01721);
   std::sprintf( sbuf, "Temperature: %.2f deg.C", temp );
   SerialUSB.println( sbuf );
   delay(500);
}