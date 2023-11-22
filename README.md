<p align="center">
  <a href="https://wiki.seeedstudio.com/SenseCAP_Indicator_How_To_Flash_The_Default_Firmware/#flash-by-arduino-ide">
    <img src="https://files.seeedstudio.com/wiki/wiki-platform/SeeedStudio.png" width="auto" height="auto" alt="SenseCAP">
  </a>
</p>

<div align="center">

# **SenseCAP Indicator RP2040**

This project is mainly some demonstration demos of RP2040, developed based on the arduino environment.

</div>

<p align="center">
  <a href="https://raw.githubusercontent.com/seeed-solution/SenseCAP_Indicator_RP2040/main/LICENSE">
    <img src="https://img.shields.io/github/license/seeed-solution/SenseCAP_Indicator_RP2040" alt="license">
  </a>
  <a href="https://github.com/seeed-solution/SenseCAP_Indicator_RP2040/releases">
    <img src="https://img.shields.io/github/v/release/seeed-solution/SenseCAP_Indicator_RP2040?include_prereleases&color=blueviolet" alt="release">
  </a>
    <img src="https://img.shields.io/github/repo-size/seeed-solution/SenseCAP_Indicator_RP2040" alt="repo-size">
</p>

> Relevant: [SenseCAP Indicator ESP32](https://github.com/Seeed-Solution/SenseCAP_Indicator_ESP32) | [Wiki](https://wiki.seeedstudio.com/SenseCAP_Indicator_How_To_Flash_The_Default_Firmware/#rp2040-development-tool)

## Arduino environment

Demos depends on the following packages.

- [Serial communication protocol](https://github.com/bakercp/PacketSerial)
- [Sensirion Arduino Core library](https://github.com/Sensirion/arduino-core)
- [SGP40 TVOC sensor library](https://github.com/Sensirion/arduino-i2c-sgp40)
- [Transfer index library: Sensirion Gas Index Algorithm](https://github.com/Sensirion/arduino-gas-index-algorithm)
- [SCD41 CO2 sensor library](https://github.com/Sensirion/arduino-i2c-scd4x)
- [AHT20 temperature and humidity sensor libray](https://github.com/Seeed-Studio/Seeed_Arduino_AHT20)

To search it in Arduino IDE, you can click `Tools` -> `Manage Libraries...` and search the name of the library.

|Packages|Version|Name|
|---|---|---|
|Sensirion Arduino Core library|0.6.0|Sensirion Core|
|Serial communication protocol|1.4.0|PacketSerial|
|SGP40 TVOC sensor library|0.1.0|Sensirion I2C SGP40|
|SCD41 CO2 sensor library|0.4.0|Sensirion I2C SCD4x|
|Transfer index library: Sensirion Gas Index Algorithm|3.2.2|Sensirion Gas Index Algorithm|
|AHT20 temperature and humidity sensor libray|1.0.1|Seeed_Arduino_AHT20|

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


## **SenseCAP Indicator Abstract**



SenseCAP Indicator is a 4-inch touch screen driven by ESP32-S3 and RP2040 Dual-MCU and supports Wi-Fi/Bluetooth/LoRa communication. 

The device comes two Grove interfaces, which supports ADC and I2C transmission protocols, and two USB Type-C ports with GPIO expantion pins inside, so user can easily expand external accessories via USB port.

SenseCAP Indicator is a fully open source powerful IoT development platform for developers. One-stop ODM Fusion service is also available for customization and quick scale-up.

<div align="center"><img width={480} src="https://files.seeedstudio.com/wiki/SenseCAP/SenseCAP_Indicator/SenseCAP_Indicator_1.png"/></div>

<p align="center" style={{textAlign: 'center'}}><a href="https://www.seeedstudio.com/SenseCAP-Indicator-D1-p-5643.html" ><img src="https://files.seeedstudio.com/wiki/RS485_500cm%20ultrasonic_sensor/image%202.png" border="0" /></a></p>



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
Seeed Studio also provides one-stop ODM service for quick customization and scale-up to meet various needs. (please contact iot@seeed.cc)





