#ifndef KALEIDORTS_DRAW_H
#define KALEIDORTS_DRAW_H

#include <stdint.h>

typedef struct {
  uint64_t width;
  uint64_t height;
  uint8_t bit;
} Canvas;

typedef struct {
  uint8_t a;
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBA;

const Canvas *new_canvas(const uint64_t width, const uint64_t height, const uint8_t bit);
void save_canvas(const Canvas *canvas, const char *path);
void set_pixel(const Canvas *canvas, const RGBA rgba);
inline const RGBA rgb_to_rgba(const uint32_t rgb);

#endif //KALEIDORTS_DRAW_H
