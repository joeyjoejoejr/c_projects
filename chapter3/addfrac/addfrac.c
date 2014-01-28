#include <stdio.h>

int main(void)
{
  int num_one, num_two, den_one, den_two;

  printf("Enter two fractions separated by a plus sign: ");
  scanf("%d/%d+%d/%d", &num_one, &den_one, &num_two, &den_two);
  printf("The sum is %d/%d\n", num_one * den_two + num_two * den_one,
         den_one * den_two);

  return 0;
}
