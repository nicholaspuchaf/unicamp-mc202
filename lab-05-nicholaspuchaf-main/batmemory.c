#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vetor.h"

vetor *bat_alloc(int tamanho, int *lista, vetor *bat_vetor)
{
    /*
        Esta função irá copiar no vetor já existente bat_vetor os novos elementos desejados
        Ela irá também verificar se há espaço no vetor para fazer a cópia, se não terá necessidade de realocar o vetor!
        Funcao irá retornar um novo ponteiro de vetor porque pode ser que seja necessário duplicar o vetor, e assim haverá uma nova posicao
    */

    int posicao = 0;

    posicao = acha_posicao_vazia(bat_vetor, tamanho + 1);
    while (posicao == -1)
    {
        bat_vetor = duplica_vetor(bat_vetor);
        posicao = acha_posicao_vazia(bat_vetor, tamanho + 1);
    }
    adiciona_elemento(bat_vetor, tamanho, posicao);
    posicao++;
    for (int i = 0; i < tamanho; i++)
    {
        adiciona_elemento(bat_vetor, lista[i], posicao + i);
    }
    printf("%d\n", posicao - 1);
    // imprime_vetor(bat_vetor);

    return bat_vetor;
}

void bat_print(vetor *bat_vetor, int endereco)
{
    /*
        Dado um vetor, e o endereco, o primeiro inteiro na posicao "endereco" representa o tamanho do vetor, e os seguintes o vetor desejado
        Nao tem retorno
    */
    int tamanho = bat_vetor->vetor[endereco] + endereco + 1;
    for (int i = endereco + 1; i < tamanho; i++)
    {
        printf("%d ", bat_vetor->vetor[i]);
    }
    printf("\n");
}

void bat_uso(vetor *bat_vetor)
{
    /*
        Esta funcao indica quantas memorias estao em uso do bat-computador, nao há retorno é apenas uma funcao de impressao!
    */
    printf("%d de %d\n", bat_vetor->emUso, bat_vetor->alocado);
}

vetor *bat_free(vetor *bat_vetor, int endereco)
{
    /*
        Dada um endereco, será liberado o espaco no vetor do bat_vetor, o espaco liberado será do tamanho do valor bat_vetor->vetor[endereco]
        O retorno será um novo vetor, que poderá ser diminuido caso 3/4 da "direita" dele estiverem livres!
    */
    int tamanho = bat_vetor->vetor[endereco] + 1 + endereco;
    for (int i = endereco; i < tamanho; i++)
    {
        bat_vetor->vetor[i] = -1;
        bat_vetor->emUso--;
    }

    // VERIFICAR SE 3/4 do vetor n estao sendo utilizados

    for (int i = bat_vetor->alocado / 4; i < bat_vetor->alocado; i++)
    {

        if (bat_vetor->vetor[i] != -1)
        {
            // imprime_vetor(bat_vetor);
            return bat_vetor;
        }
    }

    if (bat_vetor->alocado > 8)
    {
        bat_vetor = reduz_vetor(bat_vetor);
    }

    // imprime_vetor(bat_vetor);
    return bat_vetor;
}

vetor *leitura_funcao(vetor *bat_vetor)
{

    /*

    Esta funcao irá realizar o gerenciamento das funcoes do programa, irá ler o comando do usuário e também as entradas necessaŕias do comando
    A partir disso irá direcionar qual funcoa será chamada, bat-alloc, bat-free, bat-uso, bat-print junto com os devidos parametros!
    O retorno dela é um ponteiro de vetor, porque ao longo da execucao o vetor pode ser redimensionado e caso isso aconteça será necessário realocar o vetor!

    */

    char *linha = malloc(2 * sizeof(char));
    char letra;

    scanf("\n%c", &letra);
    int i = 0;
    linha[0] = '\0';
    linha[1] = '\0';
    while (letra != ' ')
    {
        /*
            Nesta parte do código estava dando erro nas funcoes strlen e strcpy porque o vetor linha nao tinha /0 no final,
            entao adicionei 2 posicoes no final dele sempre na linha nova_linha = malloc((tamlinha + 2)*sizeof(char)); para
            que haja espaço para colocar mais um caracter e tambem o /0 no final, por isso o + 2 junto com o tamLinha
        */

        linha[i] = letra;
        i++;
        int tamLinha = strlen(linha);
        char *nova_linha = malloc((tamLinha + 2) * sizeof(char));

        for (int j = 0; j < tamLinha + 2; j++)
        {
            nova_linha[j] = '\0';
        }

        if (linha)
        {
            strcpy(nova_linha, linha);
            free(linha);
        }

        linha = nova_linha;
        scanf("%c", &letra);

        if (strcmp(linha, "bat-uso") == 0)
        {
            bat_uso(bat_vetor);
            free(linha);
            return bat_vetor;
        }
    }

    if (strcmp(linha, "bat-alloc") == 0)
    {
        int tam;
        scanf("%d", &tam);

        int *lista = malloc(tam * sizeof(int));
        for (int i = 0; i < tam; i++)
        {
            scanf("%d", lista + i);
        }
        bat_vetor = bat_alloc(tam, lista, bat_vetor);
        free(lista);
    }
    else if (strcmp(linha, "bat-free") == 0)
    {

        int pos;
        scanf("%d", &pos);
        bat_vetor = bat_free(bat_vetor, pos);
    }
    else if (strcmp(linha, "bat-uso") == 0)
    {
        bat_uso(bat_vetor);
    }
    else if (strcmp(linha, "bat-print") == 0)
    {
        int pos;
        scanf("%d", &pos);
        bat_print(bat_vetor, pos);
    }

    free(linha);
    return bat_vetor;
}

int main()
{

    int N;
    scanf("%d ", &N);

    /*
        O vetor deve sempre começar com 8 inteiros de tamanho então vou iniciar ele com esse tamanho
    */

    vetor *bat_vetor;
    bat_vetor = cria_vetor(8);

    while (N > 0)
    {
        N--;
        bat_vetor = leitura_funcao(bat_vetor);
    }

    destroi_vetor(bat_vetor);

    return 0;
}
