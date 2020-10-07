#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "restaum.h"

#define CMD_SIZE 30

Tabuleiro geraTabuleiro(int m, int n) {
    Tabuleiro t;
    t.Tab = malloc(m * sizeof *t.Tab);
    for (int i = 0; i < m; i++) {
        t.Tab[i] = (int *) malloc(n * sizeof *t.Tab[i]);
    }
    t.m = m;
    t.n = n;
    return t;
}

void inicializaTabuleiro(Tabuleiro *t) {
    for (int i = 0; i < t->m; i++) {
        for (int j = 0; j < t->n; j++) {
            t->Tab[i][j] = j % 2 == 0 ? Disponivel : Ocupado;
        }
    }
}

void exibeTabuleiro(Tabuleiro *t) {
    for (int i = 0; i < t->m; ++i) {
        for (int j = 0; j < t->n; ++j) {
            printf("%d\t", t->Tab[i][j]);
        }
        printf("\n");
    }
}


bool fazJogada(Tabuleiro *t, Jogada *j) {
    bool movido = false;
    switch (j->direcao) {
        case Direita:
            if (t->Tab[j->x][j->y + 1] == Ocupado && t->Tab[j->x][j->y + 2] == Disponivel) {
                t->Tab[j->x][j->y + 1] = Disponivel;
                t->Tab[j->x][j->y + 2] = Ocupado;
                movido = true;
            }
            break;
        case Esquerda:
            if (t->Tab[j->x][j->y - 1] == Ocupado && t->Tab[j->x][j->y - 2] == Disponivel) {
                t->Tab[j->x][j->y - 1] = Disponivel;
                t->Tab[j->x][j->y - 2] = Ocupado;
                movido = true;
            }
            break;
        case Baixo:
            if (t->Tab[j->x + 1][j->y] == Ocupado && t->Tab[j->x + 2][j->y] == Disponivel) {
                t->Tab[j->x + 1][j->y] = Disponivel;
                t->Tab[j->x + 2][j->y] = Ocupado;
                movido = true;
            }
            break;
        case Cima:
            if (t->Tab[j->x - 1][j->y] == Ocupado && t->Tab[j->x - 2][j->y] == Disponivel) {
                t->Tab[j->x - 1][j->y] = Disponivel;
                t->Tab[j->x - 2][j->y] = Ocupado;
                movido = true;
            }
            break;
    }
    return movido;
}

Resultado verificaSeVenceuOuPerdeu(Tabuleiro *t) {
    int pinos = 0;
    for (int i = 0; i < t->m; i++) {
        for (int j = 0; j < t->n; j++) {
            if (t->Tab[i][j] == Ocupado) { // Verifica é possivel mover o pino para alguma direção
                if (t->Tab[i][j + 1] == Ocupado && t->Tab[i][j + 2] == Disponivel ||
                    t->Tab[i][j - 1] == Ocupado && t->Tab[i][j - 2] == Disponivel ||
                    t->Tab[i + 1][j] == Ocupado && t->Tab[i + 2][j] == Disponivel ||
                    t->Tab[i - 1][j] == Ocupado && t->Tab[i - 2][j] == Disponivel)
                    return Inconclusivo;
                ++pinos;
            }
            if(pinos == 1)
                return Venceu;
            return Perdeu;
        }
    }
}

int main(int argc, char *argv[]) {
    printf("Jogo Resta Um! \n");
    Tabuleiro t;
    FILE *file;

    if (argc > 1) {
//        file = fopen(argv[1], 'r');
//        t = importaTabuleiro(file);
    } else {
//        file = fopen("out->txt", 'w');
//        int m = rand() % 20, n = rand() % 20;
//        t = geraTabuleiro(6, 8);
    }
    t = geraTabuleiro(6, 7);
    inicializaTabuleiro(&t);
    printf("Um jogo foi %s\n\n", argc < 1 ? "criado" : "importado");

    do {
        Jogada j;
        char cmd[CMD_SIZE];
        exibeTabuleiro(&t);
        fgets(cmd, CMD_SIZE, stdin);
        char *token = strtok(cmd, " ");

        if (!strcmp(token, "c") || !strcmp(token, "b") ||
            !strcmp(token, "e") || !strcmp(token, "d")) {
            j.direcao = (Direcao) token[0];
            token = strtok(NULL, " ");
            j.x = atoi(token);
            token = strtok(NULL, " ");
            j.y = atoi(token);
            fazJogada(&t, &j);
        } else if (!strcasecmp(token, "ajuda")) {
            token = strtok(NULL, " ");
//            criaJogada(t);
        } else if (!strcasecmp(token, "salvar")) {
//            salvaTabuleiro(t, file);
        } else if (!strcasecmp(token, "sair")) {
            return 0;
        } else {
            printf("Comando invalido\n");
        }


    } while (verificaSeVenceuOuPerdeu(&t) == Inconclusivo);

//    printf("Voce %s o jogo->", verificaSeVenceu(&t) ? "venceu" : "perdeu");
    fclose(file);
    return 0;
}
