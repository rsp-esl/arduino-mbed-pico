// File: example-10.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

// The GPIO29 pin on the Pico board is used
// in ADC mode (ADC3) to measure VSYS/3.
#define ADC_PIN  (A3)
#define ADC_BITS (12)  // use 12-bit ADC value
#define ADC_VREF (3.3) 

void setup() {
   SerialUSB.begin(115200); 
   while(!SerialUSB){}
   analogReadResolution( ADC_BITS );
}

float read_adc_vsys() {
   uint32_t value = analogRead(ADC_PIN);
   float volt = ADC_VREF*value/(1 << ADC_BITS);
   return 3*volt;  
}

String sbuf;

void loop() {
   sbuf = "Voltage at VSYS Pin: ";
   sbuf += read_adc_vsys();
   sbuf += " V";
   SerialUSB.println( sbuf.c_str() );
   delay(500);
}