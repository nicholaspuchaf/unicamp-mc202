#ifndef CIRCUITOS_H
#define CIRCUITOS_H

// typedef circuito circuito;

typedef struct
{

    int identificacao_do_circuito;
    int num_jogadores;
    int total_jogadas_circuito;
    int *jogadas_dos_participantes; // VETOR DINAMINCAMENTE ALOCADO PARA AS JOGADAS DO PARTICIPANTES, MESMA ORDEM DOS JOGADORES EM UMA MESMA PARTIDA

} circuito;

circuito leitura_dados_circuito(int num_jog);

void free_circuito(circuito circuito1);

#endif