//RSENSE20_ANGOSTO_P5
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("RSENSE20_ANGOSTO_P5"); 
  Serial.println("Vinculate con el dispositivoRSENSE20_ANGOSTO_P5");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
