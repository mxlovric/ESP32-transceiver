#ifndef GETTESTDATA_H_
#define GETTESTDATA_H_

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "Arduino.h"

#define SERVICE_UUID "3f8013b4-b3e0-403e-8fc8-d5bd35c3273c"
#define CHARACTERISTIC_UUID "2878a39f-cd02-4658-a1c7-4aa89aead85a"

class getDataFromMyMobile : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    String incomingData;
    if (value.length() > 0) {
      for (int i = 0; i < value.length(); i++) {
        incomingData += value[i];
      }
    }
    Serial.println(incomingData);
  }
};

class GetTestData {
 public:
  void setup() {
    BLEDevice::init("Tranceiver");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);
    pCharacteristic->setCallbacks(new getDataFromMyMobile());
    pCharacteristic->setValue("Success!");
    pService->start();
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
  }

  void deInitBLE() {
    BLEDevice::deinit(true);
  }
};

#endif  // GETTESTDATA_H_
