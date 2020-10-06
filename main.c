#include <stdio.h>

typedef enum {
    Cima, Baixo, Esquerda, Direita
} Direcao;
typedef enum {
    Disponivel, Ocupado, Inutilizavel
} Posicao;

typedef struct {
    int x, y;
    Direcao direcao;
} Jogada;

typedef int **Tabuleiro;

Jogada criaJogada(Tabuleiro t);

int fazJogada(Tabuleiro t, Jogada j);

int VerificaSeVenceuOuPerdeu(Tabuleiro t);





int main() {
    printf("Hello, World!\n");
    return 0;
}
