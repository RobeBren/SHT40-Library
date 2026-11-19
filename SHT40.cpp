#include <BR_SHT40.h>
#include <Wire.h>


BR_SHT40::BR_SHT40(uint8_t i2c_address) {
    _i2c_address = i2c_address;
}

bool BR_SHT40::begin() {
    Wire.beginTransmission(_i2c_address);

    if (Wire.endTransmission() == 0) {
        return true;
    }

    return false;
}


uint8_t BR_SHT40::calculateCRC(uint8_t msb, uint8_t lsb) {
    uint8_t crc = BR_SHT40::CRC_INITIALIZATION;

    // Process MSB
    crc ^= msb;

    for (uint8_t bit = 0; bit < 8; bit++) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ BR_SHT40::CRC_POLYNOMIAL;
        } else {
            crc <<= 1;
        }
    }

    // Process LSB
    crc ^= lsb;

    for (uint8_t bit = 0; bit < 8; bit++) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ BR_SHT40::CRC_POLYNOMIAL;
        } else {
            crc <<= 1;
        }
    }

    // Final XOR
    crc ^= BR_SHT40::CRC_FINAL_XOR;

    return crc;
}

std::array<float, 3> BR_SHT40::getTemperatureHumidity(uint8_t reg) {

    Wire.beginTransmission(_i2c_address);
    Wire.write(reg);

    Wire.endTransmission();

    // SHT40 takes up to 8.3ms to finish high-precision conversion
    delay(10);

    Wire.requestFrom(_i2c_address, 6);

    if (Wire.available() == 6) {
        uint8_t t_msb = Wire.read();
        uint8_t t_lsb = Wire.read();
        uint8_t t_crc = Wire.read();

        uint8_t h_msb = Wire.read();
        uint8_t h_lsb = Wire.read();
        uint8_t h_crc = Wire.read();  

        // Combine MSB and LSB into a single 16 bit unsigned integer
        uint16_t raw_temperature = (t_msb << 8) | t_lsb;
        uint16_t raw_humidity = (h_msb << 8) | h_lsb;
        
        // Convert to real values based on datasheet formulas 
        float temperatureFahrenheit = -49.0 + 315.0 * ((float)raw_temperature / 65535.0);   // degrees Farenheit
        float temperatureCelsius = -45.0 + 175.0 * ((float)raw_temperature / 65535.0);   // degrees Celsius
        float humidity = -6.0 + 125.0 * ((float)raw_humidity / 65535.0);

        if (humidity < 0) humidity = 0;
        if (humidity > 100) humidity = 100;

        return {temperatureFahrenheit, temperatureCelsius, humidity};
    }
    return {0.0, 0.0, 0.0};
}
