#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lista_ligada.h"

char *le_entrada()
{

    /*
        Esta função lê a entrada do usuário e aloca o comando e o parâmetro em uma string alocada dinamicamente e retorna o ponteiro dessa string!
    */

    char *entrada;
    entrada = malloc(sizeof(char));
    entrada[0] = '\0';
    char letra;
    letra = getchar();
    int indice = 0;

    if (letra == EOF)
    {
        free(entrada);
        return NULL;
    }

    while (letra != '\n')
    {
        indice++;
        entrada = realloc(entrada, (indice + 1) * sizeof(char));
        entrada[indice - 1] = letra;
        entrada[indice] = '\0';
        letra = getchar();
    }
    indice++;
    entrada = realloc(entrada, (indice + 1) * sizeof(char));
    entrada[indice] = '\0';

    return entrada;
}

int qual_comando(char *frase)
{
    /*
        Esta função recebe a "frase" que é o input do usuário e analisa apenas a primeira palavra para verificar qual comando esta'sendo pedido
        adicionar, imprimir, remover, final ou inicio ...
        retorna um inteiro que identifca qual comando é
        0 = erro, 8 = adicionar, 7 = imprimir, 5 = inicio, 4 final
        Os numeros escolhidos representam a posicao do fim da palavra na "frase", o que é utilizado posteriormente para separação dos parametros da "frase"
    */

    for (int i = 0; i <= strlen(frase); i++)
    {
        if (frase[i] == ' ' || frase[i] == '\0')
        {
            if ((i - 1) == 8)
            {
                return 8; // ADICIONAR
            }
            if ((i - 1) == 7)
            {
                return 7; // IMPRIMIR
            }
            if ((i - 1) == 5)
            {
                return 5; // INICIO
            }
            if ((i - 1) == 6)
            {
                return 6; // REMOVER
            }
            if ((i - 1) == 4)
            {
                return 4; // FINAL
            }
        }
    }
    return 0;
}

char *pega_parametro(char *frase, int comando)
{
    /*
        Esta função recebe a "frase" que é o input do usuário, o comando(int) que determina qual será (adicionar, remover, imprimir, inicio ou final)
        e separa da frase o parametro que será o nome de um livro e retorna isso!

    */
    int tamaParametro = strlen(frase) - comando - 2;
    char *palavra = malloc((tamaParametro + 2) * sizeof(char));

    int i, j;

    for (j = 0, i = comando + 2; j < tamaParametro; i++, j++)
    {
        palavra[j] = frase[i];
    }
    palavra[j] = '\0';
    return palavra;
}

no *adiciona_elemento_lista(no *lista, char *frase, int comando)
{
    /*
        Esta funcao adicioan um elemento na lista, dentro dela ela chama outra funcao que separa da "frase" o que é comando e o que é o nome do livro de fato
        E depois adiciona.
        Ela recebe como parametro a lista a ser alterada, a "frase que é o input do usuaŕio" e um comando(int) que é utilizado para mais facilmente determinar
        o que a funcao deve fazer.
        Ela retorna um ponteiro de lista porque pode ter que adicionar na primeira posicao!
    */

    char *parametro = NULL;
    parametro = pega_parametro(frase, comando);
    lista = adiciona_elemento_final(lista, parametro);

    return lista;
}

no *remover_elem_lista(no *lista, char *frase, int comando)
{
    /*
        Esta funcao remove um elemento da lista, é passado como parametro a "frase" que é o comando com o parametro, o comando (int que permite identificar o tamanho
        do comando) e a lista de onde será removida!
        A função toma cuidado com listas vazias e parametros vazios!
        Retorna uma nova lista porque pode ser que o primeiro elemento tenha que ser retirado a alterará o ponteiro!
    */

    char *parametro = pega_parametro(frase, comando);
    lista = remover_elemento(lista, parametro);
    free(parametro);
    return lista;
}

int main()
{

    no *listaOriginal = cria_lista_vazia();

    char *frase = le_entrada();

    char controle_onde_adiciona = 'f'; // CONTROLE DE ONDE DEVE ADICIONAR COMEÇA COM f DE FINAL

    no *listaExtra = cria_lista_vazia();

    while (frase != NULL)
    {
        int comando = qual_comando(frase);

        if (comando == 8)
        { // COMANDO ADICIONAR
            // APENAS ADICIONA ELEMENTO NA LISTA
            listaExtra = adiciona_elemento_lista(listaExtra, frase, comando);
        }
        if (comando == 7)
        { // COMANDO IMPRIMIR

            // VERIFICA SE A LISTA EXTRA DEVE SER ADICIONADA NO FINAL OU NO INICIO, porque caso o usuário deseje imprimir antes de terminar
            // de inserir novos dados, isso não pode alterar a ordem de inserção dos dados! A finalização de inserção ocorrerá apenas em comandos "inicio" ou "final"

            if (controle_onde_adiciona == 'f')
            {
                imprimir_lista(listaOriginal, listaExtra);
            }
            if (controle_onde_adiciona == 'i')
            {
                imprimir_lista(listaExtra, listaOriginal);
            }
        }
        if (comando == 6)
        { // COMANDO REMOVER

            // Remove o livro da lista, é chamada duas vezes para caso o livro esteja na lista principal ou na auxiliar!

            listaOriginal = remover_elem_lista(listaOriginal, frase, comando);
            listaExtra = remover_elem_lista(listaExtra, frase, comando);
        }
        if (comando == 5)
        { // COMANDO INICIO

            // Junta a lista principal com a lista auxiliar na devida posicção

            if (controle_onde_adiciona == 'f')
            {
                listaOriginal = junta_lista(listaExtra, listaOriginal);
            }
            if (controle_onde_adiciona == 'i')
            {
                listaOriginal = junta_lista(listaOriginal, listaExtra);
            }
            listaExtra = NULL;
            controle_onde_adiciona = 'i';
        }
        if (comando == 4)
        { // COMANDO FINAL

            // Junta a lista principal com a lista auxiliar na devida posicção

            if (controle_onde_adiciona == 'f')
            {
                listaOriginal = junta_lista(listaExtra, listaOriginal);
            }
            if (controle_onde_adiciona == 'i')
            {
                listaOriginal = junta_lista(listaOriginal, listaExtra);
            }
            listaExtra = NULL;
            controle_onde_adiciona = 'f';
        }
        free(frase);
        frase = le_entrada();
    }

    printf("\n");

    destruir_lista(listaOriginal);
    destruir_lista(listaExtra);

    return 0;
}
