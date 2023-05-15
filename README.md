# **SenseCAP Indicator RP2040**

This project is mainly some demonstration demos of RP2040, developed based on the arduino environment.

> Relevant: [SenseCAP Indicator RP2040](https://github.com/Seeed-Solution/SenseCAP_Indicator_ESP32)


## Arduino environment

Demos depends on the following packages.

- [Serial communication protocol](https://github.com/bakercp/PacketSerial)
- [SGP40 TVOC sensor library](https://github.com/Sensirion/arduino-i2c-sgp40)
- [Transfer index library: Sensirion Gas Index Algorithm](https://github.com/Sensirion/arduino-gas-index-algorithm)
- [SCD41 CO2 sensor library](https://github.com/Sensirion/arduino-i2c-scd4x)
- [AHT20 temperature and humidity sensor libray](https://github.com/Seeed-Studio/Seeed_Arduino_AHT20)
- [Sensirion Arduino Core library](https://github.com/Sensirion/arduino-core)


## Example Layout

- `adc`  Demonstrates how to collect data from the Grove ADC port.
- `aht20` Demonstrates how to collect AHT20 sensor data from the Grove I2C port
- `buzzer` Demonstrates how to cuse the buzzer.
- `co2` Demonstrates how to collect built-in SCD41 sensor data.
- `co2_alarm` Demonstrates how to collect built-in SCD41 sensor data and use buzzer to alarm.
- `indicator_rp2040` Demonstrates how to collect sensor data and send to ESP32.
- `rp2040_esp32_comm` Demonstration showcases the communication between ESP32 and RP2040.
- `sd` Demonstrates how to cuse the SD.
- `tvoc` Demonstrates how to collect built-in SGP40 sensor data.


## buzzer

The built-in buzzer of SenseCAP Indicator is a passive buzzer, meaning that it requires an AC signal(PWM) to trigger and output a sound, you can generate various tones and effects.This example demonstrates how to use the buzzer.


## co2

SenseCAP Indicator (D1S/D1Pro Version)has a built-in SCD41 sensor, which can detect the CO2 value with a range of 0-40000ppm.



## **SenseCAP Indicator Abstract**



SenseCAP Indicator is a 4-inch touch screen driven by ESP32-S3 and RP2040 Dual-MCU and supports Wi-Fi/Bluetooth/LoRa communication. 

The device comes two Grove interfaces, which supports ADC and I2C transmission protocols, and two USB Type-C ports with GPIO expantion pins inside, so user can easily expand external accessories via USB port.

SenseCAP Indicator is a fully open source powerful IoT development platform for developers. One-stop ODM Fusion service is also available for customization and quick scale-up.

<div align="center"><img width={800} src="https://files.seeedstudio.com/wiki/SenseCAP/SenseCAP_Indicator/SenseCAP_Indicator_1.png"/></div>


<p style={{textAlign: 'center'}}><a href="https://www.seeedstudio.com/SenseCAP-Indicator-D1-p-5643.html?" target="_blank"><img src="https://files.seeedstudio.com/wiki/RS485_500cm%20ultrasonic_sensor/image%202.png" border="0" /></a></p>



### **Features**



- **Dual MCUs and Rich GPIOs** 
Equipped with powerful ESP32S3 and RP2040 dual MCUs and over 400 Grove-compatible GPIOs for flexible expansion options.
- **Real-time Air Quality Monitoring** 
Built-in tVOC and CO2 sensors, and an external Grove AHT20 TH sensor for more precise temperature and humidity readings.
- **Local LoRa Hub for IoT Connectivity** 
Integrated Semtech SX1262 LoRa chip (optional) for connecting LoRa devices to popular IoT platforms such as Matter via Wi-Fi, without the need for additional compatible devices.
- **Fully Open Source Platform** 
Leverage the extensive ESP32 and Raspberry Pi open source ecosystem for infinite application possibilities.
- **Fusion ODM Service Available** 
Seeed Studio also provides one-stop ODM service for quick customization and scale-up to meet various needs.(please contact iot@seeed.cc)





