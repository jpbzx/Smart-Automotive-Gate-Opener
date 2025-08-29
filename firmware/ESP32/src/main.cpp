#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2

BLEServer* pServer = nullptr;
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      digitalWrite(LED_BUILTIN, HIGH);
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      digitalWrite(LED_BUILTIN, LOW);
    }
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  BLEDevice::init("ESP32_BLE");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x180F));
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         BLEUUID((uint16_t)0x2A19),
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );
  pCharacteristic->setValue("Hello from ESP32!");
  pService->start();

  pServer->getAdvertising()->start();
  Serial.println("BLE device is now advertising");
}

void loop() {
  // You can add BLE notification logic here if needed
}


