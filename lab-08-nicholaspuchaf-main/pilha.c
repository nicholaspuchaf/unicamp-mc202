
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef ARVORE_H
#include "arvore.h"
#endif

pilha *cria_pilha()
{
    /*
        Esta funcão cria um pilha vazia de tamanho zero, retorna o ponteira para tal pilha!
    */

    pilha *p = malloc(sizeof(pilha));
    p->tamanho = 0;
    p->topo = NULL;
    return p;
}

void empilhar(pilha *p, no *item)
{
    /*
        Esta funcão empilha um "nó da árvore binária" dentro da pilha!
    */
    no_pilha *n_p = malloc(sizeof(no_pilha));

    n_p->dado = item;

    n_p->prox = p->topo;
    p->topo = n_p;
    p->tamanho++;
}

no *desempilhar(pilha *p)
{
    /*
        Esta funcão desempilha o ultimo item da pilha, ele recebe a pilha como parâmetro e retorna
        um "nó" da arvore, porque este nó da arvore binária é o dado que a pilha quarda em seus nós
        (chamados de no_pilha).
    */

    no_pilha *n_p = p->topo;

    no *n = n_p->dado;

    p->topo = n_p->prox;
    free(n_p);

    p->tamanho--;
    return n;
}

void destruir_lista(no_pilha *n_p)
{
    /*
        Está funcão destroi a lista de raizes da arvore, cada no seria uma arvore binaria.
        Neste programa em geral terá apenas um nó com a arvore binária!
        Esse TAD é mais útil para construir a arvore binária!
    */

    if (n_p == NULL)
    {
        return;
    }

    destruir_raiz(n_p->dado);
    destruir_lista(n_p->prox);
    free(n_p);
}

void destruir_pilha(pilha *p)
{
    /*
        Esta funcão destroi a pilha!
    */
    if (p == NULL)
    {
        return;
    }

    destruir_lista(p->topo);
    free(p);
}
