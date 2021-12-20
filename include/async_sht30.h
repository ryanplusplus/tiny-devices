/*!
 * @file
 * @brief
 */

#ifndef async_sht30_h
#define async_sht30_h

#include "hal/i_tiny_async_i2c.h"
#include "tiny_timer.h"

enum {
  async_sht30_default_address = 0x45,
  async_sht30_alternate_address = 0x44
};

typedef void (*async_sht30_callback_t)(
  void* context,
  bool success,
  uint16_t temperature_c_x100,
  uint16_t humidity_x100);

typedef struct {
  tiny_timer_t timer;
  uint8_t read_buffer[6];
  tiny_timer_group_t* timer_group;
  void* context;
  async_sht30_callback_t callback;
  i_tiny_async_i2c_t* i2c;
  uint8_t address;
} async_sht30_t;

void async_sht30_init(async_sht30_t* self, tiny_timer_group_t* timer_group, i_tiny_async_i2c_t* i2c, uint8_t address);
void async_sht30_read(async_sht30_t* self, async_sht30_callback_t callback, void* context);

#endif
