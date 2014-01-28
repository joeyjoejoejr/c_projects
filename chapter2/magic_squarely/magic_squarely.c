#include <stdio.h>

int main(void)
{
  int a1, a2, a3, a4,
      b1, b2, b3, b4,
      c1, c2, c3, c4,
      d1, d2, d3, d4,
      a_sum, b_sum, c_sum, d_sum,
      one_sum, two_sum, three_sum, four_sum,
      diag_sum1, diag_sum2;

  printf("Enter the numbers from 1 to 16 in any order:\n");
  scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        &a1, &a2, &a3, &a4,
        &b1, &b2, &b3, &b4,
        &c1, &c2, &c3, &c4,
        &d1, &d2, &d3, &d4);

  a_sum =  a1 + a2 + a3 + a4;
  b_sum =  b1 + b2 + b3 + b4;
  c_sum =  c1 + c2 + c3 + c4;
  d_sum =  d1 + d2 + d3 + d4;

  one_sum = a1 + b1 + c1 + d1;
  two_sum = a2 + b2 + c2 + d2;
  three_sum = a3 + b3 + c3 + d3;
  four_sum = a4 + b4 + c4 + d4;

  diag_sum1 = a1 + b2 + c3 + d4;
  diag_sum2 = a4 + b3 + c2 + d1;

  printf("%2d %2d %2d %2d\n", a1, a2, a3, a4);
  printf("%2d %2d %2d %2d\n", b1, b2, b3, b4);
  printf("%2d %2d %2d %2d\n", c1, c2, c3, c4);
  printf("%2d %2d %2d %2d\n\n", d1, d2, d3, d4);

  printf("Row sums: %d %d %d %d\n", a_sum, b_sum, c_sum, d_sum);
  printf("Column sums: %d %d %d %d\n", one_sum, two_sum, three_sum, four_sum);
  printf("Diagnal sums: %d %d\n", diag_sum1, diag_sum2);

  return 0;
}
