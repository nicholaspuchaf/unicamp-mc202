
#ifndef PECA_H
#include "peca.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pilha *cria_pilha(int tamanho_maximo)
{
    /*
        Esta função cria uma pilha vazia, com tamanho maximo pre definido de parametro int tamanho_maximo
        retorna o ponteiro desta pilha
    */

    pilha *pi = malloc(sizeof(pilha));
    pi->tamanho_maximo = tamanho_maximo;
    pi->topo = NULL;
    pi->utilizado = 0;
    return pi;
}

void empilhar(pilha *pi, peca *pe)
{
    /*
        Esta função recebe uma peca "pe" e coloca no topo da pilha! Nao retorna nada!
    */

    if (pi->tamanho_maximo == pi->utilizado)
    {
        printf("\nERRO AO EMPILHAR, SEM ESPAÇO - > TAMANHO MÁXIMO = %d\n", pi->tamanho_maximo);
        return;
    }

    no *n = malloc(sizeof(no));
    n->p = pe;
    n->proximo = pi->topo;
    pi->topo = n;
    pi->utilizado++;
}

peca *desempilhar(pilha *pi)
{

    /*
        Esta função retira a peca do topo da pilha! e retorna peça desejada!
        Realiza verificacao se a pilha esta vazia!
    */

    if (pi->topo == NULL)
    {
        printf("\nERRO PILHA VAZIA\n");
        exit(1);
    }

    peca *pe = pi->topo->p;
    no *ele = pi->topo;

    pi->topo = pi->topo->proximo;

    free(ele);
    pi->utilizado--;
    return pe;
}

void destruir_lista(no *n)
{
    /*
        Função utilizada para destruir a lista ligada que monta a pilha!
    */
    if (n != NULL)
    {

        destruir_lista(n->proximo);
        destroi_peca(n->p);
    }
}

void destruir_pilha(pilha *pi)
{
    /*
        Função destinada para destruir a pilha criada! Sem retorno!
    */

    if (pi == NULL)
    {
        return;
    }
    destruir_lista(pi->topo);
    free(pi);
}

int pilha_vazia(pilha *pi)
{
    /*
        Está função irá verificar se a pilha está vazia, retorna 1 se não está vazia, e 0 se está vazia!
    */

    if (pi->topo == NULL)
        return 0;
    return 1;
}

int pilha_tem_espaco(pilha *pi)
{
    /*
        Esta função irá verificar se tem espaço na pilha!
        Retorna 1 se tem espaço e 0 se não tem espaço!
    */

    if (pi->tamanho_maximo <= pi->utilizado)
    {
        return 0;
    }
    return 1;
}
