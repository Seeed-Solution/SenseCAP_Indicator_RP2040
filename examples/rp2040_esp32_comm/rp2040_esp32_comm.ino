#include <Arduino.h>
#include <PacketSerial.h>

#define DEBUG   0

//Type of transfer packet
#define PKT_TYPE_SENSOR_SCD41_CO2 0XB2
#define PKT_TYPE_SENSOR_ATH20_TEMP 0XB3
#define PKT_TYPE_SENSOR_ATH20_HUMIDITY 0XB4
#define PKT_TYPE_SENSOR_TVOC_INDEX 0XB5
#define PKT_TYPE_CMD_COLLECT_INTERVAL 0xA0
#define PKT_TYPE_CMD_BEEP_ON 0xA1
#define PKT_TYPE_CMD_SHUTDOWN 0xA3


#define PKT_TYPE_ACK  0x00

PacketSerial myPacketSerial;


/************************  sensor data send to  esp32 ****************************/
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

/************************ recv cmd from esp32  ****************************/

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
    case PKT_TYPE_ACK:
      {
        Serial.printf("recv: %s\r\n ", &buffer[1]);
        break;
      }
    default:
      break;
  }

}

void setup() {
  Serial.begin(115200);

  Serial1.setRX(17);
  Serial1.setTX(16);
  Serial1.begin(115200);
  myPacketSerial.setStream(&Serial1);
  myPacketSerial.setPacketHandler(&onPacketReceived);
}

int i = 0;

void loop() {
  if (i > 500) {
    i=0;
    Serial.println("send data...");
    sensor_data_send(PKT_TYPE_SENSOR_SCD41_CO2, (float)423.3);
    sensor_data_send(PKT_TYPE_SENSOR_ATH20_TEMP, (float)25.0);
    sensor_data_send(PKT_TYPE_SENSOR_ATH20_HUMIDITY, (float)65.1);
    sensor_data_send(PKT_TYPE_SENSOR_TVOC_INDEX, (float)100.0);
  }
  i++;
  myPacketSerial.update();
  if (myPacketSerial.overflow()) {
  }
  delay(10);
}
