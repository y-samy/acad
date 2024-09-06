#include <math.h>
#include <stdio.h>

int main() {
  // Runtime variable declarations
  float streetlen, treedist, treecost, totalcost;
  int treenum;

  // Input prompts
  printf("Hello, John! Let's help you fill the street with trees.\n\n");
  printf("Please enter the length of the street (m): ");
  scanf("%f", &streetlen);
  printf("Now enter the distance you want between each tree (m): ");
  scanf("%f", &treedist);
  printf("Great! Finally, enter the cost of planting one tree ($): ");
  scanf("%f", &treecost);
  printf("\n"); // To separate input from results

  // Calculations
  treenum = 1 + floor(streetlen / treedist);
  totalcost = (float) treecost * treenum;

  // Outputting the results
  printf("You will have to plant %d tree(s)\n", treenum);
  printf("The total price you'll pay will be $%.2f\n", totalcost);

  return 0;
}
