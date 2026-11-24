#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

// AS CORES DO JOGO
#define COR_RESET   "\033[0m"
#define COR_ROBO    "\033[1;32m" 
#define COR_VIRUS   "\033[1;31m" 
#define COR_AVISO   "\033[1;33m"  
#define COR_LEGENDA "\033[1;37m" 
#define COR_CURSOR  "\033[7m"    
#define COR_ERRO    "\033[0;31m"  
#define COR_VERDE "\033[38;2;35;159;83m"
#define COR_VERDE_CLARO "\033[38;2;43;255;136m"

#define LINHAS 5
#define COLUNAS 10 

#define ESTADO_MENU 0
#define ESTADO_LOJA 1
#define ESTADO_POSICIONANDO 2
#define ESTADO_TURNO 3 
#define ESTADO_DERROTA 4
#define ESTADO_VITORIA 5

//As infos de cada *
typedef struct {
    char ocupante; //Quem esta naquele *
    int hp;        // Vida de quem esta no *
    int dano;      // Dano que o ocupante causa
} Celula;

//Todas as informações da partida
typedef struct {
    Celula matriz[LINHAS][COLUNAS];
    int bits;
    int turno_atual;
    int integridade_nucleo;
    int segundos_passados; 
    int virus_v_restantes;
    int virus_t_restantes;
    int virus_r_restantes;
    int estado;
    int estado_anterior;
    int cursor_l;
    int cursor_c;
    char robo_selecionado;
    int custo_selecionado;
} EstadoJogo;

//Adicionar aqui o dicionário das funções que vcs criarem
void inicializar_tabuleiro(EstadoJogo *jogo);
void adicionar_entidade(EstadoJogo *jogo, int l, int c, char tipo); 
int carregar_jogo(EstadoJogo *jogo, const char *nome_arquivo);
int salvar_jogo(const EstadoJogo *jogo, const char *nome_arquivo);
void renderizar_interface(const EstadoJogo *jogo);
void processar_robos(EstadoJogo *jogo);
void spawnar_virus(EstadoJogo *jogo);
void mover_virus(EstadoJogo *jogo);
void verificar_condicoes(EstadoJogo *jogo);
void atualizar_estatisticas(int venceu, int tempo_segundos);
void exibir_estatisticas();

#endif