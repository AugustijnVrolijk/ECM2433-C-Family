#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pig.h"


/** Main function which continuously asks a user for a word or sentence to translate into pig latin
 * 
 * finishes when an empty line is detected
 */
int main() {
    int size = 1024;
    char *buffer;
    char *sentence;
    char *buffer_start;
    /* Malloc memory for buffer and sentence */
    if (!(buffer = (char *)malloc(size))) {
        printf("failed\n");
        exit(1);
    }
     /* save the start of the buffer to be able to freed at the end */
    buffer_start = buffer; 

    if (!(sentence = (char *)malloc(size))) {
        printf("failed\n");
        exit(1);
    }
    

    printf("Please enter a line of English:\n\n");
        /* fgets put input into buffer when input is received */
        if (fgets(buffer, size, stdin) == NULL) {
            printf("Error in fgets()\n");
            exit(1);
        }

    /* while loops breaks if sscanf is unable to assign a variable to %s, i.e not equal to 1*/
    while (sscanf(buffer, "%s", sentence) == 1)
    {

        /* iterate through buffer converting each word into pig latin
        no need to split buffer as sscanf %s stops when a whitespace is detected
        int n is used to increment buffer pointer each time new word is read */
        int n = 0;
        for (n; sscanf(buffer, "%s%n",sentence, &n) == 1; buffer +=n) {
            char *temp = pig(sentence);
            printf("%s ", temp);
            free(temp);
        }
        printf("\n\n");

        if ((int)strlen(buffer) > size-50) {
            size *= 2;
            char *temp = realloc(buffer, size);
            if (!temp) {
                printf("Error in realloc buffer\n");
                exit(1);
            }
            buffer = temp;

            temp = realloc(sentence, size);
            if (!temp) {
                printf("Error in realloc sentence\n");
                exit(1);
            }
            sentence = temp;
        }
        printf("Please enter another line of English:\n\n");
        /* fgets put input into buffer when input is received */
        if (fgets(buffer, size, stdin) == NULL) {
            printf("Error in fgets()\n");
            exit(1);
        }
    }
    free(buffer_start);
    free(sentence);
    return 0;
}




