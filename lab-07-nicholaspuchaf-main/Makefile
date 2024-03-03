all: simulador
	rm empilhadeira.o
	rm esteira.o
	rm fila.o
	rm peca.o
	rm simulador.o
	rm pilha.o
	
simulador : simulador.o empilhadeira.o esteira.o fila.o pilha.o peca.o
	gcc simulador.o empilhadeira.o esteira.o fila.o pilha.o peca.o -lm -g -o simulador

simulador.o : simulador.c empilhadeira.h esteira.h fila.h pilha.h peca.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c simulador.c

empilhadeira.o : empilhadeira.c empilhadeira.h fila.h peca.h pilha.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c empilhadeira.c

esteira.o : esteira.c esteira.h fila.h peca.h pilha.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c esteira.c

fila.o : fila.c peca.h fila.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c fila.c

pilha.o :  pilha.c peca.h pilha.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c pilha.c

peca.o : peca.c peca.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c peca.c
