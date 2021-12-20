/*!
 * @file
 * @brief
 */

#include "eeprom_24lc32.h"

void eeprom_24lc32_init(eeprom_24lc32_t* self, i_tiny_i2c_t* i2c, uint8_t address)
{
  self->i2c = i2c;
  self->address = address;
}

bool eeprom_24lc32_write(eeprom_24lc32_t* self, uint16_t address, uint8_t value)
{
  uint8_t write[] = { address >> 8, address & 0xFF, value };
  if(!tiny_i2c_write(self->i2c, self->address, false, write, sizeof(write))) {
    return false;
  }

  uint8_t dummy = 0;
  uint8_t timeout = 100;
  while(--timeout) {
    if(tiny_i2c_write(self->i2c, self->address, false, &dummy, sizeof(dummy))) {
      return true;
    }
  }

  return false;
}

bool eeprom_24lc32_read(eeprom_24lc32_t* self, uint16_t address, uint8_t* value)
{
  uint8_t read_address[] = { address >> 8, address & 0xFF };
  if(!tiny_i2c_write(self->i2c, self->address, true, read_address, sizeof(read_address))) {
    return false;
  }

  return tiny_i2c_read(self->i2c, self->address, false, value, sizeof(*value));
}
