#ifndef ARVORE_H
#include "arvore.h"
#endif

#define PILHA_H
// VAMO VER SE VAI
typedef struct no_pilha no_pilha;

struct no_pilha
{
    no *dado;
    no_pilha *prox;
};

typedef struct pilha
{
    no_pilha *topo;
    int tamanho;
} pilha;

pilha *cria_pilha();

void empilhar(pilha *p, no *item);

no *desempilhar(pilha *p);

void destruir_pilha(pilha *p);