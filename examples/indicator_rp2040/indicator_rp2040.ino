#include <Arduino.h>
#include <SensirionI2CSgp40.h>
#include <SensirionI2CScd4x.h>
#include <Adafruit_Sensor.h>
#include <VOCGasIndexAlgorithm.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <PacketSerial.h>
#include "AHT20.h"

#define DEBUG 0

#define VERSION "v1.0.0"

#define SENSECAP "\n\
   _____                      _________    ____         \n\
  / ___/___  ____  ________  / ____/   |  / __ \\       \n\
  \\__ \\/ _ \\/ __ \\/ ___/ _ \\/ /   / /| | / /_/ /   \n\
 ___/ /  __/ / / (__  )  __/ /___/ ___ |/ ____/         \n\
/____/\\___/_/ /_/____/\\___/\\____/_/  |_/_/           \n\
--------------------------------------------------------\n\
 Version: %s \n\
--------------------------------------------------------\n\
"

AHT20 AHT;
SensirionI2CSgp40 sgp40;
SensirionI2CScd4x scd4x;
VOCGasIndexAlgorithm voc_algorithm;

PacketSerial myPacketSerial;

String SDDataString = "";


//Type of transfer packet

#define PKT_TYPE_SENSOR_SCD41_CO2 0XB2
#define PKT_TYPE_SENSOR_SHT41_TEMP 0XB3
#define PKT_TYPE_SENSOR_SHT41_HUMIDITY 0XB4
#define PKT_TYPE_SENSOR_TVOC_INDEX 0XB5
#define PKT_TYPE_CMD_COLLECT_INTERVAL 0xA0
#define PKT_TYPE_CMD_BEEP_ON 0xA1
#define PKT_TYPE_CMD_SHUTDOWN 0xA3



// sensor data send to  esp32
void sensor_data_send(uint8_t type, float data) {
  uint8_t data_buf[32] = { 0 };
  int index = 0;

  data_buf[0] = type;
  index++;

  memcpy(&data_buf[1], &data, sizeof(float));
  index += sizeof(float);

  myPacketSerial.send(data_buf, index);

#if DEBUG
  Serial.printf("---> send len:%d, data: ", index);
  for (int i = 0; i < index; i++) {
    Serial.printf("0x%x ", data_buf[i]);
  }
  Serial.println("");
#endif
}


void printUint16Hex(uint16_t value) {
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}

void sensor_power_on(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);
}

void sensor_power_off(void) {
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
}


float temperature = 0.0;
float humidity = 0.0;

uint16_t defaultCompenstaionRh = 0x8000;
uint16_t defaultCompenstaionT = 0x6666;

uint16_t compensationRh = defaultCompenstaionRh;
uint16_t compensationT = defaultCompenstaionT;

/************************ aht  temp & humidity ****************************/

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
    Serial.print("%\t temerature: ");
    Serial.println(temp);
    temperature = temp;
    humidity = humi * 100;
    compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
    compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);
  } else  // GET DATA FAIL
  {
    Serial.println("GET DATA FROM AHT20 FAIL");
    compensationRh = defaultCompenstaionRh;
    compensationT = defaultCompenstaionT;
  }

  SDDataString += "aht20,";
  if (ret) {
    SDDataString += String(temperature);
    SDDataString += ',';
    SDDataString += String(humidity);
    SDDataString += ',';

    sensor_data_send(PKT_TYPE_SENSOR_SHT41_TEMP, temperature);
    sensor_data_send(PKT_TYPE_SENSOR_SHT41_HUMIDITY, humidity);
  } else {
    SDDataString += "-,-,";
  }
}

/************************ sgp40 tvoc  ****************************/

