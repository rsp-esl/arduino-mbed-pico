// File: example-9.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#define LED_PIN   (p25) // use on-board LED (GP25 pin)
#define STEPS     (10)  // number of LED brightness steps
#define MAX_VALUE (1023)

void setup() {
   SerialUSB.begin(115200);
   pinMode( LED_PIN, OUTPUT );
   analogWriteResolution( 10 ); // use 10-bit value
   analogWrite( LED_PIN, 0 );
}

char sbuf[64];

void loop() {
  uint32_t t, pw;
   for (uint32_t i=0; i < 2*STEPS; i++) {
      t = (i*MAX_VALUE/STEPS);
      pw = (t <= MAX_VALUE) ? t : 2*MAX_VALUE-t;
      analogWrite( LED_PIN, pw );
      sprintf( sbuf, "step %2lu) pulsewidth %4lu usec", i, pw );
      SerialUSB.println( sbuf );
      delay(100);
   } 
}