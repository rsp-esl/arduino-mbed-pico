#include "pico.h"
#include "hardware/gpio.h"
#include "USB/PluggableUSBSerial.h" 

#define LED_PIN (25) // use on-board LED (GP25 pin)

char sbuf[32];

int main() {
    // initialize Arduino SerialUSB
    PluggableUSBD().begin();
    Serial.begin( 115200 );
    while(!Serial){}
    Serial.println("Pico - Arduino Mbed Demo 3");

    // Pico SDK GPIO
    gpio_set_function( LED_PIN, GPIO_FUNC_SIO );
    gpio_set_pulls( LED_PIN, false, false );
    gpio_set_dir( LED_PIN, GPIO_OUT );

    while(1) {
       int next_state = !gpio_get( LED_PIN );
       gpio_put( LED_PIN, next_state );
       std::sprintf( sbuf, "LED state: %d", next_state );
       Serial.println( sbuf );
       sleep_ms( 100 );
   }
}
