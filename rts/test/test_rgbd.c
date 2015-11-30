#include <stdio.h>
#include "draw.h"

int main() {
  printf("sizeof(RGBA) = %ld\n", sizeof(RGBA));
  RGBA rgbd = rgb_to_rgba(0x66CCFF);
  printf("R = %X\n", rgbd.r);
  printf("G = %X\n", rgbd.g);
  printf("B = %X\n", rgbd.b);
  printf("A = %X\n", rgbd.a);
  return 0;
}
