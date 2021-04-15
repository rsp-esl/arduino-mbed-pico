#define LED_PIN  (25) // use on-board LED (GP25 pin)

String sbuf;

void setup() {
    // initialize Arduino SerialUSB
    Serial.begin( 115200 );
    pinMode( LED_PIN, OUTPUT ); 
    while(!Serial){}
    Serial.println("Pico - Arduino Mbed Demo 1");
}

void loop() {
    // toggle and update LED output
    int next_state = !digitalRead( LED_PIN );
    digitalWrite( LED_PIN, next_state );
    sbuf = "LED state: ";
    sbuf += next_state;
    Serial.println( sbuf.c_str() );
    delay( 100 );
}
