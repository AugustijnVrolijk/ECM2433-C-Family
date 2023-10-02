#include <stdio.h>
#include <stdlib.h>
#include "beggar.h"
#include "riffle.h"


int main(int argc,char **argv) {
    if (argc < 2) {
        printf("Please specify number of players\n");
        exit(1);
    }
    int Players = atoi(argv[1]);
    int deck[52] = {
        2,2,2,2,
        3,3,3,3,
        4,4,4,4,
        5,5,5,5,
        6,6,6,6,
        7,7,7,7,
        8,8,8,8,
        9,9,9,9,
        10,10,10,10,
        11,11,11,11,
        12,12,12,12,
        13,13,13,13,
        14,14,14,14
    };
    riffle(deck, 52, sizeof(int), 5); 
    beggar(Players,deck,1);
    return 0;
}