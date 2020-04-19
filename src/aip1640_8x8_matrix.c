/*!
 * @file
 * @brief
 */

#include "aip1640_8x8_matrix.h"
#include "stm8s.h"
#include "stm8s_gpio.h"

enum {
  max_intensity = aip1640_8x8_matrix_max_intensity
};

static inline void write_clock(aip1640_8x8_matrix_t* self, uint8_t value) {
  self->usec_delay();
  tiny_digital_output_write(self->clock, value);
}

static inline void write_data(aip1640_8x8_matrix_t* self, uint8_t value) {
  self->usec_delay();
  tiny_digital_output_write(self->data, value);
}

static inline void start(aip1640_8x8_matrix_t* self) {
  write_data(self, 0);
  write_clock(self, 0);
}

static inline void stop(aip1640_8x8_matrix_t* self) {
  write_clock(self, 1);
  write_data(self, 1);
}

static void write(aip1640_8x8_matrix_t* self, uint8_t byte) {
  for(uint8_t i = 0; i < 8; i++) {
    write_clock(self, 0);
    write_data(self, byte & 1);
    write_clock(self, 1);
    byte >>= 1;
  }

  write_clock(self, 0);
  write_data(self, 0);
}

static void write_buffer(aip1640_8x8_matrix_t* self, const uint8_t* buffer) {
  start(self);
  write(self, 0x40);
  stop(self);

  start(self);
  write(self, 0xC0);

  for(uint8_t i = 0; i < 8; i++) {
    write(self, buffer[7 - i]);
  }

  stop(self);
}

static void write_intensity(aip1640_8x8_matrix_t* self, uint8_t intensity) {
  start(self);
  write(self, 0x88 | intensity);
  stop(self);
}

void aip1640_8x8_matrix_init(
  aip1640_8x8_matrix_t* self,
  i_tiny_digital_output_t* clock,
  i_tiny_digital_output_t* data,
  void (*usec_delay)(void)) {
  self->clock = clock;
  self->data = data;
  self->usec_delay = usec_delay;
  stop(self);
}

void aip1640_8x8_matrix_render(
  aip1640_8x8_matrix_t* self,
  const uint8_t buffer[8],
  uint8_t intensity) {
  write_buffer(self, buffer);
  write_intensity(self, intensity > max_intensity ? max_intensity : intensity);
}
