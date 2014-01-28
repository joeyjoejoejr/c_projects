#include <stdio.h>

int main(void)
{
  float x = 0.0f, result;

  printf("Enter x: ");
  scanf("%f", &x);
  result = ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;
  printf("Quadrinomial Result: %.2f\n", result);
}
