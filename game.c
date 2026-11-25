#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// Inicializa as informações no tabuleiro
void inicializar_tabuleiro(EstadoJogo *jogo)
{
    jogo->bits = 50;                     // Começa o jogo com 50 bits
    jogo->turno_atual = 1;               // Turno inicial               
    jogo->integridade_nucleo = 100;      // Quantidade de vida que o nucleo começa

    jogo->segundos_passados = 0;         // Inicia o turno com o tempo zerado (isso é pra progressão do jogo, ok? o tempo que cada virus anda, cada virus/robo atira, etc)

    jogo->virus_v_restantes = 3;         // Quantidade de Virus
    jogo->virus_t_restantes = 2;         // da
    jogo->virus_r_restantes = 0;         // Primeiro turno

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

//Aqui ele vai imprimir as entidades em cada célula com suas cores e determina as cores do cursor caso ele esteja aparecendo
void imprimir_entidade(char entidade, int is_cursor) {


    if (is_cursor) {
        printf(COR_CURSOR);
    }


    if (entidade == '*') {
        if (is_cursor) {
            printf(" * ");
        } else {
            printf(COR_VERDE "*" COR_RESET);
        }
    }
    else if (entidade == 'A' || entidade == 'B' || entidade == 'G') {
        if (is_cursor) {
            printf(" %c ", entidade);
        } else {
            printf(COR_ROBO "%c" COR_RESET, entidade);
        }
    }
    else if (entidade == 'V' || entidade == 'R' || entidade == 'T') {
        if (is_cursor) {
            printf(" %c ", entidade);
        } else {
            printf(COR_VIRUS "%c" COR_RESET, entidade);
        }
    }
    else if (entidade == 'X') {
        if (is_cursor) {
            printf("\033[31m X ");
        } else {
            printf(COR_ERRO "X" COR_RESET);
        }
    }
    else {
        printf(" ");
    }


    if (is_cursor) {
        printf(COR_RESET);
    }
}

// Pega o cursor do terminal e joga para a primeira linha e coluna (Impede que a tela fique piscando)
void mover_cursor_topo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
}


