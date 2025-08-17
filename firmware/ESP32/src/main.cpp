#include <Arduino.h>
#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "BluetoothSerial.h"

#define LED_BUILTIN 2  // Most ESP32 boards use GPIO2 for the built-in LED

BluetoothSerial SerialBT;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
  Serial.begin(115200);         // Start the serial communication at 115200 baud rate
  SerialBT.begin("ESP32_BT");   // Start Bluetooth with the name "ESP32_BT"
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
  delay(500);                      // Wait for 500 milliseconds
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off
  delay(500);                      // Wait for 500 milliseconds

  if (SerialBT.available()){
    String incomingData = SerialBT.readString();
    Serial.print("Received via Bluetooth: " + incomingData);

    if (incomingData == "ON") {
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on if "ON" command is received
      Serial.println("LED is ON");
    } else if (incomingData == "OFF") {
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off if "OFF" command is received
      Serial.println("LED is OFF");
    } else {
      Serial.println("Unknown command");
    }
  }
  
  SerialBT.println("Hello from ESP32!"); // Send a message via Bluetooth
  delay(1000); // Wait for a second before sending the next message
}
