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

Tabuleiro importaTabuleiro(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Arquivo não encontrado");
        exit(1);
    }
    int m, n;
    fscanf(file, "%d %d", &m, &n);
    Tabuleiro t = geraTabuleiro(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(file, "%d", &t.Tab[i][j]);
        }
    }
    fclose(file);
    return t;
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
        }
    }
    if (pinos == 1)
        return Venceu;
    return Perdeu;


}

bool salvaTabuleiro(Tabuleiro *t, char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    if (f == NULL)
        return false;
    fprintf(f, "%d %d", t->n, t->n);
    for (int i = 0; i < t->n; ++i) {
        for (int j = 0; j < t->m; ++j) {
            fprintf(f, "%d ", t->Tab[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return true;
}

int main(int argc, char *argv[]) {
    printf("Jogo Resta Um! \n");
    Tabuleiro t;

    if (argc > 1) {
        t = importaTabuleiro(argv[1]);
    } else {
        int m = rand() % 20, n = rand() % 20;
        t = geraTabuleiro(m, n);
        inicializaTabuleiro(&t);
    }
    printf("Um jogo foi %s\n\n", argc > 1 ? "criado" : "importado");

    do {
        Jogada j;
        char cmd[CMD_SIZE];
        exibeTabuleiro(&t);
        fgets(cmd, CMD_SIZE, stdin);
        char *token = strtok(cmd, " ");

        if (!strcmp(token, "c") || !strcmp(token, "b") ||
            !strcmp(token, "e") || !strcmp(token, "d")) {
            j.direcao = (Direcao) token[0];
            j.x = token[2] - 65; // 65 == 'A'
            j.y = token[3] - 65;
            fazJogada(&t, &j);
        } else if (!strcasecmp(token, "ajuda")) {
            token = strtok(NULL, " ");
//            criaJogada(t);
        } else if (!strcasecmp(token, "salvar")) {
            token = strtok(NULL, " ");
            salvaTabuleiro(&t, token);
        } else if (!strcasecmp(token, "sair")) {
            return 0;
        } else {
            printf("Comando invalido\n");
        }


    } while (verificaSeVenceuOuPerdeu(&t) == Inconclusivo);

//    printf("Voce %s o jogo->", verificaSeVenceu(&t) ? "venceu" : "perdeu");
    return 0;
}
