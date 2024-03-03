
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef ARVORE_H
#include "arvore.h"
#endif

#ifndef PILHA_H
#include "pilha.h"
#endif

int is_string(char string[])
{
    /*
        Esta funcão verifica se uma string, é um numero(nesse caso retorna 0)
        ou é um letra ou uma expressão(nesses casos retorna 1)
    */

    if (isalpha(string[0]))
    {
        return 1;
    }

    if (isalnum(string[0]))
    {
        return 0;
    }

    if (string[0] == '(')
    {
        return 1;
    }

    return 0;
}

char *ler_expressao()
{

    /*
        Esta funcão lê a expressão que será avaliada no programa, a expressao é guardada dinamicamente
        Retorna o ponteiro para a expressao!
    */

    int i = 0;
    int tamanho = 2;

    char *expressao = malloc(tamanho * sizeof(char));

    for (int j = 0; j < tamanho; j++)
    {
        expressao[j] = '\0';
    }

    char caracter = '\n';
    scanf("%c", &caracter);

    while (caracter != '\n')
    {

        expressao[i] = caracter;
        i++;
        tamanho++;

        expressao = realloc(expressao, tamanho * sizeof(char));

        expressao[tamanho - 1] = '\0';

        scanf("%c", &caracter);
    }
    return expressao;
}

int o_que_eh(char caracter)
{
    /*
        Está funcão determina o que é dado caracter, se é um numero, letra ou operacao.
        Utilizado para gerenciar as funcoes de operacao
        Retorna um int. Recebe como parâmtro o caracter a ser analisado
    */

    /*
        Retornos :
        2 . operador logico
        1 . operador relacional
        3 . operador de igualdade
        0 . um numero
        -1 . um letra
    */

    if (caracter == '|' || caracter == '&')
    {
        return 2;
    }

    if (caracter == '>' || caracter == '<' || caracter == '{' || caracter == '}')
    {
        return 1;
    }

    if (caracter == '!' || caracter == '=')
    {
        return 3;
    }

    if (isdigit(caracter))
    {
        return 0;
    }
    return -1;
}

void realiza_operacao(char dado, pilha *parser)
{
    /*
        Está funcão é utilizada para montar a arvore binária, ele vai juntando as arvores na ordem correta!
        De forma, que no final ele cria um arvore binária de toda a expressao!
    */

    no *folha1 = desempilhar(parser);
    no *folha2 = desempilhar(parser);

    no *ramo = cria_arvore(dado, 2, folha2, folha1);

    empilhar(parser, ramo);
}

void adiciona_pilha(char dado, pilha *parser)
{
    /*
        Esta funcão cria um ramo novo da árvore, e adiciona na pilha!
        Recebe como pârametreo
    */
    int qual_tipo = o_que_eh(dado);
    no *ramo = cria_arvore(dado, qual_tipo, NULL, NULL);
    empilhar(parser, ramo);
}

void analisa_caracter(char dado, pilha *parser)
{
    /*
        Essa funcão irá analisar de acordo com o char dado, se deve criar uma nova árvore e adicionar na pilha(
        o que ocorre quando são numeros ou letras)
        Ou se deve pegar duas sub-arvores da pilha e formar uma nova e adicionar na pilha!
        Utilizada para a construcão da arvore binária!
        Recebe como parâemtro o char dado - que é dado lido na expressao, e também a pilha parser que gerencia a árvore
    */

    int qual_tipo = o_que_eh(dado) > 0 ? 1 : 0;

    if (qual_tipo == 0)
    {
        // SE FOR UM VALOR DEVE SER CRIADA UMA NOVA ARVORE PORQUE OS VALORES SEMPRE FICAM NAS FOLHAS

        adiciona_pilha(dado, parser);
    }
    else if (qual_tipo == 1)
    {
        // NESSE CASO O DADO É UM OPERADOR LOGO DEVE SER REALIZADA OPERACAO E CRIACAO DE NOVA ARVORE!

        realiza_operacao(dado, parser);
    }
}

