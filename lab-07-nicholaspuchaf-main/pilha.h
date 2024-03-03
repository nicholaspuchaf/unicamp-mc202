
#define PILHA_H

#ifndef PECA_H
#include "peca.h"
#endif

typedef struct no no;
typedef struct pilha pilha;

struct no
{

    peca *p;
    no *proximo;
};

struct pilha
{

    int tamanho_maximo;
    int utilizado;
    no *topo;
};

pilha *cria_pilha(int tamanho_maximo);
/*
        Esta função cria uma pilha vazia, com tamanho maximo pre definido de parametro int tamanho_maximo
        retorna o ponteiro desta pilha
    */
void empilhar(pilha *pi, peca *pe);
/*
        Esta função recebe uma peca "pe" e coloca no topo da pilha! Nao retorna nada!
    */
peca *desempilhar(pilha *pi);
/*
        Esta função retira a peca do topo da pilha! e retorna peça desejada!
        Realiza verificacao se a pilha esta vazia!
    */
void destruir_lista(no *n);
/*
        Função utilizada para destruir a lista ligada que monta a pilha!
    */
void destruir_pilha(pilha *pi);
/*
        Função destinada para destruir a pilha criada! Sem retorno!
    */
int pilha_vazia(pilha *pi);
/*
        Está função irá verificar se a pilha está vazia, retorna 1 se não está vazia, e 0 se está vazia!
    */
int pilha_tem_espaco(pilha *pi);
/*
        Esta função irá verificar se tem espaço na pilha!
        Retorna 1 se tem espaço e 0 se não tem espaço!
    */