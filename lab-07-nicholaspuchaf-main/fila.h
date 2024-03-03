

#ifndef PECA_H
#include "peca.h"
#endif

#define FILA_H

typedef struct no no;
typedef struct fila fila;

struct fila
{
    peca **vetor;
    int tam_maximo;
    int indice;
};

fila *cria_lista(int tamanho_maximo);
/*
        Cria um ponteiro de uma fila vazia que trabalha com vetor dinamico, porém o tamanho é predefinido durante a
        criação com o parametro int tamanho_maximo. Por isso não há mudança no tamanho do vetor ao longo do programa!
        Inicia o vetor de vetores (* peca) todos com NULL
        Retorna a o ponteiro da fila!
    */
void destruir_fila(fila *f);
/*
        Destroi a fila e libera os valores alocados dentro do vetor e do vetor, bem como da lista! Não tem retorno!
    */
void enfileira(fila *f, peca *p);
/*
        Esta função coloca uma peça no "fim" da fila, recebe como parâmetro a fila e a peca, não há retorno!
    */
peca *desenfileira(fila *f);
/*
        Esta função retira o elemento do "inicio" da fila e retorna a peca desejada!
        Recebe como parâmetro a apenas a fila!
        Retorna a peça que acabou de ser retirada da fila!
    */
int fila_vazia(fila *f);
/*
        Está função irá verificar se a fila esta vazia!
        Retorna 0 se está vazia e 1 se não está vazia!

    */