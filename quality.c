#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "riffle.h"

/* testing quality and average_quality */
int main() {

    int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    /* testing riffle_once using quality */
    void *work = NULL;
    riffle_once(numbers, 20, sizeof(*numbers), work);
    printf("the quality for 1 shuffle is: %f\n",quality(numbers, 20));

    /* testing riffle using average_quality */
    int j;
    for (j = 1; j <= 15; j++) {
            printf("the quality for %d shuffles is: %f\n",j,average_quality(50, j, 30));
        }
    
}