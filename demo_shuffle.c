#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "riffle.h"


/** main function testing riffle.c
 */

int main() {
    /* initialise numbers and greek character arrays */
    int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};

    /* testing riffle_once */
    void *work = NULL;
    riffle_once(numbers, 20, sizeof(*numbers), work);
    riffle_once(greek, 12, sizeof(*greek), work);
    
    /* print results*/
    int i = 0;
    for (i; i < 20; i++) {
        printf("%d\n", numbers[i]);
    }
    printf("\n");
    for (i = 0; i < 12; i++) {
        printf("%s\n", greek[i]);
    }
    printf("\n");

    /* testing check_shuffle*/
    int j = check_shuffle(numbers, 20, sizeof(*numbers), compare_Int);
    printf("check_shuffle result for numbers is: %d\n", j);
    j = check_shuffle(greek, 12, sizeof(*greek), compare_char);
    printf("check_shuffle result for greek characters is: %d\n", j);

    return 0;
}