void renderizar_interface(const EstadoJogo *jogo)
{
    static int ultimo_estado = -1;

    //Aqui se a tela tiver mudado, ele vai limpar a tela pra colocar a tela nova
    if (ultimo_estado != jogo->estado)
    {
        system("cls || clear");
        ultimo_estado = jogo->estado;
    }

    else
    {
        mover_cursor_topo();
    }


    //Aqui o cabeçalho
    printf(COR_VERDE "================================================================================\n" COR_RESET);
    printf(COR_VERDE "                              V I R U S . E X E            \n");
    printf(COR_VERDE "================================================================================\n" COR_RESET);

    printf(COR_LEGENDA " UNIDADES DEFENSIVAS (ROBOS)            AMEACAS VIRTUAIS (VIRUS)\n" COR_RESET);
    printf(COR_ROBO " [A] Atacante (30b) - Dano a distancia " COR_RESET " | " COR_VIRUS " <V> Comum      - Equilibrado\n" COR_RESET);
    printf(COR_ROBO " [B] Barreira (20b) - Alta vida        " COR_RESET " | " COR_VIRUS " <R> Atirador   - Dano a distancia\n" COR_RESET);
    printf(COR_ROBO " [G] Gerador  (25b) - Gera +15b/turno  " COR_RESET " | " COR_VIRUS " <T> Resistente - Alta vida\n" COR_RESET);
    printf(COR_VERDE "================================================================================\n" COR_RESET);

    printf(COR_VERDE_CLARO " [Turno: %02d/03]   [Bits: %04d]   [Integridade: %d%%]\n",
           jogo->turno_atual, jogo->bits, jogo->integridade_nucleo);
    printf(COR_VERDE "--------------------------------------------------------------------------------\n" COR_RESET);

   //Aqui é se o jogador perder
    if (jogo->estado == ESTADO_DERROTA)
    {
        printf("\n");
        printf(COR_ERRO"      +------------------------------------------------------------------+\n");
        printf("      |                                                                  |\n");
        printf("      |                     [ F A L H A  C R I T I C A ]                 |\n");
        printf("      |                                                                  |\n");
        printf("      |                O NUCLEO FOI TOTALMENTE CORROMPIDO.               |\n");
        printf("      |                          O SISTEMA CAIU.                         |\n");
        printf("      |                                                                  |\n");
        printf("      |                      Aperte 1 para Reiniciar                     |\n");
        printf("      |                        Aperte 0 para Sair                        |\n");
        printf("      |                                                                  |\n");
        printf("      +------------------------------------------------------------------+\n" COR_RESET);
        printf("\n> ");
    }
    
    //Aqui se o jogador ganhar
    else if (jogo->estado == ESTADO_VITORIA)
    {
        printf("\n");
        printf(COR_VERDE"      +------------------------------------------------------------------+\n");
        printf("      |                                                                  |\n");
        printf("      |                         [ S U C E S S O ]                        |\n");
        printf("      |                                                                  |\n");
        printf("      |                          AMEACA ELIMINADA!                       |\n");
        printf("      |                O SISTEMA ESTA SEGURO POR ENQUANTO...             |\n");
        printf("      |                                                                  |\n");
        printf("      |                       Aperte 1 para Reiniciar                    |\n");
        printf("      |                         Aperte 0 para Sair                       |\n");
        printf("      |                                                                  |\n");
        printf("      +------------------------------------------------------------------+\n" COR_RESET);
        printf("\n> ");
    }
   
    //Se o jogador nao perder nem ganhar aqui é o tabuleiro padrao
    else
    {
    
        printf("        " COR_ROBO "[NUC]" COR_RESET COR_VERDE_CLARO "    [1]    |    [2]    [3]    [4]    [5]    [6]    [7]    [8]    " COR_VIRUS "[SPAWN]" COR_RESET "\n");
        printf(COR_VERDE "--------------------------------------------------------------------------------\n" COR_RESET);


        for (int i = 0; i < LINHAS; i++)
        {
            printf(COR_VERDE_CLARO " [L%d] | " COR_RESET, i);

            for (int j = 0; j < COLUNAS; j++)
            {
                char entidade = jogo->matriz[i][j].ocupante;
                int is_cursor = (jogo->estado == ESTADO_POSICIONANDO && jogo->cursor_l == i && jogo->cursor_c == j);

                if (j == 0)
                {
                    printf(is_cursor ? " " : "  ");
                    imprimir_entidade(entidade, is_cursor);
                    printf(is_cursor ? " " : "  ");
                    printf("    ");
                }
                else if (j == 1)
                {
                    printf(is_cursor ? "" : " ");
                    imprimir_entidade(entidade, is_cursor);
                    printf(is_cursor ? "" : " ");
                    printf(COR_VERDE "    |    " COR_RESET);
                }
                else if (j >= 2 && j <= 8)
                {
                    printf(" ");
                    imprimir_entidade(entidade, 0);
                    printf(" ");
                    printf("    ");
                }
                else if (j == 9)
                {
                    printf("  ");
                    imprimir_entidade(entidade, 0);
                    printf("   ");
                }
            }

            printf("\n");
        }

        printf(COR_VERDE "--------------------------------------------------------------------------------\n" COR_RESET);

        if (jogo->estado == ESTADO_MENU)
        {
            printf(COR_AVISO "[ TERMINAL ] Aguardando input do Usuario...\n" COR_RESET);
            printf("Comandos: [1] Instalar Robo  |  [2] Iniciar Turno  | [3] Reiniciar Turno  | [0] Sair e Salvar\n> ");
        }
        else if (jogo->estado == ESTADO_LOJA)
        {
            if (jogo->estado_anterior == ESTADO_TURNO)
            {
                printf(COR_AVISO "[ LOJA ] Selecione o Sistema Defensivo (JOGO PAUSADO):\n" COR_RESET);
            }
            else
            {
                printf(COR_AVISO "[ LOJA ] Selecione o Sistema Defensivo:\n" COR_RESET);
            }

           if (jogo->bits >= 30) {
                printf(COR_LEGENDA "[1] Atacante (30b)\n" COR_RESET);
            } else {
                printf(COR_ERRO "[1] Atacante (30b) - SALDO INSUFICIENTE\n" COR_RESET);
            }
            printf("    > Objetivo: Dispara projeteis em linha reta a cada turno.\n\n");

            
            if (jogo->bits >= 20) {
                printf(COR_LEGENDA "[2] Barreira (20b)\n" COR_RESET);
            } else {
                printf(COR_ERRO "[2] Barreira (20b) - SALDO INSUFICIENTE\n" COR_RESET);
            }
            printf("    > Objetivo: Alta durabilidade, bloqueia o avanco inimigo.\n\n");

        
            if (jogo->bits >= 25) {
                printf(COR_LEGENDA "[3] Gerador  (25b)\n" COR_RESET);
            } else {
                printf(COR_ERRO "[3] Gerador  (25b) - SALDO INSUFICIENTE\n" COR_RESET);
            }
            printf("    > Objetivo: Gera +15 bits constantemente durante o turno\n\n");

            printf("[0] Voltar\n> ");
        }
        else if (jogo->estado == ESTADO_POSICIONANDO)
        {
            printf(COR_AVISO "[ INSTALACAO ] Robo [%c] selecionado.\n" COR_RESET, jogo->robo_selecionado);
            printf("Use as SETAS do teclado para mover o cursor. Aperte [ESPACO] para instalar ou [0] para cancelar.\n> ");
        }
        else if (jogo->estado == ESTADO_TURNO)
        {
            printf(COR_VIRUS "[ ALERTA ] TURNO EM ANDAMENTO! OS VIRUS ESTAO AVANCANDO!\n" COR_RESET);
            printf("Comandos: [1] Pausar (Abrir Loja)\n> ");
        }
        else if (jogo->estado == ESTADO_DERROTA)
        {
            printf(COR_ERRO "[ FALHA CRITICA ] O NUCLEO FOI TOTALMENTE CORROMPIDO. O SISTEMA CAIU.\n" COR_RESET);
            printf("Comandos: [0] Encerrar Sessao\n> ");
        }
        else if (jogo->estado == ESTADO_VITORIA)
        {
            printf(COR_LEGENDA "[ SUCESSO ] TURNO ELIMINADO! O SISTEMA ESTA SEGURO... POR ENQUANTO.\n" COR_RESET);
            printf("Comandos: [0] Encerrar Sessao\n> ");
        }
    }
}

