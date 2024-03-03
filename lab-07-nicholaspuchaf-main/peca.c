
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "peca.h"

peca *cria_peca(char entrada[10], int tipo)
{
    /*
        Funcao cria uma peca de determinado tipo e tamanho a partir do parametro char *entrada_linha, que é a entrada
        lida pela funcao main!
        Retorna um ponteira para a peça!
    */

    peca *p = NULL;
    p = malloc(sizeof(peca));

    p->tamanho_peca = separa_tamanho(entrada);
    p->tipo_peca = tipo;
    classifica_tempo(p);
    p->tempo_minimo_pilha = 0;
    return p;
}

void classifica_tempo(peca *p)
{
    /*
        Esta funcao classifica qual o tempo de classificacao da peça a partir do tamanho e tipo dela!
    */

    if (p->tamanho_peca == 0)
    {
        p->tempo_classificacao = 1;

        if (p->tipo_peca == 1)
        {
            p->tempo_embalagem = 1;
        }
        else
        {
            p->tempo_embalagem = 2;
        }
    }

    if (p->tamanho_peca == 1)
    {
        p->tempo_classificacao = 2;

        if (p->tipo_peca == 1)
        {
            p->tempo_embalagem = 2;
        }
        else
        {
            p->tempo_embalagem = 3;
        }
    }
    if (p->tamanho_peca == 2)
    {
        p->tempo_classificacao = 3;

        if (p->tipo_peca == 1)
        {
            p->tempo_embalagem = 2;
        }
        else
        {
            p->tempo_embalagem = 3;
        }
    }

    if (p->tempo_classificacao <= 0 || p->tempo_classificacao > 4 || p->tempo_embalagem <= 0 || p->tempo_embalagem > 4)
    {
        exit(3);
    }
}

int separa_tamanho(char entrada[10])
{
    /*
        Esta funcao determina qual o tamanho da peca a partir do parametro char *entrada, lido pela funcao main.
        Retorna valor int de acordo com o tamanho da peça!
    */

    if (entrada[0] == 'g')
    {
        return 2;
    }
    if (entrada[0] == 'm')
    {
        return 1;
    }
    if (entrada[0] == 'p')
    {
        return 0;
    }

    exit(2);
    return -1;
}

int separa_tipo(int tipo)
{
    /*
        A partir do parâmtro entrada, a função determina qual o tipo da peça.
        O retorno é um valor inteiro de acordo com o tamanho da peça!
    */
    return 0;
}

void destroi_peca(peca *p)
{
    /*
        Esta função destroi a peça alocada dinamicamente!
    */
    free(p);
}

void diminui_tempo_classificacao(peca *p)
{
    /*
        Esta função diminui o tempo de classificacao da peca!
    */
    p->tempo_classificacao--;
}

void diminui_tempo_embalagem(peca *p)
{
    /*
        Esta função diminui em 1 minuto o tempo restante de embalagem!
    */
    p->tempo_embalagem--;
}

int verifica_tempo_classificacao(peca *p)
{
    return p->tempo_classificacao == 0 ? 1 : 0;
}

int verifica_tempo_embalagem(peca *p)
{
    return p->tempo_embalagem == 0 ? 1 : 0;
}
