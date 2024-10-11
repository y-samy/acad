#include <stdio.h>
void main(){
    unsigned long long input = 1, buffer, sum = 0;
    int multiplicity_of_2 = 0, is_perfect = 0;
    do {
        if (input < 1) printf("Value error. Only positive integers allowed.\n");
        printf("Enter a number: ");
        scanf("%lld", &input);
    } while (input < 1);
    buffer = input;
    do {
        if (buffer % 2 != 0) {
            if (multiplicity_of_2 > 0){
                unsigned long long even_pair = input / buffer;
                if (2*even_pair - 1 == buffer) is_perfect = 1;
            }
            break;
        }
        buffer /= 2; multiplicity_of_2++;
    } while (buffer > 1);
    printf("The positive divisors: "); /* Spacing as intended in lab note */
    if (is_perfect) {
        int i, k;
        unsigned long long j = 1;
        for (k = 1; k >= 0; k--) {
            for (i = 0; i < multiplicity_of_2 + k; i++) {
                printf("%lld , ", j);
                j *= 2;
            }
            j = buffer;
        }
    } else {
        unsigned long long i;
        for (i = 1; i < input; i++){
            if (input % i != 0) continue;
            sum += i;
            printf("%lld , ", i);
        }
    }
    printf("\nThe sum of divisors is %lld\n", (is_perfect ? input : sum));
    printf("%lld is %s perfect number", input, (is_perfect ? "a" : "not a"));
}
