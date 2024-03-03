
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PECA_H
#include "peca.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef FILA_H
#include "fila.h"
#endif

#ifndef ESTEIRA_H
#include "esteira.h"
#endif

#ifndef EMPILHADEIRA_H
#include "empilhadeira.h"
#endif

int verifica_espaco_livre(fila *f, peca *p)
{
    /*
        Verifica se há espaço livre na esteira para que a maquina possa colocar uma peça na entrada!
        Os parâmetros são a fila e a entrada(vetor de char* lido pela main)!
        Retorna 0 se nao conseguiu colocar na esteira, e retorna 1 se conseguiu!
        Se há espaço na esteira será colocada uma nova peça, se não não realiza
    */

    if (f->indice == f->tam_maximo)
    {
        // NAO HÁ ESPAÇO NA ESTEIRA
        return 0;
    }
    else if (f->indice + 1 > f->tam_maximo)
    {
        exit(1);
    }
    else
    {
        // HÁ ESPAÇO NA ESTEIRA

        enfileira(f, p);
        return 1; // COLOCOU PEÇA
    }
}

int verifica_classificador_trabalhando(pilha *classficador)
{
    /*
        Esta função irá verificar se o classificador da esteira (criado a partir de uma pilha de tamanho maximo 1) possui as maos
        livres para classsificar outra peca!
        Pode pegar peça return 1.
        Possui peça nas mãos return 0.
    */

    if (classficador->tamanho_maximo != 1 || classficador->utilizado > 1)
    {
        exit(2);
    }

    if (classficador->topo == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void atualiza_status_peca(pilha *classificador)
{
    /*
        Esta funcao irá diminuir em 1 minuto o tempo de classificacao da peca que esta na mao do classificador no momento!
    */
    diminui_tempo_classificacao(classificador->topo->p);
}

int verifica_status_peca(pilha *classificador)
{

    /*
        Esta função verifica o status da peça, ou seja, se ela terminou de ser classificada e pode ser
        colocada na pilha!
        Retorna 1 se a peca esta pronta para entrar na pilha e 0 se ainda nao terminou
    */

    if (classificador->topo == NULL)
    {
        return 0; // SEM PECA NA MAOS
    }

    if (classificador->topo->p == NULL)
    {
        // O TOPO EXISTE MAS N TEM NADA!
        return 0;
    }

    if (verifica_tempo_classificacao(classificador->topo->p) == 1)
    {
        return 1; // ESTA PRONTO PARA COLOCAR A PECA NA PILHA
    }
    else
    {

        return 0; // PECA NAO ESTA PRONTA
    }
}

int verifica_tem_peca_na_esteira(fila *f)
{

    /*
        Esta funcao verifica se há peca na esteira para o classificador poder pegar para classificar!
        O retorno é 1 para tem peça e 0 para nao tem peca!
    */

    if (f->indice < 0)
    {
        exit(3);
    }

    if (f->vetor[0] != NULL && f->indice > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void classificador_pega_peca(fila *f, pilha *classificador)
{
    /*
        O classificador que trabalha na esteira pega uma peca da fila e "empilha em suas maos"
    */

    peca *p = desenfileira(f);

    empilhar(classificador, p);
}

void colocar_na_pilha(pilha *classificador, pilha *pilha_caixas)
{
    /*
        Classificador coloca a peca que esta em suas maos no topo da pilha de caixas!
    */

    peca *pe = desempilhar(classificador);
    empilhar(pilha_caixas, pe);
}

int classificador_esteira(fila *f, pilha *classificador, pilha *pilha_caixas)
{

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

    // VERIFICAR SE ELE NAO ESTA CLASSIFICANDO NO MOMENTO

    if (verifica_classificador_trabalhando(classificador) == 0)
    {
        // COM PECA NA MAO
        if (verifica_status_peca(classificador) == 1)
        {
            // PECA ESTA PRONTA

            // VERIFICAR SE A PILHA TEM ESPAÇO
            if (pilha_tem_espaco(pilha_caixas) == 1)
            {
                colocar_na_pilha(classificador, pilha_caixas);

                if (verifica_tem_peca_na_esteira(f) == 1)
                {
                    classificador_pega_peca(f, classificador);
                    return 2; // COLOCOU PECA NA PILHA MAS PEGOU OUTRA PECA DA ESTEIRA
                }

                return 1; // COLOCOU PECA NA PILHA MAS NAO PEGOU OUTRA PECA
            }
            else
            {
                return -4; // TERMINOU A PECA MAS NA PODE COLOCAR NA PILHA
            }
        }
        else
        {
            // PECA NAO ESTA PRONTA
            atualiza_status_peca(classificador);

            if (verifica_status_peca(classificador) == 1)
            {
                // PECA ESTA PRONTA

                // VERIFICA PECA NA PILHA
                if (pilha_tem_espaco(pilha_caixas) == 0)
                {
                    // NAO TEM ESPACO
                    return -3; // PECA PRONTA MAS N PODE COLOCAR NA PILHA
                }
                else
                {
                    colocar_na_pilha(classificador, pilha_caixas);

                    if (verifica_tem_peca_na_esteira(f) == 1)
                    {
                        classificador_pega_peca(f, classificador);
                        return 2; // COLOCOU PECA NA PILHA MAS NAO PEGOU OUTRA PECA DA ESTEIRA
                    }

                    return 1; // COLOCOU PECA NA PILHA E PEGOU OUTRA PECA
                    // TEM ESPACO PILHA
                }
            }
            else
            {
                return 0; // PECA NAO ESTA PRONTA
            }
        }
    }

    else
    {

        // MAOS LIVRES

        if (verifica_tem_peca_na_esteira(f) == 1)
        {
            // TEM PECA

            classificador_pega_peca(f, classificador);
            // atualiza_status_peca(classificador);

            return -1; // NAO COLOCOU PECA NA PILHA MAS PEGOU OUTRA PECA
        }
        else
        {
            // printf("Não há peça na esteira!\n");
            return -2; // NAO COLOCOU PECA NA PILHA NEM PEGOU OUTRA
            // NAO TEM PECA
        }
    }
}
