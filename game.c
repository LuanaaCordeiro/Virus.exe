#include "game.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa as informações no tabuleiro
void inicializar_tabuleiro(EstadoJogo *jogo)
{
    jogo->bits = 50;                     // Começa o jogo com 50 bits
    jogo->turno_atual = 1;               // Turno inicial
    jogo->onda_atual = 1;                // Onda inicial
    jogo->integridade_nucleo = 100;      // Quantidade de vida que o nucleo começa

    jogo->segundos_passados = 0;         // Inicia o turno com o tempo zerado (isso é pra progressão do jogo, ok? o tempo que cada virus anda, cada virus/robo atira, etc)

    jogo->virus_v_restantes = 3;         // Quantidade de Virus
    jogo->virus_t_restantes = 2;         // da
    jogo->virus_r_restantes = 0;         // Primeira onda

    jogo->estado = ESTADO_MENU;          // Estado 0, menu inicial
    jogo->estado_anterior = ESTADO_MENU; // O estado padrao pra quando ele for voltar
    jogo->cursor_l = 0;                  // Cursor para
    jogo->cursor_c = 1;                  // adicionar os robos
    jogo->robo_selecionado = ' ';        // Selecionar o robo na hr de por no tabuleiro
    jogo->custo_selecionado = 0;         // e seu custo

    // Preenche o tabuleiro
    for (int l = 0; l < LINHAS; l++)
    {
        for (int c = 0; c < COLUNAS; c++)
        {
            jogo->matriz[l][c].ocupante = '*';
            jogo->matriz[l][c].hp = 0;
            jogo->matriz[l][c].dano = 0;
        }
    }
}