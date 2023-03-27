CC = gcc
std = C99

all: single byn 

single: single.o beggar.o shuffle/shuffle.o
	gcc -o single single.o beggar.o shuffle/shuffle.o -lgsl -lgslcblas -lm

byn: byn.o beggar.o shuffle/shuffle.o
	gcc -o byn byn.o beggary.o shuffle/shuffle.o -lgsl -lgslcblas -lm
