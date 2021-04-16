// File: example-1.ino
// Date: 2021-04-13
// Target: RPi Pico RP2040 

#define LED_PIN (p25) // use on-board LED (GP25 pin)

void setup() {
   SerialUSB.begin( 115200 ); // use USB-CDC (Serial)
   pinMode( LED_PIN, OUTPUT );
}

String sbuf;

void loop() {
   int next_state = !digitalRead( LED_PIN );
   digitalWrite( LED_PIN, next_state ); // update LED output
   sbuf = "LED state: ";
   sbuf += next_state;
   SerialUSB.println( sbuf.c_str() ); // send a string
   delay(500); // delay for 0.5 seconds
}