#include <stdio.h>
#include <math.h>
void main(){
    int n = 1, i, total = 0, j;
    double avg, variance, summation = 0;
    do {
        if (n < 1) printf("Value error. Only positive integers allowed.\n");
        printf("Enter the sample size: ");
        scanf("%d", &n);
    } while (n < 1);
    int sample[n] = {}, width = floor(log10(n)) + 1;
    for (i = 1; i <= n; i++) {
        printf("Enter number (%*d/%d): ", width, i, n);
        scanf("%d", &sample[i-1]);
        total += sample[i-1];
    }
    avg = (double) total/n;
    for (j = 0; j < n; j++){
        summation +=  pow(sample[j] - avg, 2);
    }
    variance = (double) summation / (n - 1);
    printf("Average: %f\nVariance: %f", avg, variance);
}