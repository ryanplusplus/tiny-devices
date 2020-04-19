/*!
 * @file
 * @brief
 */

#ifndef aip1640_8x8_matrix_h
#define aip1640_8x8_matrix_h

#include <stdint.h>
#include "hal/i_tiny_digital_output.h"

enum {
  aip1640_8x8_matrix_max_intensity = 7
};

typedef struct {
  i_tiny_digital_output_t* clock;
  i_tiny_digital_output_t* data;
  void (*usec_delay)(void);
} aip1640_8x8_matrix_t;

void aip1640_8x8_matrix_init(
  aip1640_8x8_matrix_t* self,
  i_tiny_digital_output_t* clock,
  i_tiny_digital_output_t* data,
  void (*usec_delay)(void));

void aip1640_8x8_matrix_render(
  aip1640_8x8_matrix_t* self,
  const uint8_t buffer[8],
  uint8_t intensity);

#endif
