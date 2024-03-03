#include <stdlib.h>
#include <stdio.h>
#include "circuito.h"

circuito leitura_dados_circuito(int num_jog)
{
    /*
        Está funcao irá ler o numero de indentificacao do circuito e colocar as jogadas no vetor
    */

    circuito circuito1;

    circuito1.num_jogadores = num_jog;
    circuito1.total_jogadas_circuito = 0;

    scanf(" %d", &circuito1.identificacao_do_circuito);

    circuito1.jogadas_dos_participantes = malloc(circuito1.num_jogadores * sizeof(int));

    if (circuito1.jogadas_dos_participantes == NULL)
    {
        printf("Nao ha memoria suficiente!\n");
        exit(1);
    }

    for (int i = 0; i < num_jog; i++)
    {
        // MAXIMO DE JOGADAS POR PARTICIPANTES DEVE SER 9
        scanf(" %d", (circuito1.jogadas_dos_participantes + i));

        // SOMA AS JOGADAS JÀ, COLOCAR DENTRO DESSA FUNCAO PARA ECONOMIZAR UM FOR LOOP

        circuito1.total_jogadas_circuito += *(circuito1.jogadas_dos_participantes + i);
    }
    return circuito1;
}

void free_circuito(circuito circuito1)
{
    /*
        Liberar da memoria o vetor dinamico jogada_dos_participantes
    */
    free(circuito1.jogadas_dos_participantes);
}