//Função apra as ações dos robos funcionarem
void processar_robos(EstadoJogo *jogo)
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            char entidade = jogo->matriz[i][j].ocupante;


            if (entidade == 'G')
            {
                if (jogo->segundos_passados > 0 && jogo->segundos_passados % 2 == 0) //Vai gerar os bits a cada 2 seg
                {
                    jogo->bits += 15;
                }
            }


            else if (entidade == 'A')
            {
                if (jogo->segundos_passados > 0 && jogo->segundos_passados % 1 == 0) //Atira a cada 1 seg
                {
                    int dano_robo = jogo->matriz[i][j].dano;


                    for (int k = j + 1; k < COLUNAS; k++)
                    {
                        char alvo = jogo->matriz[i][k].ocupante;


                        if (alvo == 'V' || alvo == 'T' || alvo == 'R')
                        {
                            jogo->matriz[i][k].hp -= dano_robo;


                            if (jogo->matriz[i][k].hp <= 0)
                            {
                                adicionar_entidade(jogo, i, k, '*');
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void spawnar_virus(EstadoJogo *jogo)
{
    int total_restantes = jogo->virus_v_restantes + jogo->virus_t_restantes + jogo->virus_r_restantes;


    if (total_restantes > 0)
    {
        int linhas_validas = 0;
        for (int i = 0; i < LINHAS; i++)
        {
            if (jogo->matriz[i][0].ocupante != 'X')
                linhas_validas++;
        }


        if (linhas_validas > 0)
        {
            int linha_spawn;


            //Aqui é pra fazer o sorteio e ver se a linha foi perdida ou não
            do
            {
               
                linha_spawn = rand() % LINHAS; // O rand vai gerar um numero aleatorio e o modulo de linhas vai ser 0,1,2,3,4
            } while (jogo->matriz[linha_spawn][0].ocupante == 'X');


            //Vai spawnar os virus
            if (jogo->matriz[linha_spawn][9].ocupante == '*')
            {
                int sorteio = rand() % total_restantes;
                if (sorteio < jogo->virus_v_restantes)
                {
                    adicionar_entidade(jogo, linha_spawn, 9, 'V');
                    jogo->virus_v_restantes--;
                }
                else if (sorteio < jogo->virus_v_restantes + jogo->virus_t_restantes)
                {
                    adicionar_entidade(jogo, linha_spawn, 9, 'T');
                    jogo->virus_t_restantes--;
                }
                else
                {
                    adicionar_entidade(jogo, linha_spawn, 9, 'R');
                    jogo->virus_r_restantes--;
                }
            }
        }
    }
}
void mover_virus(EstadoJogo *jogo)
{
    for (int i = 0; i < LINHAS; i++)
    {
        //Caso o virus chegue na col 0
        char entidade = jogo->matriz[i][0].ocupante;
        if (entidade == 'V' || entidade == 'T' || entidade == 'R')
        {
            jogo->integridade_nucleo -= 20;
            if (jogo->integridade_nucleo < 0)
                jogo->integridade_nucleo = 0;


            adicionar_entidade(jogo, i, 0, 'X');


            for (int j = 1; j < COLUNAS; j++)
            {
                adicionar_entidade(jogo, i, j, '*');
            }
        }
    }


    //Dano que os virus causam
    for (int i = 0; i < LINHAS; i++)
    {


        if (jogo->matriz[i][0].ocupante == 'X')
            continue;


        for (int j = 1; j < COLUNAS; j++)
        {
            char entidade = jogo->matriz[i][j].ocupante;


            if (entidade == 'V' || entidade == 'T' || entidade == 'R')
            {
                int atacou_corpo_a_corpo = 0;


                if (entidade == 'R')
                {
                    for (int k = j - 1; k >= 0; k--)
                    {
                        char alvo = jogo->matriz[i][k].ocupante;
                        if (alvo == 'A' || alvo == 'B' || alvo == 'G')
                        {
                            jogo->matriz[i][k].hp -= jogo->matriz[i][j].dano;
                            if (jogo->matriz[i][k].hp <= 0)
                                adicionar_entidade(jogo, i, k, '*');
                            break;
                        }
                    }
                }


                else
                {
                    char alvo = jogo->matriz[i][j - 1].ocupante;
                    if (alvo == 'A' || alvo == 'B' || alvo == 'G')
                    {
                        jogo->matriz[i][j - 1].hp -= jogo->matriz[i][j].dano;
                        atacou_corpo_a_corpo = 1;
                        if (jogo->matriz[i][j - 1].hp <= 0)
                            adicionar_entidade(jogo, i, j - 1, '*');
                    }
                }




                //Os viros se movimentas pra coluna na frente na mesma linha
                if (jogo->matriz[i][j - 1].ocupante == '*' && !atacou_corpo_a_corpo)
                {
                    jogo->matriz[i][j - 1].ocupante = entidade;
                    jogo->matriz[i][j - 1].hp = jogo->matriz[i][j].hp;
                    jogo->matriz[i][j - 1].dano = jogo->matriz[i][j].dano;
                    adicionar_entidade(jogo, i, j, '*');
                }
            }
        }
    }
}
void verificar_condicoes(EstadoJogo *jogo)
{
    //Derrota
    if (jogo->integridade_nucleo <= 0)
    {
        jogo->estado = ESTADO_DERROTA;
        return;
    }


    //Verifica se tem algum virus no mapa
    int virus_ativos = 0;
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            char c = jogo->matriz[i][j].ocupante;
            if (c == 'V' || c == 'T' || c == 'R')
                virus_ativos++;
        }
    }
   
    int total_fila = jogo->virus_v_restantes + jogo->virus_t_restantes + jogo->virus_r_restantes;
   
    if (total_fila == 0 && virus_ativos == 0)
    {
       
        if (jogo->turno_atual < 3)
        {
            jogo->turno_atual++;
            jogo->bits = 50;            
            jogo->segundos_passados = 0;
            
           
            for (int i = 0; i < LINHAS; i++)
            {
                for (int j = 0; j < COLUNAS; j++)
                {
                    //Reseta o mapa
                    if (jogo->matriz[i][j].ocupante != 'X')
                    {
                        adicionar_entidade(jogo, i, j, '*');
                    }
                }
            }


            if (jogo->turno_atual == 2)
            {
                jogo->virus_v_restantes = 5;
                jogo->virus_t_restantes = 3;
                jogo->virus_r_restantes = 2;
            }
            else if (jogo->turno_atual == 3)
            {
                jogo->virus_v_restantes = 8;
                jogo->virus_t_restantes = 4;
                jogo->virus_r_restantes = 3;
            }


            jogo->estado = ESTADO_MENU;
            jogo->estado_anterior = ESTADO_MENU;
        }
        else
        {
            jogo->estado = ESTADO_VITORIA;
        }
    }
}
//Para o novo arquivo .txt
void atualizar_estatisticas(int venceu, int tempo_segundos) {
    int vitorias = 0, derrotas = 0, melhor_tempo = 0;


    //abre e le o que esta no arquivo
    FILE *arquivo = fopen("estatisticas.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d %d %d", &vitorias, &derrotas, &melhor_tempo);
        fclose(arquivo);
    }


    //Atualiza os dados
    if (venceu) {
        vitorias++;
        if (melhor_tempo == 0 || tempo_segundos < melhor_tempo) {
            melhor_tempo = tempo_segundos;
        }
    } else {
        derrotas++;
    }


    //Escreve os novos dados
    arquivo = fopen("estatisticas.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d %d %d\n", vitorias, derrotas, melhor_tempo);
        fclose(arquivo);
    }
}


//Exibe as infos na tela
void exibir_estatisticas() {
    int vitorias = 0, derrotas = 0, melhor_tempo = 0;


    FILE *arquivo = fopen("estatisticas.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d %d %d", &vitorias, &derrotas, &melhor_tempo);
        fclose(arquivo);
    }


    int total = vitorias + derrotas;
    float taxa = 0.0f;
    if (total > 0) {
        taxa = ((float)vitorias / total) * 100.0f;
    }


    system("cls || clear");
    printf(COR_AVISO "================================================================================\n" COR_RESET);
    printf("               V I R U S . E X E  //  E S T A T I S T I C A S                   \n");
    printf(COR_AVISO "================================================================================\n\n" COR_RESET);


    printf(" Partidas Jogadas : %d\n", total);
    printf(" Vitorias         : %d\n", vitorias);
    printf(" Derrotas         : %d\n", derrotas);
    printf(" Taxa de Vitoria  : %.1f%%\n", taxa);


    if (melhor_tempo > 0) {
        printf(" Recorde de Tempo : %d segundos\n", melhor_tempo);
    } else {
        printf(" Recorde de Tempo : (Nenhuma vitoria ainda)\n");
    }


    printf("\n" COR_LEGENDA "Pressione ESC para voltar ao menu" COR_RESET);
   
    while (_getch() != 27) {


    }
   
   
}