void sensor_sgp40_init(void) {
  uint16_t error;
  char errorMessage[256];

  sgp40.begin(Wire);

  uint16_t serialNumber[3];
  uint8_t serialNumberSize = 3;

  error = sgp40.getSerialNumber(serialNumber, serialNumberSize);

  if (error) {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("SerialNumber:");
    Serial.print("0x");
    for (size_t i = 0; i < serialNumberSize; i++) {
      uint16_t value = serialNumber[i];
      Serial.print(value < 4096 ? "0" : "");
      Serial.print(value < 256 ? "0" : "");
      Serial.print(value < 16 ? "0" : "");
      Serial.print(value, HEX);
    }
    Serial.println();
  }

  uint16_t testResult;
  error = sgp40.executeSelfTest(testResult);
  if (error) {
    Serial.print("Error trying to execute executeSelfTest(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else if (testResult != 0xD400) {
    Serial.print("executeSelfTest failed with error: ");
    Serial.println(testResult);
  }
}

void sensor_sgp40_get(void) {
  uint16_t error;
  char errorMessage[256];
  uint16_t defaultRh = 0x8000;
  uint16_t defaultT = 0x6666;
  uint16_t srawVoc = 0;

  Serial.print("sensor sgp40: ");

  error = sgp40.measureRawSignal(compensationRh, compensationT, srawVoc);
  if (error) {
    Serial.print("Error trying to execute measureRawSignal(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    Serial.print("SRAW_VOC:");
    Serial.println(srawVoc);
  }

  SDDataString += "sgp40,";
  if (error) {
    SDDataString += "-,";
  } else {
    SDDataString += String(srawVoc);
    SDDataString += ',';

    int32_t voc_index = voc_algorithm.process(srawVoc);
    Serial.print("VOC Index: ");
    Serial.println(voc_index);

    sensor_data_send(PKT_TYPE_SENSOR_TVOC_INDEX, (float)voc_index);
  }
}


/************************ scd4x  co2 ****************************/

void sensor_scd4x_init(void) {
  uint16_t error;
  char errorMessage[256];

  scd4x.begin(Wire);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) {
    Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;
  error = scd4x.getSerialNumber(serial0, serial1, serial2);
  if (error) {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else {
    printSerialNumber(serial0, serial1, serial2);
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) {
    Serial.print("Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  // scd4x.powerDown();
}

void sensor_scd4x_get(void) {
  uint16_t error;
  char errorMessage[256];

  Serial.print("sensor scd4x: ");
  // Read Measurement
  uint16_t co2;
  float temperature;
  float humidity;
  error = scd4x.readMeasurement(co2, temperature, humidity);
  if (error) {
    Serial.print("Error trying to execute readMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } else if (co2 == 0) {
    Serial.println("Invalid sample detected, skipping.");
  } else {
    Serial.print("Co2:");
    Serial.print(co2);
    Serial.print("\t");
    Serial.print("Temperature:");
    Serial.print(temperature);
    Serial.print("\t");
    Serial.print("Humidity:");
    Serial.println(humidity);
  }

  SDDataString += "scd4x,";
  if (error) {
    SDDataString += "-,-,-,";
  } else {
    SDDataString += String(co2);
    SDDataString += ',';
    SDDataString += String(temperature);
    SDDataString += ',';
    SDDataString += String(humidity);
    SDDataString += ',';


    sensor_data_send(PKT_TYPE_SENSOR_SCD41_CO2, (float)co2);  //todo
  }
}

/************************ beep ****************************/

#define Buzzer 19  //Buzzer GPIO

void beep_init(void) {
  pinMode(Buzzer, OUTPUT);
}
void beep_off(void) {
  digitalWrite(19, LOW);
}
void beep_on(void) {
  analogWrite(Buzzer, 127);
  delay(50);
  analogWrite(Buzzer, 0);
}



/************************ grove  ****************************/

void grove_adc_get(void) {
  String dataString = "";
  int adc0 = analogRead(26);
  dataString += String(adc0);
  dataString += ',';
  int adc1 = analogRead(27);
  dataString += String(adc1);
  Serial.print("grove adc: ");
  Serial.println(dataString);
}


/************************ recv cmd from esp32  ****************************/

static bool shutdown_flag = false;

void onPacketReceived(const uint8_t *buffer, size_t size) {

#if DEBUG
  Serial.printf("<--- recv len:%d, data: ", size);
  for (int i = 0; i < size; i++) {
    Serial.printf("0x%x ", buffer[i]);
  }
  Serial.println("");
#endif
  if (size < 1) {
    return;
  }
  switch (buffer[0]) {
    case PKT_TYPE_CMD_SHUTDOWN:
      {
        Serial.println("cmd shutdown");
        shutdown_flag = true;
        sensor_power_off();
        break;
      }
    default:
      break;
  }
}

/************************ setuo & loop ****************************/

int cnt = 0;
int i = 0;
bool sd_init_flag = 0;

void setup() {
  Serial.begin(115200);

  Serial1.setRX(17);
  Serial1.setTX(16);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);

  sensor_power_on();

  Wire.setSDA(20);
  Wire.setSCL(21);
  Wire.begin();

  const int chipSelect = 13;
  SPI1.setSCK(10);
  SPI1.setTX(11);
  SPI1.setRX(12);
  if (!SD.begin(chipSelect, 1000000, SPI1)) {
    Serial.println("Card failed, or not present");
    sd_init_flag = 0;
  } else {
    Serial.println("card initialized.");
    sd_init_flag = 1;
  }

  sensor_aht_init();
  sensor_sgp40_init();
  sensor_scd4x_init();

  int32_t index_offset;
  int32_t learning_time_offset_hours;
  int32_t learning_time_gain_hours;
  int32_t gating_max_duration_minutes;
  int32_t std_initial;
  int32_t gain_factor;
  voc_algorithm.get_tuning_parameters(
    index_offset, learning_time_offset_hours, learning_time_gain_hours,
    gating_max_duration_minutes, std_initial, gain_factor);

  Serial.println("\nVOC Gas Index Algorithm parameters");
  Serial.print("Index offset:\t");
  Serial.println(index_offset);
  Serial.print("Learing time offset hours:\t");
  Serial.println(learning_time_offset_hours);
  Serial.print("Learing time gain hours:\t");
  Serial.println(learning_time_gain_hours);
  Serial.print("Gating max duration minutes:\t");
  Serial.println(gating_max_duration_minutes);
  Serial.print("Std inital:\t");
  Serial.println(std_initial);
  Serial.print("Gain factor:\t");
  Serial.println(gain_factor);


  beep_init();
  delay(500);
  beep_on();

  Serial.printf(SENSECAP, VERSION);
}

void loop() {
  if (i > 500) {
    i = 0;

    SDDataString = "";
    Serial.printf("\r\n\r\n--------- start measure %d-------\r\n", cnt);

    SDDataString += String(cnt);
    SDDataString += ',';

    cnt++;
    sensor_aht_get();
    sensor_sgp40_get();
    sensor_scd4x_get();
    grove_adc_get();

    if (sd_init_flag) {
      File dataFile = SD.open("datalog.csv", FILE_WRITE);
      // if the file is available, write to it:
      if (dataFile) {
        dataFile.println(SDDataString);
        dataFile.close();
        // print to the serial port too:
        Serial.print("sd write: ");
        Serial.println(SDDataString);
      } else {
        Serial.println("error opening datalog.txt");
      }
    }
  }

  i++;

  myPacketSerial.update();
  if (myPacketSerial.overflow()) {
  }
  delay(10);

  // while( shutdown_flag) {
  //    delay(10);
  // }
}
