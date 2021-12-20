/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include "async_sht30.h"
#include "tiny_utils.h"

enum {
  read_setup_delay = 500
};

void async_sht30_init(async_sht30_t* self, tiny_timer_group_t* timer_group, i_tiny_async_i2c_t* i2c, uint8_t address)
{
  self->timer_group = timer_group;
  self->i2c = i2c;
  self->address = address;
}

static inline uint16_t to_temperature_c(uint8_t msb, uint8_t lsb)
{
  return ((((uint32_t)msb << 8) + lsb) * 175) / 655 - 4500;
}

static inline uint16_t to_humidity(uint8_t msb, uint8_t lsb)
{
  return ((((uint32_t)msb << 8) + lsb) * 100) / 655;
}

static void read_complete(void* context, bool success)
{
  reinterpret(self, context, async_sht30_t*);
  uint16_t temperature_c = to_temperature_c(self->read_buffer[0], self->read_buffer[1]);
  uint16_t humidity = to_humidity(self->read_buffer[3], self->read_buffer[4]);
  self->callback(self->context, success, temperature_c, humidity);
}

static void read_setup_complete(tiny_timer_group_t* timer_group, void* context)
{
  reinterpret(self, context, async_sht30_t*);
  (void)timer_group;
  tiny_async_i2c_read(self->i2c, self->address, false, self->read_buffer, sizeof(self->read_buffer), self, read_complete);
}

static void read_setup_requested(void* context, bool success)
{
  reinterpret(self, context, async_sht30_t*);

  if(success) {
    tiny_timer_start(self->timer_group, &self->timer, read_setup_delay, self, read_setup_complete);
  }
  else {
    self->callback(self->context, false, 0, 0);
  }
}

static void set_up_read(async_sht30_t* self)
{
  static const uint8_t request[] = { 0x2C, 0x06 };
  tiny_async_i2c_write(self->i2c, self->address, false, request, sizeof(request), self, read_setup_requested);
}

void async_sht30_read(async_sht30_t* self, async_sht30_callback_t callback, void* context)
{
  self->callback = callback;
  self->context = context;

  set_up_read(self);
}
