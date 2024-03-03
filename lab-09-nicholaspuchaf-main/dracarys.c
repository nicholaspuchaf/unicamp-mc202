
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arvore_rb.h"

#define MAX 1024

char *leitura_linha_fgets()
{
    /* Realiza a leitura da linha da entrada utilizando fgets, retorna uma string alocada dinamicamente da linha */
    char buffer[MAX];

    for (int i = 0; i < MAX; i++)
    {
        buffer[i] = '\0';
    }

    fgets(buffer, MAX, stdin);

    char *linha = malloc((strlen(buffer) + 3) * sizeof(char));

    strcpy(linha, buffer);

    if (strlen(linha) > 2)
    {
        if (linha[strlen(linha) - 1] == '\n')
        {
            linha[strlen(linha) - 1] = '\0';
        }
    }

    return linha;
}

char *leitura_linha()
{
    /* Realiza a leitura da linha utilizando scanf, e lendo caracter por caracter, aloca dinameicamente também e retonra a linha! */
    char *linha = malloc(3 * sizeof(char));

    for (int i = 0; i < 3; i++)
    {
        linha[i] = '\0';
    }

    char letra = '\n';

    int tamanho = 3;

    scanf("%c", &letra);
    int indice = 0;

    while (letra != '\n')
    {

        linha[indice] = letra;
        indice++;

        tamanho++;
        linha = realloc(linha, tamanho * sizeof(char));
        linha[tamanho - 1] = '\0';

        scanf("%c", &letra);
    }
    fflush(stdin);
    return linha;
}

int o_que_fazer(char *linha)
{

    /*
        Esta funçõa irá definir o que será feito a partir da string linha passada como parâmetro
        Retornos:
        1 - definicao
        2 - operacao
        3 - qualquer outra coisa
        0 - erro
        -1 - EOF
    */
    if (linha[0] == EOF)
    {
        return -1;
    }

    if (linha[0] == '#')
    {
        return 3;
    }
    if (strlen(linha) < 4)
    {
        return 3;
    }
    if (linha == NULL)
    {
        return 0;
    }

    char retorno[7] = {'r', 'e', 't', 'u', 'r', 'n'};
    int j = 0;

    for (int i = 0; i < strlen(linha); i++)
    {

        if (linha[i] == 'r')
        {
            int i_backup = i;
            i++;
            for (j = 1; j < 6; j++, i++)
            {

                if (linha[i] != retorno[j])
                {
                    break;
                }
            }
            if (j == 6)
            {
                return 3;
            }
            j = 0;
            i = i_backup;
        }

        if (linha[i] == '(')
        {
            return 3;
        }
        if (linha[i] == '{')
        {
            return 3;
        }
        if (linha[i] == '}')
        {
            return 3;
        }

        if (linha[i] == '+' || linha[i] == '*' || linha[i] == '-' || linha[i] == '/' || linha[i] == '%')
        {
            return 2;
        }
    }

    return 1;
}

no *adicionar_na_arvore(no *arvore, char tipo[10], char *nome)
{
    /* Esta função adiciona um nó na árvore, a partir do tipo do dado e do nome dado! */
    tipo_chave *chave = malloc(sizeof(tipo_chave));

    if (strcmp(tipo, "int") == 0)
    {
        chave->tipo = INT;
    }
    else if (strcmp(tipo, "double") == 0)
    {
        chave->tipo = DOUBLE;
    }
    else if (strcmp(tipo, "char") == 0)
    {
        chave->tipo = CHAR;
    }

    chave->nome_var = nome;

    arvore = inserir(arvore, chave);
    return arvore;
}

int mesmo_tipo(no *raiz1, no *raiz2)
{
    /* Dadas dois nós ele verififca sem ambas são do mesmo tipo! */
    if (raiz1 == NULL || raiz2 == NULL)
    {
        return 0;
    }

    if (raiz1->chave->tipo == raiz2->chave->tipo)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checagem_erro_definicao(no *raiz1, no *raiz2, no *raiz3, char *var1, char *var2, char *var3, int contador_linhas, int controle_erros)
{
    /* Esta função irá verificar se há erros de definção na linha!, retorna um variavel controle erros para comparar ao longo do
    programa a evolução dos erros ao longos das linhas! */
    if (raiz1 == NULL)
    {
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, var1);
        controle_erros++;
    }
    else if (raiz2 == NULL)
    {
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, var2);
        controle_erros++;
    }
    else if (raiz3 == NULL)
    {
        printf("Linha %d: o símbolo %s não foi definido.\n", contador_linhas, var3);
        controle_erros++;
    }
    return controle_erros;
}

