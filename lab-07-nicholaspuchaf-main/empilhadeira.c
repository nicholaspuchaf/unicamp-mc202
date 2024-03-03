
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef EMPILHADEIRA_H
#include "empilhadeira.h"
#endif

#ifndef PECA_H
#include "peca.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

#ifndef FILA_H
#include "fila.h"
#endif

int embalador_tem_peca(pilha *embalador)
{

    /*
        Está função verifica se o embalador possui uma peça em suas mãos!
        Retorna 1 se ele nao tem, logo pode pegar outra peça!
        Retorna 0 se está com as mãos ocupadas e não pode pegar outra peça!
    */

    if (embalador->tamanho_maximo != 1)
    {
        exit(3); // ERRO DEVE TER MAXIMO 1 DE TAMANHO
    }

    if (embalador->topo == NULL)
    {
        return 1; // Embalador pode pegar peça!
    }
    else
    {
        return 0; // Embalador ocupado!
    }
}

void embalador_pega_peca_pilha(pilha *pi, pilha *embalador)
{
    /*
        Nesta função o embalador pega outra peça da pilha!
    */

    no *ele = malloc(sizeof(no));
    ele->p = desempilhar(pi);
    ele->proximo = NULL;

    embalador->topo = ele;
}

void embalador_da_uma_embalada(pilha *embalador)
{
    diminui_tempo_embalagem(embalador->topo->p);
}

int peca_esta_pronta(pilha *embalador)
{
    /*
        Função verifica se a peça está pronta, retorna 1 se está pronta e 0 se não esta
    */
    if (verifica_tempo_embalagem(embalador->topo->p) == 1)
    {
        // ESTA PRONTA
        return 1;
    }
    return 0; // NAO ESTA
}

void embalador_envia_peca(pilha *embalador)
{
    /*
        Nesta função o embalador emvia a peça embora! (Destroi a peça!)
    */
    destroi_peca(embalador->topo->p);
    free(embalador->topo);

    embalador->topo = NULL;
}

int empilhadeira_embalador(pilha *pi, pilha *embalador)
{
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

    // verificar se o embalador tem peca nas maos

    if (embalador_tem_peca(embalador) == 1)
    {
        // Embalador pode pegar peça

        if (pi->topo != NULL)
        {
            // TEM PECA NA PILHA

            if (pi->topo->p->tempo_minimo_pilha == 0)
            {
                // Pode pegar a peça da pilha
                embalador_pega_peca_pilha(pi, embalador);

                // embalador_da_uma_embalada(embalador);

                if (peca_esta_pronta(embalador))
                {
                    embalador_envia_peca(embalador);

                    return 2; // Tem peça na pilha, mas nao nas maõs, pegou outra e enviou!
                }

                return 4; // Pegou outra pessa mas nao enviou
            }
            else if (pi->topo->p->tempo_minimo_pilha == 1)
            {
                // Tem que esperar um minuto ainda para pegar a peça!

                return -7; // Embalador esta livre, mas não pode pegar peça da pilha ainda!
            }
        }

        else if (pi->topo == NULL)
        {
            // Pilha esta vazia

            return -5; // Pilha e as maos do embalador estão vazias, nada foi feito!
        }
    }
    else if (embalador_tem_peca(embalador) == 0)
    {
        // Embalador está com as maos cheias!

        embalador_da_uma_embalada(embalador);

        if (peca_esta_pronta(embalador))
        {
            embalador_envia_peca(embalador);

            if (pi->topo != NULL)
            {
                // Tem peça na pilha

                if (pi->topo->p->tempo_minimo_pilha == 0)
                {
                    // PODE PEGAR A PEÇA já

                    embalador_pega_peca_pilha(pi, embalador);
                    return 1; // TERMINOU UMA PECA, ENVIOU E PEGOU OUTRA
                }
                // NAO PODE PEGAR A PECA NAO ESTA POSSIVEL DE PEGAR AINDA
            }

            return 8; // Embalador terminou sua peça e enviou, mas nao pegou outra!
        }

        return -3; // Não enviou peça mas coletou, sem enviar depois!
    }
    exit(9);
    return 9; // ALGO DEU ERRADO
}
