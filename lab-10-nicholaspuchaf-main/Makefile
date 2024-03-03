
cozinha: cozinha.o heap.o
	gcc cozinha.o heap.o -lm -g -o cozinha

cozinha.o: cozinha.c heap.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c cozinha.c

heap.o: heap.c heap.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c heap.c

