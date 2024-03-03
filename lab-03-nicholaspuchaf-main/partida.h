#ifndef PARTIDA_H
#define PARTIDA_H

#include "circuito.h"

typedef struct
{
    int identificador;
    int soma_jogadas;

} jogador;

typedef struct
{
    double aluguel_valor;
    int identificacao_partida;
    int num_jogadores;
    int num_circuitos;
    int num_equipamentos;
    circuito *circuitos;
    jogador *jogadores;
    int circuito_mais_dificil[2]; // 0: qual circuito é, 1: quantas jogadas necessárias

} partida;

void leitura_dados_partida(partida *partida1, int num_partida);

void calculo_aluguel(partida *partida1);

void inicializacao_jogadores(partida *partida1);

void impressao_relatorio(partida partida1);

void calculo_das_jogadas_somadas(partida partida1, int i);

void calculo_circuito_mais_dificil(partida *partida1, int i);

void leitura_dos_circuitos(partida *partida1);

void free_circuitos_todos(partida partida1);

void realiza_tudo(int num_partida);

#endif