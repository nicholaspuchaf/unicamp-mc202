#include <stdio.h>

#define N 10000

void leitura_frutas(int lista[N], int num)
{

    int i = 0;

    for (i = 0; i < num; i++)
    {
        scanf("%d", &lista[i]);
    }
}

void calcula_vendas(int lista[N], int num);

int main()
{

    int frutasVendidas[N];
    int num = 0;
    int vendas[3] = {0, 0, 0};
    int maiorStreak[2] = {0, 0};
    int streakAtual[2] = {0, 0};

    // LEITURA DAS FRUTAS
    scanf("%d", &num);

    leitura_frutas(frutasVendidas, num);
    int i = 0;
    for (i = 0; i < num; i++)
    {
        if (frutasVendidas[i] == 5)
        {
            vendas[0]++;
        }
        else if (frutasVendidas[i] == 7)
        {
            vendas[1]++;
        }
        else if (frutasVendidas[i] == 10)
        {
            vendas[2]++;
        }

        if (streakAtual[0] == frutasVendidas[i])
        {
            streakAtual[1]++;
        }
        else
        {
            if (maiorStreak[1] < streakAtual[1])
            {
                maiorStreak[0] = streakAtual[0];
                maiorStreak[1] = streakAtual[1];
            }
            streakAtual[0] = frutasVendidas[i];
            streakAtual[1] = 1;
        }
    }

    if (maiorStreak[1] < streakAtual[1])
            {
                maiorStreak[0] = streakAtual[0];
                maiorStreak[1] = streakAtual[1];
            }

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", vendas[0], vendas[1], vendas[2]);
    printf("James vendeu %d saladas de %d reais consecutivamente\n", maiorStreak[1], maiorStreak[0]);

    return 0;
}
