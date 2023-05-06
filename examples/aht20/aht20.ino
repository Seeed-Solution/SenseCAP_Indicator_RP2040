#include <Arduino.h>
#include <Wire.h>
#include "AHT20.h"

AHT20 AHT;

void sensor_aht_init(void) {
  AHT.begin();
}

void sensor_aht_get(void) {
  float humi, temp;
  int ret = AHT.getSensor(&humi, &temp);
  if (ret)  // GET DATA OK
  {
    Serial.print("humidity: ");
    Serial.print(humi * 100);
    Serial.print("  temerature: ");
    Serial.println(temp);
  } else  // GET DATA FAIL
  {
    Serial.println("GET DATA FROM AHT20 FAIL");
  }
}

void setup() {
  Serial.begin(115200);

  Wire.setSDA(20);
  Wire.setSCL(21);
  Wire.begin();

  sensor_aht_init();
}

void loop() {
  sensor_aht_get();
  delay(5000);
}
