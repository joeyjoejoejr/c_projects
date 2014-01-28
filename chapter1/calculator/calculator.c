#include <stdio.h>

int main(void)
{
  float amount;

  printf("Enter an ammount: ");
  scanf("%f", &amount);
  printf("With tax added: %.2f\n", amount + amount * 0.05);
}
