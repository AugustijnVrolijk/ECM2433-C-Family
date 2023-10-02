all: single byn test_pig piglatin quality demo_shuffle
 
test_pig: test_pig.o
	gcc -ansi test_pig.o pig.c -o test_pig

test_pig.o:
	gcc -ansi -c test_pig.c -o test_pig.o

piglatin: piglatin.o
	gcc -ansi piglatin.o pig.c -o piglatin
	
piglatin.o:
	gcc -ansi -c piglatin.c -o piglatin.o

demo_shuffle: demo_shuffle.o
	gcc -ansi demo_shuffle.o riffle.c -o demo_shuffle

demo_shuffle.o:
	gcc -ansi -c demo_shuffle.c -o demo_shuffle.o

quality: quality.o
	gcc -ansi quality.o riffle.c -o quality

quality.o:
	gcc -ansi -c quality.c -o quality.o

single: single.o
	gcc -ansi single.o riffle.c beggar.c -o single

single.o: single.c
	gcc -ansi -c single.c -o single.o

byn: byn.o
	gcc -ansi byn.o riffle.c beggar.c -o byn

byn.o: byn.c
	gcc -ansi -c byn.c -o byn.o