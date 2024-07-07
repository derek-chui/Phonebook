lab10:	lab10.h main10.c list10.c file10.c binary10.c
		gcc -std=c99 -pthread -o lab10 main10.c list10.c file10.c binary10.c
		./lab10 output output.bin 200