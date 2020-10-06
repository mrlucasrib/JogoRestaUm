//
// Created by lucas on 06/10/2020.
//

#include <bits/types/FILE.h>

#ifndef RESTAUM_RESTAUM_H
#define RESTAUM_RESTAUM_H
typedef enum {
    Cima = 99, Baixo = 98, Esquerda = 101, Direita = 100
} Direcao;
typedef enum {
    Disponivel = 0, Ocupado = 1, Inutilizavel = -1
} Posicao;

typedef struct {
    int x, y;
    Direcao direcao;
} Jogada;

typedef int **Tabuleiro;

Jogada criaJogada(Tabuleiro t);

int fazJogada(Tabuleiro t, Jogada j);

int verificaSeVenceuOuPerdeu(Tabuleiro t);

int salvaTabuleiro(Tabuleiro t, FILE *f);

void exibeTabuleiro(Tabuleiro t);

int verificaSeVenceu(Tabuleiro t);

Tabuleiro importaTabuleiro(FILE *f);

Tabuleiro geraTabuleiro(int m, int n);



#endif //RESTAUM_RESTAUM_H
