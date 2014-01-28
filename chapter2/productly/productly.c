#include <stdio.h>

int main(void)
{
  int item_number, month, day, year;
  float item_price;

  printf("Enter item number: ");
  scanf("%d", &item_number);
  printf("Enter a unit price: ");
  scanf("%f", &item_price);
  printf("Enter purchase date (mm/dd/yyyy): ");
  scanf("%d/%d/%d", &month, &day, &year);

  printf("Item\tUnit Price\tPurchase Date\n");
  printf("%-d\t$%7.2f\t%.2d/%.2d/%.4d\n", item_number, item_price, month, day, year);

  return 0;
}
