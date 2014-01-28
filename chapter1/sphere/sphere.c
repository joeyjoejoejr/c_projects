#include <stdio.h>

int main(void) {
  float radius = 10;
  printf("Volume of sphere with radius %.1f: %.1f\n", radius,
    4.0f/3.0f * radius * radius * radius);
}
