/*!
 * @file
 * @brief
 */

#ifndef eeprom_24lc32_h
#define eeprom_24lc32_h

#include "hal/i_tiny_i2c.h"

enum {
  eeprom_24lc32_default_address = 0x50
};

typedef struct {
  i_tiny_i2c_t* i2c;
  uint8_t address;
} eeprom_24lc32_t;

void eeprom_24lc32_init(eeprom_24lc32_t* self, i_tiny_i2c_t* i2c, uint8_t address);
bool eeprom_24lc32_write(eeprom_24lc32_t* self, uint16_t address, uint8_t value);
bool eeprom_24lc32_read(eeprom_24lc32_t* self, uint16_t address, uint8_t* value);

#endif
