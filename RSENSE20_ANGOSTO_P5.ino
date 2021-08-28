#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "BLEAddress.h"
#include <sstream>

std::string MAC_iBeacon = "24:62:ab:f3:54:fa";

int scanTime = 1; //In seconds
BLEScan* pBLEScan;
BLEUtils BLEutil;


class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      BLEAddress address(advertisedDevice.getAddress());
      if (address.toString().compare(MAC_iBeacon) == 0) {
        std::stringstream ss;
        ss << "RSSI: " << advertisedDevice.getRSSI() << std::endl
           << "Counter: " << *(uint16_t*)(advertisedDevice.getManufacturerData().data() + 23) << std::endl;
        Serial.println(ss.str().c_str());
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {

  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults();
}
