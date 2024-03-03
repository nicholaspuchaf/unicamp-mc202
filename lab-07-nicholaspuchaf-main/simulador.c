
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef PECA_H
#include "peca.h"
#endif

#ifndef FILA_H
#include "fila.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef ESTEIRA_H
#include "esteira.h"
#endif

#ifndef EMPILHADEIRA_H
#include "empilhadeira.h"
#endif

void impressao(int minutagem, int controle_embalador, int controle_classificador, int controle_esteira)
{
    /*
        Está função irá realizar a impressão do relatório minuto a minuto!
    */
    int embalagem1 = 0, embalagem2 = 0, classificacao1 = 0, classificacao2 = 0;

    // EMBALAGEM

    if (controle_embalador == 8)
    {

        embalagem2 = 1;
    }
    else if (controle_embalador == -3)
    {

        embalagem2 = 0;
    }
    else if (controle_embalador == 1)
    {
        embalagem2 = 1;
    }
    else if (controle_embalador == -5)
    {
        embalagem2 = 0;
    }
    else if (controle_embalador == 2)
    {
        embalagem2 = 1;
    }
    else if (controle_embalador == 4)
    {
        embalagem2 = 0;
    }
    else if (controle_embalador == -7)
    {
        embalagem2 = 0;
    }

    // CLASSIFICACAO

    if (controle_classificador == 1)
    {
        classificacao2 = 1;
        embalagem1 = 1;
    }
    else if (controle_classificador == 2)
    {
        classificacao2 = 1;
        embalagem1 = 1;
    }
    else if (controle_classificador == 0)
    {
        classificacao2 = 0;
    }
    else if (controle_classificador == -1)
    {
        classificacao2 = 0;
    }
    else if (controle_classificador == -2)
    {
        classificacao2 = 0;
    }
    else if (controle_classificador == -4)
    {
        classificacao2 = 0;
    }

    if (controle_esteira == 1)
    {
        classificacao1 = 1;
    }
    else
    {
        classificacao1 = 0;
    }

    printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", minutagem, classificacao1, classificacao2, embalagem1, embalagem2);
}

int main()
{

    // O QUE A FUNCAO DEVE FAZER

    int tamEsteira = 0, tamPilha = 0;
    scanf("%d %d", &tamEsteira, &tamPilha);
    int numEntradas = 0;
    scanf("%d", &numEntradas);

    /*
        Definição dos trabalhadores, da pilha e da esteira!
    */

    pilha *pilha_principal = cria_pilha(tamPilha);

    fila *esteira = cria_lista(tamEsteira);

    pilha *embalador = cria_pilha(1);

    pilha *classificador = cria_pilha(1);

    int i = 0;
    int minutagem = 0;
    int minutagemAtraso = 0;
    char entrada[10];
    int tipo;
    printf("##### Simulação\n");

    int controle_embalador = 0;
    int controle_classificador = 0;
    int controle_esteira = 0;

    while (i < numEntradas)
    {
        scanf("%s %d", entrada, &tipo); // LEITURA DA PECA
        i++;

        peca *p = cria_peca(entrada, tipo); // CRIACAO DA PEÇA

        // O EMBALADOR DEVE TENTAR FAZER SEU TRABALHO

        controle_embalador = empilhadeira_embalador(pilha_principal, embalador);

        // O CLASSIFICADOR DEVE TENTAR FAZER SEU TRABALHO

        controle_classificador = classificador_esteira(esteira, classificador, pilha_principal);

        // DEPOIS ADICIONA CAIXA NA ESTEIRA, SEM NAO TIVER ESPAçO ATRASA 1 MINUTO

        controle_esteira = verifica_espaco_livre(esteira, p);

        if (controle_esteira == 0)
        {
            // NAO HOUVE ESPACO NA ESTEIRA HAVERÁ ATRASO

            while (controle_esteira == 0)
            {
                minutagem++;
                impressao(minutagem, controle_embalador, controle_classificador, controle_esteira);
                minutagemAtraso++;

                controle_embalador = empilhadeira_embalador(pilha_principal, embalador);
                controle_classificador = classificador_esteira(esteira, classificador, pilha_principal);

                controle_esteira = verifica_espaco_livre(esteira, p);
            }
        }

        // IMPRESSAO DA RODADA
        minutagem++;

        impressao(minutagem, controle_embalador, controle_classificador, controle_esteira);
    }

    controle_esteira = 0;

    /*
        Terminou a fase de inserção de peças irá verificar as peças que sobraram na esteira, na pilha e nos trabalhadores!
    */

    while (fila_vazia(esteira) || pilha_vazia(pilha_principal) || pilha_vazia(classificador) || pilha_vazia(embalador))
    {

        controle_embalador = empilhadeira_embalador(pilha_principal, embalador);
        controle_classificador = classificador_esteira(esteira, classificador, pilha_principal);

        minutagem++;
        impressao(minutagem, controle_embalador, controle_classificador, controle_esteira);
    }

    printf("Tempo atraso: %d.\n", minutagemAtraso);

    destruir_pilha(pilha_principal);
    destruir_pilha(embalador);
    destruir_pilha(classificador);
    destruir_fila(esteira);

    return 0;
}
