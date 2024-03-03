
#ifndef PECA_H
#include "peca.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef FILA_H
#include "fila.h"
#endif

fila *cria_lista(int tamanho_maximo)
{

    /*
        Cria um ponteiro de uma fila vazia que trabalha com vetor dinamico, porém o tamanho é predefinido durante a
        criação com o parametro int tamanho_maximo. Por isso não há mudança no tamanho do vetor ao longo do programa!
        Inicia o vetor de vetores (* peca) todos com NULL
        Retorna a o ponteiro da fila!
    */

    fila *f = malloc(sizeof(fila));
    f->tam_maximo = tamanho_maximo;
    f->indice = 0;
    f->vetor = malloc(tamanho_maximo * sizeof(peca));
    for (int i = 0; i < tamanho_maximo; i++)
    {
        f->vetor[i] = NULL;
    }
    return f;
}

void destruir_fila(fila *f)
{
    /*
        Destroi a fila e libera os valores alocados dentro do vetor e do vetor, bem como da lista! Não tem retorno!
    */

    if (f == NULL)
    {
        return;
    }

    for (int i = 0; i < f->tam_maximo; i++)
    {
        if (f->vetor[i] != NULL)
        {
            destroi_peca(f->vetor[i]);
        }
    }
    free(f->vetor);
    free(f);
}

void enfileira(fila *f, peca *p)
{
    /*
        Esta função coloca uma peça no "fim" da fila, recebe como parâmetro a fila e a peca, não há retorno!
    */

    if (f->tam_maximo <= f->indice)
    {
        exit(3);
    }

    f->vetor[f->indice] = p;

    f->indice++;
}

peca *desenfileira(fila *f)
{

    /*
        Esta função retira o elemento do "inicio" da fila e retorna a peca desejada!
        Recebe como parâmetro a apenas a fila!
        Retorna a peça que acabou de ser retirada da fila!
    */

    if (f->indice == -1)
    {
        // ESTA VAZIO
        printf("\nERRO FILA VAZIA\n");
        exit(1);
    }

    peca *p = f->vetor[0];

    int i = 1;

    for (i = 1; i < f->tam_maximo; i++)
    {
        f->vetor[i - 1] = f->vetor[i];
    }
    f->vetor[i - 1] = NULL;
    f->indice--;

    return p;
}

int fila_vazia(fila *f)
{
    /*
        Está função irá verificar se a fila esta vazia!
        Retorna 0 se está vazia e 1 se não está vazia!

    */
    if (f->vetor[0] == NULL)
        return 0;

    return 1;
}