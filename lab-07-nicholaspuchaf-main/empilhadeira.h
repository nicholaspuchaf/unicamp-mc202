#define EMPILHADEIRA_H

#ifndef PECA_H
#include "peca.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef FILA_H
#include "fila.h"
#endif

int embalador_tem_peca(pilha *embalador);
/*
        Está função verifica se o embalador possui uma peça em suas mãos!
        Retorna 1 se ele nao tem, logo pode pegar outra peça!
        Retorna 0 se está com as mãos ocupadas e não pode pegar outra peça!
    */

void embalador_pega_peca_pilha(pilha *pi, pilha *embalador);
/*
        Nesta função o embalador pega outra peça da pilha!
    */
void embalador_da_uma_embalada(pilha *embalador);
/*
        Função verifica se a peça está pronta, retorna 1 se está pronta e 0 se não esta
    */
int peca_esta_pronta(pilha *embalador);
/*
        Nesta função o embalador emvia a peça embora! (Destroi a peça!)
    */
void embalador_envia_peca(pilha *embalador);

int empilhadeira_embalador(pilha *pi, pilha *embalador);
/*
        Está é a função principal do embalador que gerencia as ações dele, desde trabalhar em uma peça, pegar outra e enviar a que já terminou.
        Retornos
        1 Terminou a peça e pegou outra!
        2 Pegou uma peça, já terminou e já enviou!
        4 Pegou outra peça mas n enviou!
        8 Terminou sua peça, enviou mas n pegou outra
        9 Erro no programa quebra o programa!
        -3 Pegou outra peça, mas n enviou nada!
        -5 Embalador n tem peça, mas pilha tambem nao tem!
        -7 Pode pegar outra peça da pilha, mas a pilha n deixa porque tem q ficar pelo menos 1 minuto na pilha!

    */