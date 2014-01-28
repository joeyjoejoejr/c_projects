#include <stdio.h>

int main(void)
{
  float loan_amount, interest_rate, monthly_payment, monthly_interest, remaining_balance;

  printf("Enter amount of loan: ");
  scanf("%f", &loan_amount);
  printf("Enter interest rate: ");
  scanf("%f", &interest_rate);
  printf("Enter monthly payment: ");
  scanf("%f", &monthly_payment);

  monthly_interest = interest_rate * 0.01f / 12.0f;
  remaining_balance = (loan_amount - monthly_payment) * (1 + monthly_interest);
  printf("Balance remaining after first payment: %.2f\n", remaining_balance);
  remaining_balance = (remaining_balance - monthly_payment) * (1 + monthly_interest);
  printf("Balance remaining after second payment: %.2f\n", remaining_balance);
  remaining_balance = (remaining_balance - monthly_payment) * (1 + monthly_interest);
  printf("Balance remaining after third payment: %.2f\n", remaining_balance);
  return 0;
}
