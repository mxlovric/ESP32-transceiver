#include "Arduino.h"
#include "getTestData.h"
GetTestData getData;

void setup() {
  Serial.begin(115200);
  getData.setup();
}

void loop() {
}
