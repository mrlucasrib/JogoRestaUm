#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "restaum.h"

#define CMD_SIZE 30

Tabuleiro geraTabuleiro(int m, int n) {
    Tabuleiro t;
    t = (Tabuleiro) malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        t[i] = (int *) malloc(n * sizeof(int));
    }
}

int main(int argc, char *argv[]) {
    printf("Jogo Resta Um! \n");
    Tabuleiro t;
    FILE *file;

    if (argc > 0) {
        file = fopen(argv[1], 'r');
        t = importaTabuleiro(file);
    } else {
        file = fopen("out.txt", 'w');
        int m = rand() % 20, n = rand() % 20;
        t = geraTabuleiro(m, n);
    }
    printf("Um jogo foi %s\n\n", argc > 0 ? "criado" : "importado");

    do {
        Jogada j;
        char cmd[CMD_SIZE];
        exibeTabuleiro(t);
        fgets(cmd, CMD_SIZE, stdin);
        char *token = strtok(cmd, " ");
        printf("%s\n", token);

        if (!strcmp(token, "c") || !strcmp(token, "b") ||
            !strcmp(token, "e") || !strcmp(token, "c")) {
            j.direcao = (Direcao) token;
            token = strtok(NULL, " ");
            j.x = atoi(token);
            token = strtok(NULL, " ");
            j.y = atoi(token);
            fazJogada(t, j);
        } else if (!strcasecmp(token, "ajuda")) {
            token = strtok(NULL, " ");
            criaJogada(t);
        } else if (!strcasecmp(token, "salvar")) {
            salvaTabuleiro(t, file);
        } else if (!strcasecmp(token, "sair")) {
            return 0;
        } else {
            printf("Comando invalido");
        }


    } while (verificaSeVenceuOuPerdeu(t));

    printf("Voce %s o jogo.", verificaSeVenceu(t) ? "venceu" : "perdeu");
    fclose(file);
    return 0;
}
