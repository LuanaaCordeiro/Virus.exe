# 🕹️ VIRUS.EXE


<div align="center">
  <img src="Virus.png" width="200">
</div>

## 📖 A História
Um servidor sofreu uma invasão coordenada por agentes maliciosos. Após o rompimento do firewall primário, uma horda de malwares avança em direção ao 
Núcleo do Sistema, ameaçando comprometê-lo. Para impedir o colapso, o jogador deverá instalar estrategicamente robôs de defesa na memória RAM, criando linhas 
de proteção capazes de eliminar as ameaças antes que alcancem o núcleo.


## 🧱 Estruturas de Dados (Structs)
Neste projeto, utilizamos as seguintes `structs` para organizar o jogo:

*   **`[Celula]`**: [É a struct para cada espaço no tabuleiro, ou seja, o que cada ocupante do tabuleiro possuiu]
*   **`[EstadoJogo]`**: [É a struct que controla todas as principais informações do jogo]

```c
typedef struct {
    char ocupante; 
    int hp;        
    int dano;      
} Celula;

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
```
## 🎮 Controles Básicos
* Menu Principal: 1 Iniciar Jogo | 2 Continuar Jogo Salvo | 3 Estatísticas | 4 Sair do Sistema
* Tela de Estatísticas: ESC para voltar ao menu
* Durante a Preparação: 1 Instalar Robô (Loja) | 2 Iniciar Turno | 3 Reiniciar | 0 Salvar e Sair
* Loja: 1 Atacante (30b) | 2 Barreira (20b) | 3 Gerador (25b) | 0 Voltar
* Posicionamento: Setas direcionais para mover o cursor | Espaço para instalar | 0 para cancelar
* Durante o Turno: 1 Pausar e abrir a loja
* Tela de Vitória/Derrota: 1 Reiniciar | 0 Salvar e Sair

## 📼 Arquivos de Dados
* savegame.bin: Armazena o estado completo da partida atual para continuar posteriormente.
* estatisticas.txt: Registra o histórico de vitórias, derrotas e o melhor tempo de conclusão.

## 🎮 Funções (Structs)
*   **`[inicializar_tabuleiro]`**: [Inicializa as informações do tabuleiro que estão na struct EstadoJogo]
*   **`[adicionar_entidade]`**: [Adiciona as entidades com seus respectivos atributos]
*   **`[carregar_jogo]`**: [Carrega a partida que foi salva]
*   **`[salvar_jogo]`**: [Salva a partida que esta acontecendo]
*   **`[renderizar_interface]`**: [Cria a principal interface do jogo]
*   **`[processar_robos]`**: [Processa as ações dos robos]
*   **`[spawnar_virus]`**: [Gera os virus no tabuleiro]
*   **`[mover_virus]`**: [Faz os vírus se movimentarem no mapa]
*   **`[verificar_condicoes]`**: [Verifica se o jogador ganhou, perdeu ou mudou de turno]
*   **`[atualizar_estatisticas]`**: [Adiciona e modifica as estatisticas de partidas do usuário]
*   **`[exibir_estatisticas]`**: [Mostra as estatisticas para o usuário]

## 👪 Equipe
* Emilly Maciel de Lima
* Guido Vidal de Oliveira
* Luana da Costa Cordeiro
* Maria Fernanda Sombra Costa

