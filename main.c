#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    EstadoJogo *jogo = (EstadoJogo *)malloc(sizeof(EstadoJogo));
    if (jogo == NULL) {
        printf("ERRO CRITICO: Falha ao alocar memoria para o sistema do jogo!\n");
        return 1; 
    }
}