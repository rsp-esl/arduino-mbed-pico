// File: example-3.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#define LED_PIN (p25) // use on-board LED (GP25 pin)

uint32_t start_time_ms, saved_time_ms = 0;

void setup() {
   SerialUSB.begin( 115200 );
   pinMode( LED_PIN, OUTPUT );
   saved_time_ms = start_time_ms = millis();
}

String sbuf;

void loop() {
  uint32_t now = millis();
  if ( now - saved_time_ms >= 100 ) {
    saved_time_ms = now;
    digitalWrite( LED_PIN, !digitalRead( LED_PIN ) );
    sbuf = "LED state: ";
    sbuf += digitalRead( LED_PIN );
    sbuf += " ";
    sbuf += (now - start_time_ms);
    sbuf += "ms";
    SerialUSB.println( sbuf.c_str() ); 
  }
}
