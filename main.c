#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "restaum.h"

#define CMD_SIZE 30
#define MAX_JOGADAS 5

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
    for (int i = -1; i < t->m; ++i) {
        for (int j = -1; j < t->n; ++j) {
            if (j == -1)
                printf("%c\t", i == -1 ? ' ' : i + 1 + 65);
            else if (i == -1)
                printf("%c\t", j != t->n ? j + 65 : '\n');
            else
                printf("%d\t", t->Tab[i][j]);
        }
        printf("\n");
    }
}


bool fazJogada(Tabuleiro *t, Jogada *j) {
    bool movido = false;
    switch (j->direcao) {
        case Direita:
            if (j->y + 2 < t->n - 1)
                if (t->Tab[j->x][j->y] == Ocupado && t->Tab[j->x][j->y + 1] == Ocupado &&
                    t->Tab[j->x][j->y + 2] == Disponivel) {
                    t->Tab[j->x][j->y + 1] = Disponivel;
                    t->Tab[j->x][j->y + 2] = Ocupado;
                    t->Tab[j->x][j->y] = Disponivel;
                    movido = true;
                }
            break;
        case Esquerda:
            if (j->y - 2 >= 0)
                if (t->Tab[j->x][j->y] == Ocupado && t->Tab[j->x][j->y - 1] == Ocupado &&
                    t->Tab[j->x][j->y - 2] == Disponivel) {
                    t->Tab[j->x][j->y - 1] = Disponivel;
                    t->Tab[j->x][j->y - 2] = Ocupado;
                    t->Tab[j->x][j->y] = Disponivel;
                    movido = true;
                }
            break;
        case Baixo:
            if (j->x + 2 < t->m - 1)
                if (t->Tab[j->x][j->y] == Ocupado && t->Tab[j->x + 1][j->y] == Ocupado &&
                    t->Tab[j->x + 2][j->y] == Disponivel) {
                    t->Tab[j->x + 1][j->y] = Disponivel;
                    t->Tab[j->x + 2][j->y] = Ocupado;
                    t->Tab[j->x][j->y] = Disponivel;

                    movido = true;
                }
            break;
        case Cima:
            if (j->x - 2 >= 0)
                if (t->Tab[j->x][j->y] == Ocupado && t->Tab[j->x - 1][j->y] == Ocupado &&
                    t->Tab[j->x - 2][j->y] == Disponivel) {
                    t->Tab[j->x - 1][j->y] = Disponivel;
                    t->Tab[j->x - 2][j->y] = Ocupado;
                    t->Tab[j->x][j->y] = Disponivel;
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
                if (i - 2 >= 0 && j - 2 >= 0 && i+3 <= t->m && j + 3 <= t->n)
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

bool criaEFazJogada(Tabuleiro *t) {
    for (int i = 0; i < t->m; ++i) {
        for (int k = 0; k < t->n; ++k) {
            for (Direcao w = Baixo; w <= Esquerda; ++w) {
                Jogada j;
                j.x = i;
                j.y = k;
                j.direcao = w;
                if (fazJogada(t, &j))
                    return true;
            }

        }
    }
    return false;
}

bool verificaSeExistemJogadas(Tabuleiro *t) {
    Tabuleiro t2 = *t;
    for (int i = 0; i < MAX_JOGADAS; ++i) {
        if (!criaEFazJogada(&t2)) // TESTA ATÉ MAX_JOGADAS OU NÃO CONSEGUIR FAZER MOVIMENTOS
            return false; // SE NAO TIVER MAIS JOGADAS RETORNA A FALSE

    }
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
            for (int i = 0; i < (int) token[0]; ++i) {
                criaEFazJogada(&t);
                exibeTabuleiro(&t);
            }
        } else if (!strcasecmp(token, "salvar")) {
            token = strtok(NULL, " ");
            salvaTabuleiro(&t, token);
        } else if (!strcasecmp(token, "sair")) {
            return 0;
        } else {
            printf("Comando invalido\n");
        }


    } while (verificaSeExistemJogadas(&t));
    Resultado verifica = verificaSeVenceuOuPerdeu(&t);
    if (verifica == Venceu)
        printf("Voce venceu o jogo.");
    else if (verifica == Perdeu)
        printf("Voce perdeu o jogo.");
    return 0;
}
