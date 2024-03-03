#include <stdio.h>
#include <stdlib.h>

int **grava_matriz(int tamanho)
{
    /*
        Esta função irá realizar a leitura da matriz e alocala dinamicamente em um vetor de vetores, e retornar este vetor de vetor, o parametro utilizado é o tamanho, porque se trata de uma matriz quadrada
    */
    int **quadra;
    quadra = malloc(tamanho * (sizeof(int *)));

    if (quadra == NULL)
    {
        printf("Nao ha memoria suficiente para armazenar o vetor!");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++)
    {
        *(quadra + i) = malloc(tamanho * sizeof(int));

        if (*(quadra + i) == NULL)
        {
            printf("Nao ha memoria suficiente para armazenar o vetor!");
            exit(1);
        }
    }

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            scanf(" %d", &quadra[i][j]);
        }
    }

    return quadra;
}

void free_matriz(int **matriz, int tamanho)
{
    /*
        Libera o espaco de memoria da matriz!
    */
    for (int i = 0; i < tamanho; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

void impressao_matriz(int **quadra, int tamanho)
{
    /*
        Esta funcao realiza a impressao da matriz quadra, dado o ponteiro da matriz e o tamanho pelos parametros, não retorna nada!
    */
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            printf("%d  ", quadra[i][j]);
        }
        printf("\n");
    }
}

int soma_matriz(int **matriz, int tamanho, int inicioI, int inicioJ)
{
    /*
        Esta funcao irá realizar a soma de todos os valores da matriz que for passado para ela, o objetivo será construir a funcao de forma que possa ser utilizado para submatrizes de uma mesma matriz.
        A funcao recebe de parametro a matriz, o tamanho da matriz, que pode variar conforme a sub matriz a ser avaliada, e aposicoa inicial, de onde começa a sub matriz.

    */

    int i;
    int j;
    int soma = 0;
    for (i = 0; i < tamanho; i++)
    {
        for (j = 0; j < tamanho; j++)
        {
            soma += matriz[i + inicioI][j + inicioJ];
        }
    }

    return soma;
}

int *compara_sub_matrizes(int **matriz, int tamanho)
{
    /*
        Esta funcao irá comparar a soma de submatrizes e retornar a com maior valor, que será a com estado mais critico de reparos.
        Como é uma matriz quadrada, iremos comparar 4 matrizes e retornar 1.
        O parametros será a matriz, o tamanho da matriz (varia de acordo com a submatriz avaliada), a matriz sempre será analisada a partir d0 0,0, porque a matriz sempre é regravada para uma menor!
        Retorna um vetor dinamicamente alocado de duas posicoes que indica onde começa a proxima matriz.
    */

    int vetorSomas[4] = {0, 0, 0, 0};

    vetorSomas[0] = soma_matriz(matriz, tamanho - 1, 0, 0);
    vetorSomas[1] = soma_matriz(matriz, tamanho - 1, 0 + 1, 0);
    vetorSomas[2] = soma_matriz(matriz, tamanho - 1, 0, 0 + 1);
    vetorSomas[3] = soma_matriz(matriz, tamanho - 1, 0 + 1, 0 + 1);

    int *maior;
    maior = malloc(2 * sizeof(int));

    *maior = vetorSomas[0];
    *(maior + 1) = 0;

    for (int i = 0; i < 4; i++)
    {
        if (*(maior) < vetorSomas[i])
        {
            *maior = vetorSomas[i];
            *(maior + 1) = i;
        }
    }

    int *retorno;

    retorno = malloc(2 * sizeof(int));
    if (*(maior + 1) == 0)
    {
        *(retorno) = 0;
        *(retorno + 1) = 0;
    }
    else if (*(maior + 1) == 1)
    {
        *(retorno) = 0 + 1;
        *(retorno + 1) = 0;
    }
    else if (*(maior + 1) == 2)
    {
        *(retorno) = 0;
        *(retorno + 1) = 0 + 1;
    }
    else if (*(maior + 1) == 3)
    {
        *(retorno) = 0 + 1;
        *(retorno + 1) = 0 + 1;
    }

    free(maior);

    return retorno;
}

int **altera_matriz(int **matriz, int tamanho, int posI, int posJ)
{

    /*
        A abordagem desta funcao é receber a matriz original, o tamanho dela, e a posicao da quadra que deseja ser alterada, e assim ,criar um outra submatriz apenas com a quadra desejada, bem como liberar o espaço de memória da matriz original.
        O retorno dela é o endereço da nova sub matriz, que é armazenado no endereço da matriz original!
    */

    int **novaMatriz;

    novaMatriz = malloc((tamanho - 1) * sizeof(int *));
    if (novaMatriz == NULL)
    {
        printf("Não há memória suficiente no computador!");
        exit(1);
    }
    for (int i = 0; i < (tamanho - 1); i++)
    {
        novaMatriz[i] = malloc((tamanho - 1) * sizeof(int));
    }
    // GRAVACAO DA NOVA MATRIZ

    for (int i = 0; i < (tamanho - 1); i++)
    {
        for (int j = 0; j < (tamanho - 1); j++)
        {
            novaMatriz[i][j] = matriz[posI + i][posJ + j];
        }
    }
    free_matriz(matriz, tamanho);
    return novaMatriz;
}

int verifica_iteracao()
{
    /*
        Está função irá verificar se a entrada pelo usuário foi 0 ou 1, se for 1 ela retorna 1 para o while, continuar rodando, caso foi 0 sai do while!
    */
    int a = 0;
    scanf("%d", &a);
    return a;
}

void alterar_valor_matriz(int **matriz, int posI, int posJ, int val)
{
    /*
        Esta função irá receber a matriz, a posicao, e o valor da alteracao e irá realizar a alteracao na funcao.
    */
    matriz[posI][posJ] = val;
}

int main()
{
    int tamanho_quadra = 0;
    int **quadra;

    scanf("%d", &tamanho_quadra);
    quadra = grava_matriz(tamanho_quadra);
    printf("Quadras:\n");
    impressao_matriz(quadra, tamanho_quadra);

    int *pos;

    pos = compara_sub_matrizes(quadra, tamanho_quadra);
    quadra = altera_matriz(quadra, tamanho_quadra, pos[0], pos[1]);
    tamanho_quadra--;
    pos[0] = 0;
    pos[1] = 0;
    printf("\n");
    printf("Conjuntos que precisam de atenção:\n");
    impressao_matriz(quadra, tamanho_quadra);

    while (verifica_iteracao())
    {
        int posI, posJ, val;

        scanf("%d %d %d", &posI, &posJ, &val);

        alterar_valor_matriz(quadra, posI, posJ, val);
        free(pos);
        pos = compara_sub_matrizes(quadra, tamanho_quadra);
        quadra = altera_matriz(quadra, tamanho_quadra, pos[0], pos[1]);
        tamanho_quadra--;
        pos[0] = 0;
        pos[1] = 0;
        printf("\n");
        printf("Conjuntos que precisam de atenção:\n");
        impressao_matriz(quadra, tamanho_quadra);
    }

    free_matriz(quadra, tamanho_quadra);
    free(pos);
    return 0;
}
