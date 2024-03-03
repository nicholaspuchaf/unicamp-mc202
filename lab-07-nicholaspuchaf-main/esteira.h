
#define ESTEIRA_H

#ifndef PECA_H
#include "peca.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef FILA_H
#include "fila.h"
#endif

int verifica_espaco_livre(fila *f, peca *p);
/*
        Verifica se há espaço livre na esteira para que a maquina possa colocar uma peça na entrada!
        Os parâmetros são a fila e a entrada(vetor de char* lido pela main)!
        Retorna 0 se nao conseguiu colocar na esteira, e retorna 1 se conseguiu!
        Se há espaço na esteira será colocada uma nova peça, se não não realiza
    */

int verifica_classificador_trabalhando(pilha *classificador);
/*
        Esta função irá verificar se o classificador da esteira (criado a partir de uma pilha de tamanho maximo 1) possui as maos
        livres para classsificar outra peca!
        Pode pegar peça return 1.
        Possui peça nas mãos return 0.
    */
void atualiza_status_peca(pilha *classificiador);
/*
        Esta funcao irá diminuir em 1 minuto o tempo de classificacao da peca que esta na mao do classificador no momento!
    */
int verifica_status_peca(pilha *classificador);
/*
        Esta função verifica o status da peça, ou seja, se ela terminou de ser classificada e pode ser
        colocada na pilha!
        Retorna 1 se a peca esta pronta para entrar na pilha e 0 se ainda nao terminou
    */
int verifica_tem_peca_na_esteira(fila *f);
/*
        Esta funcao verifica se há peca na esteira para o classificador poder pegar para classificar!
        O retorno é 1 para tem peça e 0 para nao tem peca!
    */
void classificador_pega_peca(fila *f, pilha *classificador);
/*
        O classificador que trabalha na esteira pega uma peca da fila e "empilha em suas maos"
    */
void colocar_na_pilha(pilha *classificador, pilha *pilha_caixas);
/*
        Classificador coloca a peca que esta em suas maos no topo da pilha de caixas!
    */
int classificador_esteira(fila *f, pilha *classificador, pilha *pilha_caixas);
/*
        Esta é a função principal da esteira que conecta o classificador com a esteira e com a pilha de caixas.

        Irá verificar se o classificador terminou, se tem peca para pegar na esteira, se a pilha esta vazia para
        colocar mais uma peça!
        Possui varios retornos:
        1 - se colocou peca na pilha e pegou outra peca
        2 - se colocou peca na pilha mas nao pegou outra peca
        0 - se nao colocou peca na pilha porque a peca nao esta pronta
        -1 - nao possui peca nas maos mas pegou outra peca
        -2 - nao possui peca nas maos e nem pegou outra!
        -3 - peca pronta mas pilha sem espaco
    */