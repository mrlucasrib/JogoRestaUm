//
// Created by lucas on 06/10/2020.
//

#include <bits/types/FILE.h>
#include <stdbool.h>

#ifndef RESTAUM_RESTAUM_H
#define RESTAUM_RESTAUM_H
typedef enum {
    Cima = 99, Baixo = 98, Esquerda = 101, Direita = 100
} Direcao;

typedef enum {
    Disponivel = 0, Ocupado = 1, Inutilizavel = -1
} Posisao;

typedef enum {
    Venceu, Perdeu, Inconclusivo
} Resultado;

typedef struct {
    int x, y;
    Direcao direcao;
} Jogada;

typedef struct {
    int **Tab;
    int m, n;
} Tabuleiro;


bool criaEFazJogada(Tabuleiro *t);

bool verificaSeExistemJogadas(Tabuleiro *t);

bool fazJogada(Tabuleiro *t, Jogada *j);

Resultado verificaSeVenceuOuPerdeu(Tabuleiro *t);

bool salvaTabuleiro(Tabuleiro *t, char *nomeArquivo);

void exibeTabuleiro(Tabuleiro *t);

Tabuleiro importaTabuleiro(char *nomeArquivo);

Tabuleiro geraTabuleiro(int m, int n);

void inicializaTabuleiro(Tabuleiro *t);


#endif //RESTAUM_RESTAUM_H
