
#ifndef HEAP_H
#include "heap.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rodada(Heap *h, int num_panelas, int rodada_counter)
{
    /*
        Esta funcao executa uma rodada do chef, tem retorno int em que 1 significa que deve continuar e 0 se deve interromper a entrada
        de novos pratos no programa e encaminhar para o final.
    */
    int num;
    scanf("%d", &num);

    if (num == 0)
    {
        return 1;
    }

    for (int i = 0; i < num; i++)
    {

        char linha[3 * MAX];
        scanf("\n");
        fgets(linha, 3 * MAX, stdin);

        if (linha[0] == 'n')
        {

            /* ADICIONAR - executa a funcao de adicionar pratos no heap */

            int id = 0;
            char prato[MAX];
            char tipo[MAX];

            sscanf(linha, "%s %d %[^\n]", tipo, &id, prato);

            Item item;

            for (int i = 0; i < MAX; i++)
            {
                item.nome[i] = '\0';
                item.prato[i] = '\0';
            }

            item.id = id;

            item.chave = h->ids[id].chave;
            strcpy(item.prato, prato);
            strcpy(item.nome, h->ids[id].nome);

            insere(h, item);
        }
        if (linha[0] == 'a')
        {
            /* ALTERAR - executa a alteracao de prioridade de um prato no heap */
            int id = 0;
            int valor = 0;
            char tipo[MAX];

            sscanf(linha, "%s %d %d", tipo, &id, &valor);

            muda_prioridade(h, h->ids[id].endereco_heap, valor);

            /* ALTERAR */
        }
    }

    /* Ao final da rodada realiza a impressao dos pratos feitos ao longo da rodada! */

    printf("---- rodada %d ----\n", rodada_counter);

    for (int i = 0; i < num_panelas; i++)
    {

        Item item = extrai_maximo(h);
        printf("%s %s %d\n", item.nome, item.prato, item.chave);
    }

    return 0;
}

int main()
{

    int num_panelas = 0;
    int sobreviventes = 0;

    scanf("%d %d\n", &num_panelas, &sobreviventes);

    Heap *h = cria_heap(sobreviventes);

    for (int i = 0; i < sobreviventes; i++)
    {
        char linha[3 * MAX];
        fgets(linha, 3 * MAX, stdin);

        char nome[MAX * 2];
        char sobrenome[MAX];
        int chave = 0;

        sscanf(linha, "%s %s %d", nome, sobrenome, &chave);

        int id = i;
        h->ids[id].chave = chave;

        strcat(nome, " ");
        strcat(nome, sobrenome);
        strcpy(h->ids[id].nome, nome);
        h->ids[id].endereco_heap = -1;
    }
    int rodada_counter = 0;
    while (1)
    {
        /* Executadas todas as rodadas desejadas */
        rodada_counter++;

        int controle = rodada(h, num_panelas, rodada_counter);

        if (controle == 1)
        {
            break;
        }
    }

    while (h->n > 0)
    {
        /* Ao fim das entradas de novos pratos, agora são finalizados e impressos os restantes!  */
        printf("---- rodada %d ----\n", rodada_counter);
        rodada_counter++;
        for (int i = 0; i < num_panelas; i++)
        {
            if (h->n <= 0)
            {
                break;
            }
            Item item = extrai_maximo(h);
            printf("%s %s %d\n", item.nome, item.prato, item.chave);
        }
    }

    destroi_heap(h);
    return 0;
}
