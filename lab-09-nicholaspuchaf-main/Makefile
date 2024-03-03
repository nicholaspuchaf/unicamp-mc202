
dracarys: dracarys.o arvore_rb.o
	gcc dracarys.o arvore_rb.o -lm -g -o dracarys
	
dracarys.o: dracarys.c arvore_rb.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c dracarys.c

arvore_rb.o: arvore_rb.c arvore_rb.h
	gcc -std=c99 -Wall -Werror -Wvla -g -c arvore_rb.c
