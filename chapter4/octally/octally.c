#include <stdio.h>

int main(void)
{
  int decimal, digit1, digit2, digit3, digit4, digit5, remainder;

  printf("Enter a number between 0 and 32767: ");
  scanf("%d", &decimal);
  digit5 = decimal % 8;
  remainder = decimal / 8;
  digit4 = remainder % 8;
  remainder = remainder / 8;
  digit3 = remainder % 8;
  remainder = remainder / 8;
  digit2 = remainder % 8;
  remainder = remainder / 8;
  digit1 = remainder % 8;
  remainder = remainder / 8;
  printf("In octal your number is: %d%d%d%d%d\n", digit1, digit2, digit3, digit4, digit5);

  return 0;
}


