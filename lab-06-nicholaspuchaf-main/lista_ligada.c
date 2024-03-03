
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_ligada.h"

no *cria_lista_vazia()
{
    // CRIA LISTA VAZIA = NULA
    return NULL;
}

void destruir_lista(no *lista)
{
    /*
        Destroi a lista recursivamente. Nao tem retorno e recebe a lista como primeiro elemento.

    */
    if (lista == NULL)
    {
        return;
    }
    if (lista != NULL)
    {
        destruir_lista(lista->proximo);
    }
    free(lista->livro);
    free(lista);
}

no *adiciona_elemento_final(no *lista, char *dado)
{
    /*
        Adiciona um elemento no final da lista, recebe a lista e o dado a ser adicionado como parametros.
        Retorna uma nova lista ligada porque pode-ser que a lista passada seja nula!
    */
    no *elemento = lista;

    if (lista == NULL)
    {
        // E O PRIMEIRO
        elemento = malloc(sizeof(no));
        elemento->livro = dado;
        elemento->proximo = NULL;
        return elemento;
    }

    while (elemento->proximo != NULL)
    {
        elemento = elemento->proximo;
    }
    no *elemento_a_adicionar = malloc(sizeof(no));
    elemento_a_adicionar->livro = dado;
    elemento_a_adicionar->proximo = NULL;
    elemento->proximo = elemento_a_adicionar;
    return lista;
}

no *junta_lista(no *listaOriginal, no *listaExtra)
{
    /*
        Junta duas lista ligadas, sendo que essa junta a listaExtra no final da listaOriginal
        retorna o ponteiro para a nova lista ligada combinada!

    */

    if (listaExtra == NULL)
    {
        return listaOriginal;
    }
    if (listaOriginal == NULL)
    {
        return listaExtra;
    }

    no *elemento = listaExtra;
    while (elemento->proximo != NULL)
    {
        elemento = elemento->proximo;
    }
    elemento->proximo = listaOriginal;
    return listaExtra;
}

void imprimir_lista(no *lista, no *lista2)
{
    /*
        Imprime a lista, recebe duas listas, a lista original e a auxiliar, verifica se ambas forem diferentes de NULL imprime as duas, caso contrário
        imprime apenas uma!
    */

    if (lista != NULL && lista2 != NULL)
    {
        no *elemento = lista;

        while (elemento->proximo != NULL)
        {
            printf("%s, ", elemento->livro);
            elemento = elemento->proximo;
        }
        printf("%s, ", elemento->livro);

        elemento = lista2;

        while (elemento->proximo != NULL)
        {
            printf("%s, ", elemento->livro);
            elemento = elemento->proximo;
        }

        printf("%s", elemento->livro);
    }

    else if (lista != NULL)
    {

        no *elemento = lista;

        while (elemento->proximo != NULL)
        {
            printf("%s, ", elemento->livro);
            elemento = elemento->proximo;
        }
        printf("%s", elemento->livro);
    }
    else if (lista2 != NULL)
    {
        no *elemento = lista2;

        while (elemento->proximo != NULL)
        {
            printf("%s, ", elemento->livro);
            elemento = elemento->proximo;
        }
        printf("%s", elemento->livro);
    }
    printf("\n");
}

no *remover_elemento(no *lista, char *dado)
{
    /*
        Função remove o elemento da lista ligada, recebe como parâmetro a lista e o dado a ser retirado
        Retorna um ponteiro da lista, porque pode-ser que tenha que retirar o primeiro elemento!
    */

    if (lista == NULL)
    {
        return NULL;
    }

    if (dado == NULL)
    {
        printf("\nErro de parametro!\n");
    }

    if (lista->livro == NULL)
    {
        printf("\nErro livro nao salvo!\n");
    }

    if (strcmp(lista->livro, dado) == 0)
    {
        // E O PRIMEIRO

        no *retornar = lista->proximo;
        free(lista->livro);
        free(lista);
        return retornar;
    }

    no *anterior;
    no *atual;

    anterior = lista;
    atual = anterior->proximo;

    while (atual != NULL)
    {

        if (strcmp(atual->livro, dado) == 0)
        {
            // SAO IGUAIS DEVE RETIRAR

            anterior->proximo = atual->proximo;
            free(atual->livro);
            free(atual);
            return lista;
        }
        anterior = anterior->proximo;
        atual = anterior->proximo;
    }

    return lista;
}