int checagem_erro_tipo(no *raiz1, no *raiz2, no *raiz3, char *var1, char *var2, char *var3, char operador, int contador_linhas, int controle_erros)
{
    /* ERROS DE TIPO */

    /* realiza verificacao de erros de tipo dois nos da entrada, em dada operacao! */

    if (raiz2 != NULL && raiz3 != NULL)
    {
        if (mesmo_tipo(raiz2, raiz3) == 0)
        {
            char *tipo2 = extrai_tipo(raiz2);
            char *tipo3 = extrai_tipo(raiz3);
            printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n", contador_linhas, var2, tipo2, operador, var3, tipo3);
            controle_erros++;
            free(tipo2);
            free(tipo3);
        }

        else if (raiz1 != NULL)
        {

            if (mesmo_tipo(raiz2, raiz3))
            {

                if (mesmo_tipo(raiz1, raiz2) == 0)
                {
                    char *tipo1 = extrai_tipo(raiz1);
                    char *tipo2 = extrai_tipo(raiz2);
                    printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", contador_linhas, var1, tipo1, tipo2);
                    controle_erros++;
                    free(tipo1);
                    free(tipo2);
                }
            }
        }
    }
    return controle_erros;
}

int main()
{

    /* CRIACAO DA ARVORE RUBRO NEGRA */

    no *arvore = NULL;

    char *linha = NULL;
    int contador_linhas = 0;
    int controle_erros = 0;

    while (1)
    {
        contador_linhas++;
        // linha = leitura_linha();
        linha = leitura_linha_fgets();

        if (feof(stdin))
        {
            free(linha);
            break;
        }

        int a = o_que_fazer(linha);

        if (a == -1)
        {
            /* EOF DEVE TERMINAR O PROGRAMETS*/
            free(linha);
            break;
        }
        else if (a == 3)
        {
            free(linha);
            continue;
        }

        if (a == 2)
        {
            /* PARSE DA LINHA */

            char operador;
            char *var1 = malloc((strlen(linha) / 2) * sizeof(char));
            char *var2 = malloc((strlen(linha) / 2) * sizeof(char));
            char *var3 = malloc((strlen(linha) / 2) * sizeof(char));

            sscanf(linha, "%s = %s %c %[^;]", var1, var2, &operador, var3);

            /* ERROS DE DEFINICAO */
            no *raiz1 = NULL;
            no *raiz2 = NULL;
            no *raiz3 = NULL;

            raiz1 = buscar_nome(arvore, var1);
            raiz2 = buscar_nome(arvore, var2);
            raiz3 = buscar_nome(arvore, var3);
            int backup_erros = controle_erros;
            controle_erros = checagem_erro_definicao(raiz1, raiz2, raiz3, var1, var2, var3, contador_linhas, controle_erros);
            if (controle_erros == backup_erros)
            {
                controle_erros = checagem_erro_tipo(raiz1, raiz2, raiz3, var1, var2, var3, operador, contador_linhas, controle_erros);
            }
            free(var1);
            free(var2);
            free(var3);
        }
        else if (a == 1)
        {
            /* CRIACAO DA VARIAVEL */

            /* PARSE DA LINHA*/
            char tipo[10];
            char *nome = malloc(strlen(linha) * sizeof(char));
            for (int i = 0; i < strlen(linha); i++)
            {
                nome[i] = '\0';
            }
            sscanf(linha, "%s %[^;]", tipo, nome);

            arvore = adicionar_na_arvore(arvore, tipo, nome);
        }
        else if (a == 0)
        {
            exit(404);
        }
        free(linha);
    }

    if (controle_erros == 0)
    {
        printf("Não há erros de tipo.\n");
    }

    imprimir_esq_dir(arvore);
    destruir_arvore(arvore);

    return 0;
}
