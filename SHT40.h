/*
 * ***************************************************************************
 * Component:    SHT40 - Temperature and Humidity Sensor
 * Manufacturer: Adafruit
 * Product:      SHT40 - Sensirion Temperature & Humidity Sensor - STEMMA QT / Qwiic
 * Product ID:   4885
 *
 * Product Page:
 *     https://www.adafruit.com/product/4885
 *
 * Datasheet:
 *     https://sensirion.com/media/documents/33FD6951/6A7C10A0/HT_DS_Datasheet_SHT4x_V7.3.pdf
 *
 * ***************************************************************************
 */

#ifndef SHT40_H
#define SHT40_H

#include <Arduino.h>
#include <array>


class SHT40 {
    public:

        /// I2C interface address
        static constexpr uint8_t I2C_ADR = 0x44;             


        /// measure T & RH with high precision (high repeatability) Register
        static constexpr uint8_t TEMP_RH_HIGH = 0xFD;
        /// measure T & RH with medium precision (medium repeatability) Register   
        static constexpr uint8_t TEMP_RH_MEDIUM = 0xF6;
        /// measure T & RH with lowest precision (low repeatability) Register   
        static constexpr uint8_t TEMP_RH_LOW = 0xE0;
        /// read serial number Register   
        static constexpr uint8_t SERIAL_NUMBER = 0x89;
        /// soft reset Register  
        static constexpr uint8_t RESET = 0x94;
        /// activate heater with 200mW for 1s Register       
        static constexpr uint8_t HEATER_1 = 0x39;
        /// activate heater with 200mW for 0.1s Register
        static constexpr uint8_t HEATER_2 = 0x32;
        /// activate heater with 110mW for 1s Register
        static constexpr uint8_t HEATER_3 = 0x2F;
        /// activate heater with 110mW for 0.1s Register
        static constexpr uint8_t HEATER_4 = 0x24;
        /// activate heater with 20mW for 1s Register
        static constexpr uint8_t HEATER_5 = 0x1E;
        /// activate heater with 20mW for 0.1s Register
        static constexpr uint8_t HEATER_6 = 0x15;


        

        SHT40(uint8_t i2c_address = I2C_ADR);
        bool begin();
        std::array<float, 3> getTemperatureHumidity(uint8_t reg);
        // uint32_t getSerialNumber();
        // bool reset();
        // void activateHeater(uint8_t heater);

    private:
        uint8_t _i2c_address;

        /// CRC Checksum Polynomial Value Register
        static constexpr uint8_t CRC_POLYNOMIAL = 0x31;
        /// CRC Checksum Initialization Value Register    
        static constexpr uint8_t CRC_INITIALIZATION = 0xFF;
        /// CRC Checksum Final XOR Value Register
        static constexpr uint8_t CRC_FINAL_XOR = 0x00;

        static uint8_t calculateCRC(uint8_t msb, uint8_t lsb);

};

#endif
