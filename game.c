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

//Adiciona a entidade na linha e na coluna (Valores temporarios pra ver se ta balanciado)
void adicionar_entidade(EstadoJogo *jogo, int l, int c, char tipo) {
    jogo->matriz[l][c].ocupante = tipo;
    
    switch (tipo) {

        // Robôs
        case 'A': jogo->matriz[l][c].hp = 100; jogo->matriz[l][c].dano = 40; break;
        case 'B': jogo->matriz[l][c].hp = 300; jogo->matriz[l][c].dano = 0;  break;
        case 'G': jogo->matriz[l][c].hp = 80;  jogo->matriz[l][c].dano = 0;  break;
        
        // Vírus
        case 'V': jogo->matriz[l][c].hp = 80;  jogo->matriz[l][c].dano = 50; break;
        case 'R': jogo->matriz[l][c].hp = 50;  jogo->matriz[l][c].dano = 40; break;
        case 'T': jogo->matriz[l][c].hp = 180; jogo->matriz[l][c].dano = 25; break;
        case 'X': jogo->matriz[l][c].hp = 0;   jogo->matriz[l][c].dano = 0;  break; 
        
        //Caso nn tenha nenhuma entidade
        case '*': jogo->matriz[l][c].hp = 0;   jogo->matriz[l][c].dano = 0;  break;
    }
    
}
int carregar_jogo(EstadoJogo *jogo, const char *nome_arquivo) {
    //Abre o arquivo
    FILE *arquivo = fopen(nome_arquivo, "rb");


    if (arquivo == NULL) {
        return 0;
    }
   
    //Le os dados do arquivo
    fread(jogo, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    return 1;
}

int salvar_jogo(const EstadoJogo *jogo, const char *nome_arquivo) {


    //Aponta para um arquivo e abre ele
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de save!\n");
        return 0;
    }
   
    // Escreve toda a struct no arquivo;
    fwrite(jogo, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    return 1;
}