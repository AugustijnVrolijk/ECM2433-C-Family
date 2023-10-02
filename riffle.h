#ifndef RIFFLE_H_
#define RIFFLE_H_

void riffle_once(void *L, int len, int size, void *work); 
void riffle(void *L, int len, int size, int N);
int check_shuffle(void *L, int len, int size, int (*cmp)(void*, void*));
int compare_Int(void *A, void *B);
int compare_char(void *A, void *B); 
float quality(int *numbers, int len);
float average_quality(int N, int shuffles, int trials);


#endif