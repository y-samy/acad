#include <stdio.h>
int main()
{
  int quantity,discount_type;
  float unit_price,net_price;
  printf("Enter the quantity of the item: ");
  scanf("%d", &quantity);
  printf("Enter the price per item: $");
  scanf("%f", &unit_price);
  printf("Enter the type of discount you have: ");
  scanf("%d", &discount_type);
  
  printf("\nQuantity: %d \t\t Unit Price: $%.2f \t ", quantity,unit_price);
  switch(discount_type)
  {
    case 1:
      net_price = (unit_price*quantity)*0.9;
      printf("Discount Type: 1 \t Net Price : $%.2f \n", net_price);
      break;
    case 2:
      net_price = (unit_price*quantity)*0.85;
      printf("Discount Type: 2 \t Net Price: $%.2f \n", net_price);
      break;
    default:
      net_price = (unit_price*quantity)*0.95;
      printf("Discount Type: Others \t Net Price: $%.2f \n", net_price);
      break;
  }
  return 0;
}
