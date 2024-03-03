
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef ARVORE_H
#include "arvore.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

no *cria_arvore(char dado, int tipo_dado, no *filho_esq, no *filho_dir)
{

    /*
        Cria uma arvore binária, guardando o dado na raiz, e coloca os parâmetros como folhas da nova
        árvore!
        Retorna a nova árvore binária!
        Recebe como parâmtro: dado que é o dado da própria raiz, o int tipo_dado que identifica se é um nó novo ou
        antigo, no* filho_esq, no* filho_dir são as outras árvores adicionadas na folha da nova árvore.
    */

    no *raiz = malloc(sizeof(no));

    raiz->dado = dado;
    raiz->tipo_dado = tipo_dado;
    raiz->filho_esq = filho_esq;
    raiz->filho_dir = filho_dir;

    return raiz;
}

void destruir_raiz(no *raiz)
{

    /*
        Está funcão destroi uma árvore binária, recebe uma raiz como parâmetro!
        É um funcão recursiva!
    */

    if (raiz == NULL)
    {
        return;
    }

    destruir_raiz(raiz->filho_esq);
    destruir_raiz(raiz->filho_dir);

    free(raiz);
}
