#include <stdint.h>
#include "draw.h"

const RGBA rgb_to_rgba(const uint32_t rgb) {
  RGBA rgba = {
    .a = 0xFF,
    .r = (uint8_t) ((rgb & 0xFF0000) >> 16),
    .g = (uint8_t) ((rgb & 0x00FF00) >> 8),
    .b = (uint8_t) (rgb & 0x0000FF)
  };
  return rgba;
}
