#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "riffle.h"

/** A function which riffles an array once
 * 
 * @param L a pointer to an array of elements to riffle shuffle
 * @param len the number of elements in the array
 * @param size the size of a single element in the array (type)
 * @param work a pointer to an array to use to work in
 */
void riffle_once(void *L, int len, int size, void *work) {

    /* Initialise pointers and seed rand() with time(NULL)
    pointers leftP and rightP are used to split the deck into 2 halves*/
    void *end = (void *)((char *)L + (len * size));
    void *midPoint = (void *)((char *)L + (len * size) / 2);
    void *leftP = L;
    void *rightP = midPoint;
    srand(time(NULL));

    /*  malloc memory for the working array based on the size of the original array*/
    if (!(work = malloc(len * size))) {
        printf("failed to malloc work array\n");
        exit(1);
    }
    void *workP = work;

    /* riffle shuffle randomly until either the first half or 2nd half is fully used*/
    while (leftP < midPoint && rightP < end) {

        if (rand() % 2 == 0) {
            memcpy(workP, leftP, size);
            workP = (char *)workP + size;
            leftP = (char *)leftP + size;
        } else {
            memcpy(workP, rightP, size);
            workP = (char *)workP + size;
            rightP = (char *)rightP + size;
        }
    /* add remaining cards of first half if any are left */
    }
    while (leftP < midPoint) {
        memcpy(workP, leftP, size);
        workP = (char *)workP + size;
        leftP = (char *)leftP + size;
    }
    /* add remaining cards of second half if any are left */
    while (rightP < end) {
        memcpy(workP, rightP, size);
        workP = (char *)workP + size;
        rightP = (char *)rightP + size;
    }

    /* copy riffle shuffled deck back into the original array */
    workP = work;
    leftP = L;
    int j = 0;
    for (j; j < len; j++) {
        memcpy(leftP, workP, size);
        workP = (char *)workP + size;
        leftP = (char *)leftP + size;
    }
    free(work);
    return;
}

/** A function which riffles an array multiple times
 * 
 * @param L a pointer to an array of elements to riffle shuffle
 * @param len the number of elements in the array
 * @param size the size of a single element in the array (type)
 * @param N the number of times to riffle shuffle the array
 */
void riffle(void *L, int len, int size, int N) {
    void *work = NULL;
    for (N; N > 0; N--)
    {
        riffle_once(L, len, size, work);
    }
    return;
}

/** A function which checks if the values of two integer pointers are the same
 * 
 * @param a a integer pointer to an element in an array
 * @param b a integer pointer to an element in an array
 *  
 * @returns 0 if they are the same, 1 if the first pointer is larger, -1 if its smaller
 */
int compare_Int(void* a, void* b) {
    /* assign temporary pointers to int type */
    int* x = (int*)a;
    int* y = (int*)b;
    if (*x == *y) {
        return 0;
    } else if (*x > *y) {
        return 1;
    } else {
        return -1;
    }
}

/** A function which checks if the values of two char pointers are the same
 * 
 * @param a a char pointer to an element in an array
 * @param b a char pointer to an element in an array
 * 
 * @returns 0 if they are the same, 1 if the first pointer is larger, -1 if its smaller
 */
int compare_char(void* a, void* b) {
    /* assign temporary pointers to char type */
    char* x = (char*)a;
    char* y = (char*)b;
    if (*x == *y) {
        return 0;
    } else if (*x > *y) {
        return 1;
    } else {
        return -1;
    }
}

/** A function which checks if the values of two char pointers are the same
 * 
 * @param L a pointer to an array of elements to test riffle shuffle
 * @param len the number of elements in the array
 * @param size the size of a single element in the array (type)
 * @param cmp a pointer to the corresponding compare function depending on the type of the array L
 * supported types are int and char
 * 
 * @returns 1 if they contain the same elements, 0 if not
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void*, void*)) {

    /* Allocate memory for a copy of the original array */
    void *copy;
    if (!(copy = malloc(len * size))) {
        printf("failed to malloc copy array\n");
        exit(1);
    }
    memcpy(copy, L, len * size);

    /* Shuffle the copied array */
    void *work = NULL;
    riffle_once(copy, len, size, work);

    /* Check that all elements in the original array are present in the copied shuffled array */
    int i, j;
    void *current;
    int found;
    /* iterate through members of original list*/
    for (i = 0; i < len; i++) {
        current = (void *)((char *)L + (i * size));
        found = 0;
        /* iterate through members of copied list and compare if element is found in the orignal array*/
        for (j = 0; j < len; j++) {
            if (cmp(current, (void *)((char *)copy + (j * size))) == 0) {
                found = 1;
                break;
            }
        }
        if (found != 1) {
            /* Element not found in shuffled array - breaking */
             free(copy);
            return 0;
        }
    }

    /* Check that all elements in the copied shuffled array are present in the original array 
    its necessary to check both ways as one list could be a sublist of the other.
    i.e. if copied list was [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1], each element would be inside the original list [1,2,3,4,5]
    but not vice versa*/

    /* iterate through members of copied shuffled list*/
    for (i = 0; i < len; i++) {
        current = (void *)((char *)copy + i * size);
        found = 0;
        /* iterate through members of original list and compare if element is found in the copied shuffled array*/
        for (j = 0; j < len; j++) {
            if (cmp(current, (void *)((char *)L + j * size)) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            /* Element not found in original array */
            free(copy);
            return 0;
        }
    }
    free(copy);
    
    /* All elements found in both arrays, shuffle is correct */
    return 1;
}

/** a function which compares the ratio at which a consecutive element in a 
 *  riffle shuffled array is greater than its predecessor
 * 
 * @param numbers a pointer to an array of numbers
 * @param len number of elements in the numbers array
 * 
 * @returns float representing the ratio of consecutive elements greater than their predecessor
  */
float quality(int *numbers, int len) {

    /* iterate through sorted array - check if 2 consecutive elements are greater than each other */
    int greaterThan = 0;
    int i = 0;
    for (i; i < len-1; i++) {
        if (numbers[i] < numbers[i+1]) {
            greaterThan++;
        }
    }

    /* calculate ratio of pairs greater than each other 
    len-1 used as only 19 comparisons are made for an array of 20 elements*/
    
    float qualityParam = (float)greaterThan/(len-1);
    return qualityParam;
}

/** average_quality calculates the quality of shuffling an array over a certain number of trials and shuffling the array
 * a certain amount of times
 * 
 * @param N int representing size of array to create and test
 * @param shuffles number of times to shuffle array
 * @param trials number of times to measure the quality of the shuffling
 * 
 * @returns float representing the average quality of the shuffling of an array over a certain number of trials
  */
float average_quality(int N, int shuffles, int trials)  {
    /* malloc memory for numbers array */
    int *numbers = NULL;
     if (!(numbers = (int *)malloc(N * sizeof(int)))) {
        printf("failed to malloc memory for numbers array\n");
        exit(1);
    }
    

    float sum_quality = 0.0;
    int i, j;
    for (i = 0; i < trials; i++) {
        
        /* fill numbers array with ascending numbers from 0 to N-1 
        reset it back to the same state between trials*/
        for (j = 0; j < N; j++) {
            numbers[j] = j;
        }

        /* shuffle the array  */
        riffle(numbers, N, sizeof(int), shuffles); 
        sum_quality += quality(numbers, N);
    }
    free(numbers);  
    float average_quality_ratio = (float)sum_quality/trials;

    return average_quality_ratio;
}
