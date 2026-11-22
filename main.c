#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main()
{

    EstadoJogo *jogo = (EstadoJogo *)malloc(sizeof(EstadoJogo));
    if (jogo == NULL)
    {
        printf("ERRO CRITICO: Falha ao alocar memoria para o sistema do jogo!\n");
        return 1;
    }

    // Tela inicial para carregar novo jogo ou jogo salvo
    system("cls || clear"); // Isso aqui é pra limpar o terminal

    printf(COR_VERDE "================================================================================\n" COR_RESET);
    printf(COR_VERDE "                              V I R U S . E X E            \n");
    printf(COR_VERDE "================================================================================\n" COR_RESET);
    printf("\n");
    printf(COR_LEGENDA " [1] Iniciar Novo Jogo\n" COR_RESET);
    printf(COR_LEGENDA " [2] Restaurar Jogo Anterior\n" COR_RESET);
    printf("\n> Aguardando input... ");

    // Aqui ele torna o menu funcional, 1 é novo jogo e 2 é carregar jogo ou iniciar caso nn tenha jogo salvo
    int inicializou = 0;
    while (!inicializou)
    {

        // Esse _kbhit verifica se alguma tecla foi apertada
        if (_kbhit())
        {
            int tecla_boot = _getch(); // O _getch verifica qual a tecla que foi apertada
            if (tecla_boot == '1')
            {
                inicializar_tabuleiro(jogo);
                inicializou = 1;
            }
            else if (tecla_boot == '2')
            {
                if (carregar_jogo(jogo, "savegame.bin"))
                {
                    if (jogo->estado != ESTADO_DERROTA && jogo->estado != ESTADO_VITORIA)
                    {
                        jogo->estado = ESTADO_MENU;
                        jogo->estado_anterior = ESTADO_MENU;
                    }
                }
                else
                {
                    inicializar_tabuleiro(jogo);
                }

                inicializou = 1;
            }
        }
    }

    system("cls || clear");

    int rodando = 1;
    clock_t ultimo_movimento = clock();
    int delay_movimento_ms = 1000;

    renderizar_interface(jogo);

    while (rodando)
    {

        //Ele usa o clock do pc pra calcular o tempo
        if (jogo->estado == ESTADO_TURNO)
        {
            clock_t agora = clock();
            int tempo_passado_ms = (agora - ultimo_movimento) * 1000 / CLOCKS_PER_SEC;

            if (tempo_passado_ms >= delay_movimento_ms)
            {
                jogo->segundos_passados++;

                processar_robos(jogo);
                mover_virus(jogo);
                spawnar_virus(jogo);

                verificar_condicoes(jogo);

                ultimo_movimento = agora;
                renderizar_interface(jogo);
            }
        }

        //Aqui ele faz a mudança de telas, movimentação do cursor e saves
        if (_kbhit())
        {
            int tecla = _getch();

            if (tecla == 224 || tecla == 0)
            {
                tecla = _getch();

                if (jogo->estado == ESTADO_POSICIONANDO)
                {
                    if (tecla == 72)
                    {
                        if (jogo->cursor_l > 0)
                        {
                            jogo->cursor_l--;
                        }
                    }
                    else if (tecla == 80)
                    {
                        if (jogo->cursor_l < LINHAS - 1)
                        {
                            jogo->cursor_l++;
                        }
                    }
                    else if (tecla == 75)
                    {
                        if (jogo->cursor_c > 0)
                        {
                            jogo->cursor_c--;
                        }
                    }
                    else if (tecla == 77)
                    {
                        if (jogo->cursor_c < 1)
                        {
                            jogo->cursor_c++;
                        }
                    }
                }
            }
            else
            {
                if (jogo->estado == ESTADO_MENU)
                {
                    if (tecla == '1')
                    {
                        jogo->estado_anterior = ESTADO_MENU;
                        jogo->estado = ESTADO_LOJA;
                    }
                    else if (tecla == '2')
                    {
                        jogo->estado = ESTADO_TURNO;
                        ultimo_movimento = clock();
                    }
                    else if (tecla == '0')
                    {
                        salvar_jogo(jogo, "savegame.bin");
                        rodando = 0;
                    }
                }
                else if (jogo->estado == ESTADO_LOJA)
                {
                    if (tecla == '1' && jogo->bits >= 30)
                    {
                        jogo->robo_selecionado = 'A';
                        jogo->custo_selecionado = 30;
                        jogo->estado = ESTADO_POSICIONANDO;
                    }
                    else if (tecla == '2' && jogo->bits >= 20)
                    {
                        jogo->robo_selecionado = 'B';
                        jogo->custo_selecionado = 20;
                        jogo->estado = ESTADO_POSICIONANDO;
                    }
                    else if (tecla == '3' && jogo->bits >= 25)
                    {
                        jogo->robo_selecionado = 'G';
                        jogo->custo_selecionado = 25;
                        jogo->estado = ESTADO_POSICIONANDO;
                    }
                    else if (tecla == '0')
                    {
                        jogo->estado = jogo->estado_anterior;
                    }
                }
                else if (jogo->estado == ESTADO_POSICIONANDO)
                {
                    if (tecla == '0')
                    {
                        jogo->estado = jogo->estado_anterior;
                    }
                    else if (tecla == ' ')
                    {
                        if (jogo->matriz[jogo->cursor_l][0].ocupante == 'X')
                        {
                        }
                        else if (jogo->matriz[jogo->cursor_l][jogo->cursor_c].ocupante == '*')
                        {
                            adicionar_entidade(jogo, jogo->cursor_l, jogo->cursor_c, jogo->robo_selecionado);
                            jogo->bits -= jogo->custo_selecionado;
                            jogo->estado = jogo->estado_anterior;
                        }
                    }
                }
                else if (jogo->estado == ESTADO_TURNO)
                {
                    if (tecla == '1')
                    {
                        jogo->estado_anterior = ESTADO_TURNO;
                        jogo->estado = ESTADO_LOJA;
                    }
                }
                else if (jogo->estado == ESTADO_DERROTA || jogo->estado == ESTADO_VITORIA)
                {
                    if (tecla == '0')
                    {
                        salvar_jogo(jogo, "savegame.bin");
                        rodando = 0;
                    }
                }
            }
            renderizar_interface(jogo);
        }
    }

    free(jogo);

    return 0;
}