char *impressao_arvore(no *raiz)
{

    /*
        Essa funcão realiza a impressao da expressão (que foi guardada em árvore binária) antes de ser balanceada!
        A funcão é recursiva e o caso base é quando ambas as raizes filhas são "valores ou numeros"
        O retorno é o ponteiro de uma string que alocada dinamicamente, dentro da funcão as "substrings" são liberadas, e a final é liberada na main!

    */

    int no_esq = o_que_eh(raiz->filho_esq->dado);
    int no_dir = o_que_eh(raiz->filho_dir->dado);

    if (no_esq <= 0 && no_dir <= 0)
    {
        // AMBOS SAO NUMEROS OU VALORES

        char *expressao = malloc(8 * sizeof(char));

        for (int i = 0; i < 8; i++)
        {
            expressao[i] = '\0';
        }

        expressao[0] = '(';
        expressao[1] = raiz->filho_esq->dado;
        expressao[2] = ' ';
        expressao[3] = raiz->dado;
        expressao[4] = ' ';
        expressao[5] = raiz->filho_dir->dado;
        expressao[6] = ')';

        return expressao;
    }
    else
    {

        // NAO È O CASO BASE, IRÀ CRIAR AS "subexpressoes" e depois junta-las

        if (no_esq <= 0)
            exit(3);
        if (no_dir <= 0)
            exit(3);

        char *expressaoEsq = impressao_arvore(raiz->filho_esq); // aqui a sub-expressao esquerda
        char *expressaoDir = impressao_arvore(raiz->filho_dir); // aqui a sub-expressao direita

        // realiza a juncão delas!

        int tamEsq = strlen(expressaoEsq);
        int tamDir = strlen(expressaoDir);

        int tamanho = 2 * (1 + tamDir + tamEsq);

        char *expressaoFinal = malloc(tamanho * sizeof(char));

        for (int i = 0; i < tamanho; i++)
        {
            expressaoFinal[i] = '\0';
        }

        expressaoFinal[0] = '(';
        strcat(expressaoFinal, expressaoEsq);
        // strcat(expressaoFinal, " ");

        char oper[3] = {' ', raiz->dado, ' '};

        strcat(expressaoFinal, oper);
        // strcat(expressaoFinal, " ");
        strcat(expressaoFinal, expressaoDir);
        strcat(expressaoFinal, ")");

        free(expressaoEsq);
        free(expressaoDir);

        return expressaoFinal;
    }
}

void imprimir_arvore(no *raiz)
{

    if (o_que_eh(raiz->dado) == 0 || o_que_eh(raiz->dado) == -1)
    {
        /* É numero ou letra */
        printf("%c", raiz->dado);
    }
    else
    {
        /* É OPERADOR */

        printf("(");
        imprimir_arvore(raiz->filho_esq);
        printf(" %c ", raiz->dado);
        imprimir_arvore(raiz->filho_dir);
        printf(")");
    }
}

int operacao_ou(char *val1, char *val2)
{

    /*
        Operacão OU ( | ), retorna int
        1 - T
        0 - F
        2 - mantenha a expressao
    */

    if (val1[0] == 'T')
        return 1;
    if (val2[0] == 'T')
        return 1;

    if (strlen(val1) > 1)
    {
        return 2;
    }
    if (strlen(val2) > 1)
    {
        return 2;
    }

    return 0;
}

int operacao_ee(char *val1, char *val2)
{

    /*
        Operacão E ( & ), retorna int
        1 - T
        0 - F
        2 - mantenha a expressao
    */

    if (val1[0] == 'F')
        return 0;
    if (val2[0] == 'F')
        return 0;

    if (strlen(val1) > 1)
    {
        return 2;
    }
    if (strlen(val2) > 2)
    {
        return 2;
    }

    return 0;
}

