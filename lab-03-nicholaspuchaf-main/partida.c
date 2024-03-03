#include <stdlib.h>
#include <stdio.h>

#include "circuito.h"
#include "partida.h"

void leitura_dados_partida(partida *partida1, int num_partida)
{
    /*
        Recebe o vetor de partida para que possa alterar os valores da struct
        Está função irá ler o numero de jogadores de uma partida, irá ler o numero de circuitos, o numero de equipamentos, depois irá rodar
        um loop para cada circuito para ler as jogadas de cada jogador
    */
    partida1->circuito_mais_dificil[0] = 0;
    partida1->circuito_mais_dificil[1] = 0;

    partida1->identificacao_partida = num_partida;
    scanf("%d", &(partida1->num_jogadores));
    scanf("%d", &(partida1->num_circuitos));
    scanf("%d", &(partida1->num_equipamentos));
}

void calculo_aluguel(partida *partida1)
{
    /*
        Recebe o vetor de partida como parametro para que possa alterar dados da struct
        Esta funcao irá calulcar o valor do alguel de determinada partida, uma vez já obtida os dados da partida
    */
    partida1->aluguel_valor = (10.0 * partida1->num_circuitos) + (17.5 * partida1->num_equipamentos);
}

void inicializacao_jogadores(partida *partida1)
{
    /*
        O parametro que recebe é o vetor para que se possa alterar os dados da struct
        Esta funcao inicializa o vetor dinamico de jogadores com o identificar de 0 a o num_jogadores para que possa depois ser somadas as jogadas uma vez que a ordem das jogadas é sempre a mesma.
        Além disso, inicializa o soma_jogadas com 0, e o circuito mais dificil, para futura comparacao
    */

    partida1->jogadores = malloc(partida1->num_jogadores * (sizeof(jogador)));

    for (int i = 0; i < partida1->num_jogadores; i++)
    {
        (partida1->jogadores + i)->identificador = i;
        (partida1->jogadores + i)->soma_jogadas = 0;
    }
}

void free_jogadores(partida partida1)
{
    /*
        Esta funcao nao irá alterar dados dentro da struct, apenas liberar a memoria do vetor dinamico jogadores, por isso o parametro é o valor da struct
    */
    free(partida1.jogadores);
}

void impressao_relatorio(partida partida1)
{
    /*
        Nao recebe o vetor de partida, mas sim o "valor" da struct partida porque a funcao n vai alterar valor, apenas realizar leitura
        Impressao de relatorio conforme indicado pelo lab03
    */
    printf("Partida %d\n", partida1.identificacao_partida + 1);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", partida1.num_jogadores, partida1.num_circuitos, partida1.num_equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", partida1.aluguel_valor);
    for (int j = 0; j < partida1.num_jogadores; j++)
    {
        printf("Jogador %d: %d\n", j + 1, partida1.jogadores[j].soma_jogadas);
    }
    printf("Circuito mais dificil: %d\n", partida1.circuito_mais_dificil[0]);
    printf("##########\n");
}

void calculo_das_jogadas_somadas(partida partida1, int i)
{
    /*
        Esta funcao irá trabalhar com o vetor de jogadas de um circuito e somar todas as jogadas dos jogadores j às suas respectivadas soma_jogadas.
        A variavel i que é passada como parametro é utilizada para identificar qual circuito será analisado.
    */

    for (int j = 0; j < partida1.num_jogadores; j++)
    {
        partida1.jogadores[j].soma_jogadas += partida1.circuitos[i].jogadas_dos_participantes[j];
    }
}

void calculo_circuito_mais_dificil(partida *partida1, int i)
{
    /*
        Esta funcao irá trabalhar com o vetor jogadas, para identificar o circuito com maior dificuldade (maior numero de jogadas necessárias para terminar), como cada circuito já possui o numero total de jogadas, apenas será necessário analisar todos os circuitos
    */

    if (((partida1->circuitos) + i)->total_jogadas_circuito > partida1->circuito_mais_dificil[1])
    {
        partida1->circuito_mais_dificil[0] = ((partida1->circuitos) + i)->identificacao_do_circuito;
        partida1->circuito_mais_dificil[1] = ((partida1->circuitos) + i)->total_jogadas_circuito;
    }
}

void leitura_dos_circuitos(partida *partida1)
{

    /*
        Esta funcao irá ler o vetor dinamicamente alocado de circuitos e colocar cada jogada
    */

    (partida1->circuitos) = malloc(partida1->num_circuitos * sizeof(circuito));

    for (int i = 0; i < partida1->num_circuitos; i++)
    {
        (partida1->circuitos)[i] = leitura_dados_circuito(partida1->num_jogadores);

        // AGORA IRÁ SOMAR AS JOGADAS DE CADA JOGADOR
        calculo_das_jogadas_somadas(*partida1, i);

        // AGORA IRÁ CALCULAR O CIRCUITO MAIS DIFICIL
        calculo_circuito_mais_dificil(partida1, i);
    }
}

void free_circuitos_todos(partida partida1)
{
    for (int i = 0; i < partida1.num_circuitos; i++)
    {
        free_circuito(partida1.circuitos[i]);
    }
    // free(partida1.circuitos);
}

void realiza_tudo(int num_partida)
{
    /*
        Esta funcao realiza todas as funcoes da partida, desde coleta de dados, impressao do relatorio e free da memoria.
    */

    partida *partida1;

    partida1 = malloc(sizeof(partida));

    leitura_dados_partida(partida1, num_partida);
    calculo_aluguel(partida1);
    inicializacao_jogadores(partida1);

    leitura_dos_circuitos(partida1);

    impressao_relatorio(*partida1);
    free_jogadores(*partida1);
    free_circuitos_todos(*partida1);

    free(partida1->circuitos);
    free(partida1);
}
