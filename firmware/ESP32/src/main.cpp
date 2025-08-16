#include <Arduino.h>
#include "esp32-hal.h"
#include "esp32-hal-gpio.h"

#define LED_BUILTIN 2  // Most ESP32 boards use GPIO2 for the built-in LED

void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
  
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
  delay(500);                      // Wait for 500 milliseconds
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
  delay(500);                      // Wait for 500 milliseconds
}