int operacao_desigualdade_igual(char operador, char *val1, char *val2)
{

    /*
        Operacão { } , retorna int
        1 - T
        0 - F
        2 - mantenha a expressao
    */

    if (operador == '{')
    {
        if (val2[0] == '9')
        {
            return 1;
        }

        if (val1[0] == '0')
        {
            return 1;
        }

        if (strcmp(val1, val2) == 0)
        {
            return 1;
        }

        if (is_string(val2))
        {
            return 2;
        }

        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 <= valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (operador == '}')
    {

        if (val2[0] == '0')
        {
            return 1;
        }

        if (val1[0] == '9')
        {
            return 1;
        }

        if (strcmp(val1, val2) == 0)
        {
            return 1;
        }

        if (is_string(val2))
        {
            return 2;
        }
        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 >= valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    exit(7);
}

int operacao_desigualdade(char operador, char *val1, char *val2)
{
    /*
        Operacão < > , retorna int
        1 - T
        0 - F
        2 - mantenha a expressao
    */

    if (operador == '>')
    {

        if (val2[0] == '9')
        {
            return 0;
        }

        if (val1[0] == '0')
        {
            return 0;
        }

        if (strcmp(val1, val2) == 0)
        {
            return 0;
        }

        if (is_string(val2))
        {
            return 2;
        }

        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 > valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (operador == '<')
    {

        if (val2[0] == '0')
        {
            return 0;
        }

        if (val1[0] == '9')
        {
            return 0;
        }

        if (strcmp(val1, val2) == 0)
        {
            return 0;
        }

        if (is_string(val2))
        {
            return 2;
        }

        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 < valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    exit(7);
}

int operacao_igualdade(char operador, char *val1, char *val2)
{

    /*
        Operacão = ! , retorna int
        1 - T
        0 - F
        2 - mantenha a expressao
    */

    if (operador == '=')
    {

        if (strcmp(val1, val2) == 0)
        {
            return 1;
        }

        if (is_string(val2))
        {
            return 2;
        }

        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 == valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (operador == '!')
    {

        if (strcmp(val1, val2) == 0)
        {
            return 0;
        }

        if (is_string(val2))
        {
            return 2;
        }

        if (is_string(val1))
        {
            return 2;
        }

        int valor1 = val1[0] * 1;
        int valor2 = val2[0] * 1;

        if (valor1 != valor2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    exit(7);
}

char *cria_expressao(char operador, char *val1, char *val2, int temfree)
{

    /*
        Essa funcão irá concatenar um operador com duas outras strings, e irá dar free nas outras duas strings
        Retorna uma nova expressao alocada dinamicamente!
    */

    char *expressao;

    int tamanho = 2 * (3 + strlen(val1) + strlen(val2));

    expressao = malloc(tamanho * sizeof(char));

    for (int i = 0; i < tamanho; i++)
    {
        expressao[i] = '\0';
    }

    expressao[0] = '(';
    strcat(expressao, val1);
    strcat(expressao, " ");

    char operadores[2] = {operador, ' '};

    strcat(expressao, operadores);
    // strcat(expressao, " ");
    strcat(expressao, val2);
    strcat(expressao, ")");

    if (temfree)
    {
        free(val1);
        free(val2);
    }

    return expressao;
}

char *retonar_t_ou_f(char dado)
{

    /*
        Esta funcão irá pegar um char dado e criar um string com apenas esse char dado
        Retorna um string de tamanho 2 = {dado, '/0'}
    */

    char *retorno = malloc(2 * sizeof(char));

    retorno[0] = dado;
    retorno[1] = '\0';

    return retorno;
}

char *resolver_arvore(no *raiz)
{
    /*
        Esta funcão irá "resolver" a árvore, que seria tentar balancear e diminuir a funcão
        Também é uma funcão recursiva, similar a funcão de impressão, a diferenca é que possui alguns criterios para tentar
        balancea-la
        Retonra uma string alocada dinamicante também!
    */
    int noEsq = o_que_eh(raiz->filho_esq->dado);
    int noDir = o_que_eh(raiz->filho_dir->dado);

    if (noEsq <= 0 && noDir <= 0)
    {
        // AMBOS FILHOS SAO LETRAS OU NUMEROS

        char operador = raiz->dado;
        int operador_qual = o_que_eh(raiz->dado);

        char val1[2] = {raiz->filho_esq->dado, '\0'};
        char val2[2] = {raiz->filho_dir->dado, '\0'};

        // char *val1 = &(raiz->filho_esq->dado);
        // char *val2 = &(raiz->filho_dir->dado);

        if (operador_qual == 2)
        {
            if (operador == '|')
            {
                int retorno = operacao_ou(val1, val2);

                if (retorno == 2)
                {
                    return cria_expressao(operador, val1, val2, 0);
                }

                if (retorno == 0)
                {

                    return retonar_t_ou_f('F');
                }
                if (retorno == 1)
                {

                    return retonar_t_ou_f('T');
                }
            }
            else if (operador == '&')
            {
                int retorno = operacao_ee(val1, val2);

                if (retorno == 2)
                {
                    return cria_expressao(operador, val1, val2, 0);
                }

                if (retorno == 0)
                {

                    return retonar_t_ou_f('F');
                }
                if (retorno == 1)
                {

                    return retonar_t_ou_f('T');
                }
            }
        }

        if (operador_qual == 1)
        {

            if (operador == '{' || operador == '}')
            {

                int retorno = operacao_desigualdade_igual(operador, val1, val2);

                if (retorno == 2)
                {
                    return cria_expressao(operador, val1, val2, 0);
                }

                else if (retorno == 1)
                {

                    return retonar_t_ou_f('T');
                }
                else if (retorno == 0)
                {

                    return retonar_t_ou_f('F');
                }
            }
            if (operador == '<' || operador == '>')
            {

                int retorno = operacao_desigualdade(operador, val1, val2);

                if (retorno == 2)
                {
                    return cria_expressao(operador, val1, val2, 0);
                }

                if (retorno == 1)
                {

                    return retonar_t_ou_f('T');
                }
                if (retorno == 0)
                {

                    return retonar_t_ou_f('F');
                }
            }
        }

        if (operador_qual == 3)
        {

            int retorno = operacao_igualdade(operador, val1, val2);

            if (retorno == 2)
            {
                return cria_expressao(operador, val1, val2, 0);
            }

            if (retorno == 1)
            {

                return retonar_t_ou_f('T');
            }

            if (retorno == 0)
            {

                return retonar_t_ou_f('F');
            }
        }
    }
    else
    {

        char *expressao_esq = resolver_arvore(raiz->filho_esq);
        char *expressao_dir = resolver_arvore(raiz->filho_dir);

        char operador = raiz->dado;
        int operador_qual = o_que_eh(raiz->dado);

        if (operador_qual == 2)
        {
            if (operador == '|')
            {
                int retorno = operacao_ou(expressao_esq, expressao_dir);

                if (retorno == 2)
                {
                    return cria_expressao(operador, expressao_esq, expressao_dir, 1);
                }

                if (retorno == 0)
                {

                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('F');
                }
                if (retorno == 1)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('T');
                }
            }
            else if (operador == '&')
            {
                int retorno = operacao_ee(expressao_esq, expressao_dir);

                if (retorno == 2)
                {
                    return cria_expressao(operador, expressao_esq, expressao_dir, 1);
                }

                if (retorno == 0)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('F');
                }
                if (retorno == 1)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('T');
                }
            }
        }

        if (operador_qual == 1)
        {

            if (operador == '{' || operador == '}')
            {

                int retorno = operacao_desigualdade_igual(operador, expressao_esq, expressao_dir);

                if (retorno == 2)
                {
                    return cria_expressao(operador, expressao_esq, expressao_dir, 1);
                }

                else if (retorno == 1)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('F');
                }
                else if (retorno == 0)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('F');
                }
            }
            if (operador == '<' || operador == '>')
            {

                int retorno = operacao_desigualdade(operador, expressao_esq, expressao_dir);

                if (retorno == 2)
                {
                    return cria_expressao(operador, expressao_esq, expressao_dir, 1);
                }

                if (retorno == 1)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('T');
                }
                if (retorno == 0)
                {
                    free(expressao_dir);
                    free(expressao_esq);
                    return retonar_t_ou_f('F');
                }
            }
        }

        if (operador_qual == 3)
        {

            int retorno = operacao_igualdade(operador, expressao_esq, expressao_dir);

            if (retorno == 2)
            {
                return cria_expressao(operador, expressao_esq, expressao_dir, 1);
            }

            if (retorno == 1)
            {
                free(expressao_dir);
                free(expressao_esq);
                return retonar_t_ou_f('T');
            }

            if (retorno == 0)
            {
                free(expressao_dir);
                free(expressao_esq);
                return retonar_t_ou_f('F');
            }
        }
    }

    exit(9);
}

int main()
{

    int num_de_linhas = 0;
    scanf("%d\n", &num_de_linhas);

    char *expressao = NULL;

    while (num_de_linhas != 0)
    {
        num_de_linhas--;
        pilha *parser = cria_pilha();

        expressao = ler_expressao();

        for (int i = 0; i < strlen(expressao); i++)
        {

            char dado = expressao[i];

            analisa_caracter(dado, parser);
        }

        // char *expressaoFinal = impressao_arvore(parser->topo->dado);

        // printf("%s\n", expressaoFinal);

        imprimir_arvore(parser->topo->dado);

        printf("\n");

        char *arvore_resolvida = resolver_arvore(parser->topo->dado);

        printf("%s\n", arvore_resolvida);

        printf("\n");

        free(arvore_resolvida);
        // free(expressaoFinal);
        free(expressao);
        destruir_pilha(parser);
    }

    return 0;
}
