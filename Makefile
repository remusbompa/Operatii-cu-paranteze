build: TStructuri.h functii.c main.c
	gcc functii.c main.c -Wall -g -o tema2

clean: 
	rm *.o tema2
