#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pig.h"

/* function prototypes */

void testWords(char *words[]);

/* Main setup - define words to test and run test function */
int main() {
    char *happy = "Happy";
    char *duck = "duck";
    char *glove = "glove";
    char *evil = "evil";
    char *eight = "eight";
    char *yowler = "yowler";
    char *crystal = "crystal";
    char *words[] = {happy, duck, glove, evil, eight, yowler, crystal, 0};
    testWords(words);
    return 0;
}

/** A function which translates a 'sentence' or array of words into pig latin
 * 
 * @param words a pointer to an array of english words
 */
void testWords(char *words[]) {
    char **i;
    for(i = words; i != 0; i++) {
        char *temp;
        printf("Initial word is: %s\n",*i);
        temp = pig(*i);
        printf("Pig Latin word is: %s\n", temp);
    }
    return;
}