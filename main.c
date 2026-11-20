#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {

    EstadoJogo *jogo = (EstadoJogo *)malloc(sizeof(EstadoJogo));
    if (jogo == NULL) {
        printf("ERRO CRITICO: Falha ao alocar memoria para o sistema do jogo!\n");
        return 1; 
    }
 
    // Tela inicial para carregar novo jogo ou jogo salvo
    system("cls || clear");  //Isso aqui é pra limpar o terminal

    printf(COR_VERDE "================================================================================\n" COR_RESET);
    printf(COR_VERDE "                              V I R U S . E X E            \n");
    printf(COR_VERDE "================================================================================\n" COR_RESET);
    printf("\n");
    printf(COR_LEGENDA " [1] Iniciar Novo Jogo\n" COR_RESET);
    printf(COR_LEGENDA " [2] Restaurar Jogo Anterior\n" COR_RESET);
    printf("\n> Aguardando input... ");

    //Aqui ele torna o menu funcional, 1 é novo jogo e 2 é carregar jogo ou iniciar caso nn tenha jogo salvo
    int inicializou = 0;
    while (!inicializou) {

        //Esse _kbhit verifica se alguma tecla foi apertada
        if (_kbhit()) {
            int tecla_boot = _getch(); //O _getch verifica qual a tecla que foi apertada
            if (tecla_boot == '1') {
                inicializar_tabuleiro(jogo);
                inicializou = 1;
            } 
            else if (tecla_boot == '2') {
                if (carregar_jogo(jogo, "savegame.bin")) {
                    if (jogo->estado != ESTADO_DERROTA && jogo->estado != ESTADO_VITORIA) {
                        jogo->estado = ESTADO_MENU;
                        jogo->estado_anterior = ESTADO_MENU;
                    }
                } else {
                    inicializar_tabuleiro(jogo);
                }

                inicializou = 1;
            }
        }
    }

    renderizar_interface(jogo);

}