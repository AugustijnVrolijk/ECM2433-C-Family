#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pig.h"


/** A function which translates a given word from english to pig latin
 * It classifies the given word into 3 categories
 * 
 * @param word a pointer to a word in english
 * 
 * @returns pointer to a translated word in pig Latin
 */

char *pig(char *word) {
    char *pigLatinWord;
    
    /* Malloc memory for piglatin word - max is 3 char longer than original 
    for a word starting with a vowel */
    if (!(pigLatinWord = (char *)malloc((strlen(word)+4)*sizeof(*word)))) {
        printf("failed to malloc memory for word\n");
        exit(1);
        }

    if (tolower(*word) == 121) {
        handleY(word, pigLatinWord);
    } else if (isConsonant(*word)) {
        consonant(word, pigLatinWord);
    } else {
        vowel(word, pigLatinWord);
    }
    return pigLatinWord;
}


/** A function which returns true if a character is a consonant, and false if its a vowel
 * 
 * @param character a single character in the english alphabet
 * 
 * @returns true or false depending on whether the input char is a consonant
 */
bool isConsonant(char character) {
    /* returns true if character is a consonant, otherwise false 
     tolower enables this to also handle uppercase cases without
      doubling the size of the switch case*/
    switch (tolower(character))
    {
    case 'a':return false;
    case 'b':return true;
    case 'c':return true;
    case 'd':return true;
    case 'e':return false;
    case 'f':return true;
    case 'g':return true;
    case 'h':return true;
    case 'i':return false;
    case 'j':return true;
    case 'k':return true;
    case 'l':return true;
    case 'm':return true;
    case 'n':return true;
    case 'o':return false;
    case 'p':return true;
    case 'q':return true;
    case 'r':return true;
    case 's':return true;
    case 't':return true;
    case 'u':return false;
    case 'v':return true;
    case 'w':return true;
    case 'x':return true;
    case 'y':return false;
    case 'z':return true;
    case ' ':return false;
    case 0:return false;
    /* case 0 is added in case word only has consonants, 
    if NUL character is found it returns false stopping the loop */    
    default:
        printf("One of the characters in the given word was not a valid character");
        exit(1);
    }
}

/** A function which translates a word beginning with a consonant into pig latin
 * 
 * @param word a pointer to an english word
 * @param pigLatinWord a pointer to malloced memory to put the translated word into
 */

void consonant(char *word, char *pigLatinWord) {
  
    /* Malloc memory for temp array to store starting consonants,
     this cant be larger than the length of the word */
    char *startingConsonants;
    if (!(startingConsonants = (char *)malloc(strlen(word)*sizeof(*word)))) {
        printf("failed to malloc memory for word\n");
        exit(1);
    }

    char *PigLatinP = pigLatinWord;
    char *startingConsonantsP = startingConsonants;
    char *wordP = word;

    /* add starting consonants to temporary array to add back later */
    for(; isConsonant(*wordP); wordP++) {
        *startingConsonantsP = tolower(*wordP);
        startingConsonantsP++;
    }
    *startingConsonantsP = 0;

    /* Copy origianl word into malloced memory - stops when a NUL character is found*/
    for(; *wordP != 0; wordP++) {
        *PigLatinP = *wordP;
        PigLatinP++;
    }

    /* add back consonants to end of word */
    for(startingConsonantsP = startingConsonants; *startingConsonantsP != 0; startingConsonantsP++) {
        *PigLatinP = *startingConsonantsP;
        PigLatinP++;
    }
 
    /* add 'ay' as well as ending NUL character */
    *PigLatinP = 'a';
    PigLatinP++; *PigLatinP = 'y';
    PigLatinP++; *PigLatinP = 0;
    free(startingConsonants);

    return;
    }

/** A function which translates a word beginning with a 'Y' into pig latin
 * 
 * @param word a pointer to an english word
 * @param pigLatinWord a pointer to malloced memory to put the translated word into
 */
void handleY(char *word, char *pigLatinWord) {
    
    /* Malloc memory for temp array to store starting consonants,
     this cant be larger than the length of the word */
    char *startingConsonants;
    if (!(startingConsonants = (char *)malloc(strlen(word)*sizeof(*word)))) {
        printf("failed to malloc memory for word\n");
        exit(1);
    }

    char *PigLatinP = pigLatinWord;
    char *startingConsonantsP = startingConsonants;
    char *wordP = word;
    
    /* Add starting Y to consonants despite it classified as a vowel */
    *startingConsonantsP = tolower(*wordP);
    startingConsonantsP++;
    wordP++;

    /* add starting consonants to temporary array to add back later */
    for(; isConsonant(*wordP); wordP++) {
        *startingConsonantsP = tolower(*wordP);
        startingConsonantsP++;
    }
    *startingConsonantsP = 0;

    /* Copy origianl word into malloced memory - stops when a NUL character is found*/
    for(; *wordP != 0; wordP++) {
        *PigLatinP = *wordP;
        PigLatinP++;
    }

    /* add back consonants to end of word */
    for(startingConsonantsP = startingConsonants; *startingConsonantsP != 0; startingConsonantsP++) {
        *PigLatinP = *startingConsonantsP;
        PigLatinP++;
    }
 
    /* add 'ay' as well as ending NUL character */
    *PigLatinP = 'a';
    PigLatinP++; *PigLatinP = 'y';
    PigLatinP++; *PigLatinP = 0;
    free(startingConsonants);

    return;
    }

/** A function which translates a word beginning with a vowel into pig latin
 * 
 * @param word a pointer to an english word
 * @param pigLatinWord a pointer to malloced memory to put the translated word into
 */
void vowel(char *word, char *pigLatinWord) {

    /* Copy original word into malloced memory - stops when a NUL character is found*/
    char *p = word;
    char *i = pigLatinWord;
    for(; *p != 0; p++) {
        *i = *p;
        i++;
    }
    /* add 'way' as well as ending NUL character */
    *i = 'w';     
    i++; *i = 'a';     
    i++; *i = 'y';   
    i++; *i = 0;
    return;
}