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
    int onda_atual;
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

