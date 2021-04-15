#include "mbed.h"
#include "USB/PluggableUSBSerial.h" 

#define LED_PIN (p25) // use on-board LED (GP25 pin)

mbed::DigitalOut led( LED_PIN );
std::string sbuf;

int main() {
    // initialize Arduino SerialUSB
    PluggableUSBD().begin();
    Serial.begin( 115200 );
    while(!Serial){}
    Serial.println("Pico - Arduino Mbed Demo 2");

    auto sleep_ms = std::chrono::milliseconds(100);
    while (1) {
        // toggle and update LED output
        led = !led;
        sbuf = "LED state: ";
        sbuf += std::to_string( led.read() );
        Serial.println( sbuf.c_str() ); 
        rtos::ThisThread::sleep_for( sleep_ms );
    }
}
