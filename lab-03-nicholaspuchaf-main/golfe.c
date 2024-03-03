
#include <stdio.h>
#include <stdlib.h>

#include "partida.h"

int main()
{

    int num_partidas = 0;

    scanf("%d", &num_partidas);

    for (int i = 0; i < num_partidas; i++)
    {
        realiza_tudo(i);
    }

    return 0;
}
