// gcc -std=c99 -Wall -Wvla -Werror -g -lm palavras.c -o palavras.exe

#include <stdio.h>
#include <string.h>

#define N 300
#define Np 20

void ler_matriz(char matriz[][N], int L, int C)
{
    /*
    Função irá ler a matriz dos carateres, e após isso irá zerar todos os caracteres não lidos.
    Não retorna nada
    */ 

    int i = 0;
    int j = 0;

    for (i = 0; i < N; i++)
    {

        if (i < L)
        {

            for (j = 0; j < N; j++)
            {

                if (j < C)
                {
                    scanf(" %c\n", &matriz[i][j]);
                }
                else
                {
                    matriz[i][j] = '\0';
                }
            }
        }
        else
        {
            for (j = 0; j < N; j++)
            {
                matriz[i][j] = '\0';
            }
        }
    }

    fflush(stdin);
}

void imprimir_matriz(char matriz[][N], int L, int C)
{
    /*
    Função irá imprimir a matriz dos caracteres, não é utilizada pelo programa, mas foi utilizada para o desenvolvimento !
    */ 

    int i = 0;
    int j = 0;
    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
        {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

void ler_palavras(char palavras[][Np], int P, int palavrasLen[])
{
    /*
    Funcao ira ler as P palavras a serem buscadas na matriz, o maximo de posicoes e 20, apos isso sera preenchida com '\0'
    */ 
    int i = 0;

    for (i = 0; i < P; i++)
    {
        fgets(palavras[i], N, stdin);
        palavrasLen[i] = strlen(palavras[i]) - 1;

        // for (int j = palavrasLen[i]; j < N; j++)
        // {
        //     palavras[i][j] = '\0';
        // }
    }
}

int verifica_palavra_no_vetor_old(char vetor[N], int L, char palavra[Np], int palavraLen)
{
    /* 
        Está função irá buscar uma palavra no vetor, retorna 1 se achou e 0 se não achou
        Não utilizada, foi substituida pela de baixo que eh mais parecida com a de busca em colunas
    */

    for (int i = 0; i < L; i++)
    {
        int savei = i;
        int flag = 0;

        if (vetor[savei] == palavra[flag])
        {

            while (vetor[savei] == palavra[flag])
            {
                flag++;
                savei++;

                if (flag == palavraLen)
                {
                    return 1;
                }
            }

            if (flag == palavraLen)
            {
                return 1;
            }
        }
    }

    return 0;
}

int verifica_palavra_no_vetor(char matriz[][N], int lugar, int C, char palavra[Np], int palavraLen)
{
    /*  
        Esta funcao fixa uma linha pela variavel lugar (matriz[lugar]) e percorre o vetor de forma horizontal, de forma analoga
        com o que foi feito na funcao das colunas
        retorna 0 se a palavra nao esta no vetor, e retorna 1 se esta no vetor, se encontrar a palavra ela para de buscar e retorna 1, para nao ter que realizar 
        a busca inteira!

    */

    for (int i = 0; i < C; i++)
    {

        int savei = i;

        int flag = 0;

        if (palavra[flag] == matriz[lugar][i])
        {

            while (palavra[flag] == matriz[lugar][savei])
            {

                flag++;
                savei++;

                if (flag == palavraLen)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int verifica_palavra_na_coluna(char matriz[][N], int lugar, int C, char palavra[Np], int palavraLen)
{
    /*  
        Esta funcao fixa uma coluna pela variavel lugar (matriz[i][lugar]) e percorre a coluna de forma vertical.
        retorna 0 se a palavra nao esta na coluna, e retorna 1 se esta na coluna, se encontrar a palavra ela para de buscar e retorna 1, para nao ter que realizar 
        a busca inteira!
    */

    for (int i = 0; i < C; i++)
    {

        int savei = i;

        int flag = 0;

        if (palavra[flag] == matriz[i][lugar])
        {

            while (palavra[flag] == matriz[savei][lugar])
            {

                flag++;
                savei++;

                if (flag == palavraLen)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void cria_palavra_invertida(char palavras[][Np], int palavrasLen[N], int P, char palavrasInvertidas[][Np])
{

    /* 
        Esta funcao pega as palavras do vetor de string "palavras" e cria um outro vetor igual porem com as palavras invertidas para
        buscar as palavras de tras para frente com as mesmas funcoes!
        Nao retorna nada!
    */

    for (int i = 0; i < P; i++)
    {

        char palavraInvertida[Np];

        int j = palavrasLen[i];
        j--;
        for (int k = 0; j >= 0; j--, k++)
        {

            palavraInvertida[k] = palavras[i][j];
        }
        for (int k = palavrasLen[i]; k < Np; k++)
        {
            palavraInvertida[k] = '\0';
        }

        strcpy(palavrasInvertidas[i], palavraInvertida);
    }
}

int main()
{
    int L = 0, C = 0, P = 0;

    char matriz[N][N];

    scanf("%d %d %d ", &L, &C, &P);
    ler_matriz(matriz, L, C);

    char palavras[N][Np];
    char palavrasInvertidas[N][Np];
    int palavrasLen[N];

    ler_palavras(palavras, P, palavrasLen);

    cria_palavra_invertida(palavras, palavrasLen, P, palavrasInvertidas);


    int palavrasEncontradas[N];

    for (int i = 0; i < N; i++)
    {
        palavrasEncontradas[i] = 0;
    }

    for (int j = 0; j < P; j++)
    {

        int flag = 0;

        /*
            Loop de busca das palavras, se encontra a palavra
            a flag eh utilizada para que se a palavra for encontrada no vetor nao buscar nas colunas, de forma a ter menos loop's
        */


        for (int i = 0; i < L; i++)
        {

            if (verifica_palavra_no_vetor(matriz, i, C, palavras[j], palavrasLen[j]) == 1)
            {
                palavrasEncontradas[j] = 1;
                flag = 1;
                break;
            }

            if (verifica_palavra_no_vetor(matriz, i, C, palavrasInvertidas[j], palavrasLen[j]) == 1)
            {
                palavrasEncontradas[j] = 1;
                flag = 1;
                break;
            }
        }

        if(flag == 1){
            continue;
        }

        for (int i = 0; i < C; i++)
        {

            if (verifica_palavra_na_coluna(matriz, i, L, palavras[j], palavrasLen[j]) == 1)
            {
                palavrasEncontradas[j] = 1;
                break;
            }

            if (verifica_palavra_na_coluna(matriz, i, L, palavrasInvertidas[j], palavrasLen[j]) == 1)
            {
                palavrasEncontradas[j] = 1;
                break;
            }
        }
    }

    /*
        Impressao de todas as palavras encontradas !
    */

    for (int i = 0; i < P; i++)
    {
        printf("A palavra ");

        for (int j = 0; j < palavrasLen[i]; j++)
        {
            printf("%c", palavras[i][j]);
        }

        if (palavrasEncontradas[i] == 1)
        {
            printf(" está no texto!\n");
        }
        else
        {
            printf(" não está no texto!\n");
        }
    }
    printf("\n");

    return 0;
}
