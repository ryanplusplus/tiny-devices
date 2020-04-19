/*!
 * @file
 * @brief
 */

#ifndef sht30_h
#define sht30_h

#include "hal/i_tiny_async_i2c.h"
#include "tiny_timer.h"

enum {
  sht30_default_address = 0x45,
  sht30_alternate_address = 0x44
};

typedef void (*sht30_callback_t)(
  void* context,
  bool success,
  uint16_t temperature_c_x100,
  uint16_t humidity_x100);

typedef struct {
  tiny_timer_t timer;
  uint8_t read_buffer[6];
  tiny_timer_group_t* timer_group;
  void* context;
  sht30_callback_t callback;
  i_tiny_async_i2c_t* i2c;
  uint8_t address;
} sht30_t;

void sht30_init(sht30_t* self, tiny_timer_group_t* timer_group, i_tiny_async_i2c_t* i2c, uint8_t address);
void sht30_read(sht30_t* self, sht30_callback_t callback, void* context);

#endif
