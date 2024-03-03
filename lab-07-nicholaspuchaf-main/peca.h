
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PECA_H

typedef struct peca peca;

struct peca
{

    int tamanho_peca; // 0 pequena, 1 media e 2 grande
    int tipo_peca;    // 1 ou 2

    int tempo_classificacao;
    int tempo_embalagem;
    int tempo_minimo_pilha;
};

peca *cria_peca(char entrada[10], int tipo);
/*
        Funcao cria uma peca de determinado tipo e tamanho a partir do parametro char *entrada_linha, que é a entrada
        lida pela funcao main!
        Retorna um ponteira para a peça!
    */
void classifica_tempo(peca *p);
/*
        Esta funcao classifica qual o tempo de classificacao da peça a partir do tamanho e tipo dela!
    */
int separa_tamanho(char entrada[10]);
/*
        Esta funcao determina qual o tamanho da peca a partir do parametro char *entrada, lido pela funcao main.
        Retorna valor int de acordo com o tamanho da peça!
    */
int separa_tipo(int tipo);
/*
        A partir do parâmtro entrada, a função determina qual o tipo da peça.
        O retorno é um valor inteiro de acordo com o tamanho da peça!
    */
void destroi_peca(peca *p);
/*
        Esta função destroi a peça alocada dinamicamente!
    */
void diminui_tempo_classificacao(peca *p);
/*
        Esta função diminui o tempo de classificacao da peca!
    */
void diminui_tempo_embalagem(peca *p);
/*
        Esta função diminui em 1 minuto o tempo restante de embalagem!
    */
int verifica_tempo_classificacao(peca *p);

int verifica_tempo_embalagem(peca *p);
