
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arvore_rb.h"

int eh_preto(no *raiz)
{
    /* Está função verifica se o nó é preto!, retorna 1, se é preto, 0 se é vermelho, 1 se é NULL, porque as folhas NULLs sao pretas */
    if (raiz == NULL)
    {
        return 1;
    }
    else
    {
        return raiz->cor == PRETO;
    }
}

int eh_vermelho(no *raiz)
{
    /* Essa função verifica se o nó é vermelho, retorna 1 se for vermelho, 0 se for preto e 0 se for NULL */
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        return raiz->cor == VERMELHO;
    }
}

no *rotacao_para_esquerda(no *raiz)
{
    /* Está função rotaciona a árvore para a esquerda! */
    no *x = raiz->dir;

    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

no *rotacao_para_direita(no *raiz)
{
    /* Está função rotaciona a árvore para a direita, retorna o novo ponteiro para a raiz! */
    no *x = raiz->esq;

    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

void sobe_vermelho(no *raiz)
{
    /* Está função sobre o vermelho do nó */
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

int comparar_chaves(tipo_chave *chave1, tipo_chave *chave2)
{
    /*  Está função comparar duas "chaves", tipo_chave é o dado guardado pela árvore, essa função é utilizada para comparar dois nós e
        pode decidir qual é "maior" e qual é "menor". Assim podendo ordenar os nós!
     */
    if (strcmp(chave1->nome_var, chave2->nome_var) < 0) // str1 < str2
    {
        return 1; // chave1 < chave2
    }
    else // str1 >= str2
    {
        return 0; // chave2 >= chave 1
    }
}

no *inserir_rec(no *raiz, tipo_chave *chave)
{
    /*
        Está função é um insercao recursiva na árvore, que também arruma a árvore, após a inserção.
        Retirado do slide do Rafael!
    */
    if (raiz == NULL)
    {

        no *novo = malloc(sizeof(no));

        novo->esq = NULL;
        novo->dir = NULL;
        novo->chave = chave;
        novo->cor = VERMELHO;
        return novo;
    }

    if (comparar_chaves(chave, raiz->chave))
    {
        raiz->esq = inserir_rec(raiz->esq, chave);
    }
    else
    {
        raiz->dir = inserir_rec(raiz->dir, chave);
    }

    /* Corrige a árvore */
    if (eh_vermelho(raiz->dir) && eh_preto(raiz->esq))
    {
        raiz = rotacao_para_esquerda(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq))
    {
        raiz = rotacao_para_direita(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir))
    {
        sobe_vermelho(raiz);
    }

    return raiz;
}

no *inserir(no *raiz, tipo_chave *chave)
{
    /*
        Está é a função de inserir uma chave na árvore, ele roda a insercao recursiva, e no final garante que a raiz seja preta
        Retorna ponteiro para a nova árvore!
        Retirado do slide do Rafael!
    */
    raiz = inserir_rec(raiz, chave);
    raiz->cor = PRETO;
    return raiz;
}

int mesmo_nome_chave(tipo_chave *chave1, tipo_chave *chave2)
{
    /*
        Está função compara se duas chaves tem o mesmo nome! Não é utilizada em Dracarys!
    */
    if (chave1 == NULL)
    {
        return 0;
    }
    if (chave2 == NULL)
    {
        return 0;
    }
    if (strcmp(chave1->nome_var, chave2->nome_var) == 0)
    {
        return 1;
    }
    if (strcmp(chave1->nome_var, chave2->nome_var) < 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

no *buscar_nome(no *raiz, char *nome)
{
    /*
        Esta função procura uma determinada raiz na árvore, a partir do nome do nó como parâmetro!
        Retorna um nó
    */
    if (raiz == NULL)
    {
        return raiz;
    }
    if (strcmp(raiz->chave->nome_var, nome) == 0)
    {
        return raiz;
    }
    if (strcmp(raiz->chave->nome_var, nome) < 0)
    {
        return buscar_nome(raiz->dir, nome);
    }
    else
    {
        return buscar_nome(raiz->esq, nome);
    }
}

no *buscar(no *raiz, tipo_chave *chave)
{
    /*
        Busca um nó a partir de um dado chave, não é utilizado em Dracarys!
    */
    if (mesmo_nome_chave(raiz->chave, chave) == 1)
    {
        return raiz;
    }
    else if (mesmo_nome_chave(raiz->chave, chave) == 2) // < 0
    {
        return buscar(raiz->esq, chave);
    }
    else if (mesmo_nome_chave(raiz->chave, chave) == 3)
    {
        return buscar(raiz->dir, chave);
    }
    else if (mesmo_nome_chave(raiz->chave, chave) == 0)
    {
        return raiz; // RAIZ = NULL ou CHAVE = NULL
    }
    return raiz;
}

void imprimir_arvore(no *raiz)
{
    /*
        Está função imprimie a árvore, imprime todos os nós, utilizado apenas para debuggar!
    */
    if (raiz == NULL)
    {
        return;
    }
    // HAVERA ERRO AQUi
    printf("%s : %d\n", raiz->chave->nome_var, raiz->chave->tipo);
    imprimir_arvore(raiz->esq);
    imprimir_arvore(raiz->dir);
}

void destruir_chave(tipo_chave *chave)
{
    /* Esta função irá dar free na chave passada como parâmetro! */
    if (chave == NULL)
    {
        return;
    }
    free(chave->nome_var);
    free(chave);
}

void destruir_arvore(no *raiz)
{
    /* Esta função detroi a árvore inteira recursivamente! */
    if (raiz == NULL)
    {
        return;
    }
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    destruir_chave(raiz->chave);
    free(raiz);
}

char *extrai_tipo(no *raiz)
{
    /* Esta função irá extrar o tipo do dado de um nó, retorna uma string alocada dinamicamente com este nome! */
    char *tipo = malloc(7 * sizeof(char));
    for (int i = 0; i < 7; i++)
    {
        tipo[i] = '\0';
    }

    if (raiz->chave->tipo == INT)
    {
        strcpy(tipo, "int");
    }

    else if (raiz->chave->tipo == CHAR)
    {
        strcpy(tipo, "char");
    }

    else if (raiz->chave->tipo == DOUBLE)
    {
        strcpy(tipo, "double");
    }
    return tipo;
}

void imprimir_esq_dir(no *raiz)
{
    /* Esta função irá imprimir a arvore em ordem alfabetica! */
    if (raiz == NULL)
    {
        return;
    }
    imprimir_esq_dir(raiz->esq);
    char *tipo = extrai_tipo(raiz);
    printf("%s %s\n", raiz->chave->nome_var, tipo);
    free(tipo);
    imprimir_esq_dir(raiz->dir);
}

int contagem_numero_nos(no *raiz)
{
    /* Esta função conta o numero de nós da árvore, utilizado apenas para debuggar tambem! */
    if (raiz == NULL)
    {
        return 0;
    }

    return contagem_numero_nos(raiz->esq) + contagem_numero_nos(raiz->dir) + 1;
}

int altura_da_arvore(no *raiz)
{
    /* Esta função calcula a altura da arvore, utilizado apenas para debuggar tambem! */
    int tamanho = 0;
    no *temp = raiz;

    while (temp != NULL)
    {
        tamanho++;
        temp = temp->esq;
    }

    return tamanho;
}
