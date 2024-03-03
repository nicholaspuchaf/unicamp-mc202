
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HEAP_H
#include "heap.h"
#endif

#define PAI(i) (i - 1) / 2
#define FILHO_ESQ(i) (2 * i) + 1
#define FILHO_DIR(i) (2 * i) + 2

Heap *cria_heap(int tam)
{
    /*
        Está é a função que cria a fila de prioridade heap, recebe int tam como parametro que define o tamanho da fila heap!
        Retorna um ponteiro da heap
    */
    Heap *h = malloc(sizeof(Heap));

    h->tamanho = tam;
    h->n = 0;

    h->v = malloc(tam * sizeof(Item));

    h->ids = malloc(tam * sizeof(Id));

    return h;
}

void destroi_heap(Heap *h)
{
    /*
        Desaloca toda as memorias alocadas da fila heap
    */
    free(h->ids);
    free(h->v);
    free(h);
}

void troca(Heap *h, int ind1, int ind2)
{
    /*
        Esta função troca dois itens da fila de prioridades, recebe "h" a fila heap, e ind1 e ind2 os indices dos itens a serem trocados
    */

    Item temp = h->v[ind1];
    int posTemp = h->ids[temp.id].endereco_heap;

    h->v[ind1].chave = h->v[ind2].chave;
    // strcpy(h->v[ind1].nome, h->v[ind2].nome);
    memmove(h->v[ind1].nome, h->v[ind2].nome, MAX);
    // strcpy(h->v[ind1].prato, h->v[ind2].prato);
    memmove(h->v[ind1].prato, h->v[ind2].prato, MAX);

    h->ids[h->v[ind1].id].endereco_heap = h->ids[h->v[ind2].id].endereco_heap;
    h->v[ind1].id = h->v[ind2].id;

    h->v[ind2].chave = temp.chave;
    // strcpy(h->v[ind2].nome, temp.nome);
    memmove(h->v[ind2].nome, temp.nome, MAX);
    // strcpy(h->v[ind2].prato, temp.prato);
    memmove(h->v[ind2].prato, temp.prato, MAX);

    h->ids[h->v[ind2].id].endereco_heap = posTemp;
    h->v[ind2].id = temp.id;
}

void sobe_no_heap(Heap *h, int indice)
{
    /*
        Está funcao sobe no heap um item
    */
    if (indice > 0 && h->v[PAI(indice)].chave < h->v[indice].chave)
    {
        troca(h, PAI(indice), indice);
        sobe_no_heap(h, PAI(indice));
    }
}

void insere(Heap *h, Item item)
{
    /*
        Esta função insere um item na fila de prioridades heap
    */
    h->v[h->n] = item;
    h->n++;

    h->ids[item.id].endereco_heap = h->n - 1;

    sobe_no_heap(h, h->n - 1);
}

void desce_no_heap(Heap *h, int indice)
{
    /*
        Esta função desce um item no heap, dado o int indice dele.
    */
    int ind_maior_filho = 0;
    if (FILHO_ESQ(indice) < h->n)
    {
        ind_maior_filho = FILHO_ESQ(indice);

        if (FILHO_DIR(indice) < h->n && h->v[FILHO_ESQ(indice)].chave < h->v[FILHO_DIR(indice)].chave)
        {
            ind_maior_filho = FILHO_DIR(indice);
        }

        if (h->v[indice].chave < h->v[ind_maior_filho].chave)
        {
            troca(h, indice, ind_maior_filho);
            desce_no_heap(h, ind_maior_filho);
        }
    }
}

Item extrai_maximo(Heap *h)
{
    /*
        Esta funcao retira o item de maior prioridade do heap
    */
    Item item = h->v[0];

    troca(h, 0, h->n - 1);
    h->n--;
    // h->ids[item.id].endereco_heap = -1;

    desce_no_heap(h, 0);
    return item;
}

void muda_prioridade(Heap *h, int indice, int valor)
{
    /*
        Esta funcao muda a prioridade do item do heap e atualiza a posicao dele no heap
    */
    int novo_valor = h->v[indice].chave + valor;
    if (h->v[indice].chave < novo_valor)
    {
        h->v[indice].chave = novo_valor;
        // h->ids[h->v[indice].id].chave = novo_valor;
        sobe_no_heap(h, indice);
    }
    else
    {
        h->v[indice].chave = novo_valor;
        // h->ids[h->v[indice].id].chave = novo_valor;
        desce_no_heap(h, indice);
    }
}
