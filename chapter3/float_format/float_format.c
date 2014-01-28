#include <stdio.h>

int main(void)
{
  float x;
  printf("Enter x: ");
  scanf("%f", &x);
  printf("%-8.2e\n", x);
  printf("%10.6e\n", x);
  printf("%-8.3f\n", x);
  printf("%6.0f\n", x);

  return 0;
}
