/*Declara��es e prototipos*/

# include "console_v1.5.5.h"


/*Constantes*/
# define VIDA 10
# define VIDA_INIMIGO 20
# define TAM_ENEMY_01 3
# define GERADOR_INIMIGO 150
# define VELOCIDADE_PROJETIL_INIMIGO 10
# define VELOCIDADE_GAME 1
# define DISPARA_PROJETEIS_INIMIGOS 6
# define DISPARA_PROJETEIS_PLAYER 3
# define GERACAO_BONUS_SPEED 10
# define LIMITE_MOVIMENTO_CIMA_Y 25
# define LIMITE_MOVIMENTO_BAIXO_Y 57 /*Isso nao eh recomendado por questoes de portabilidade, o recomendado seria passar a estrutura Janela
                                        para a verificacao no case do movimento para baixo, onde tenho a maximizacao da minha janela no ponto Y,
                                        no caso teria o limitador correto para qualquer tela, pois pego o tamanho maximo dela.
                                        Nao fiz por pura preguica sorry ;(
                                        */

/*Registros*/
typedef struct _nave
{
    int vida;
    COORD posicao_nave;
    COORD posicao_disparo;
    EVENTO ship_navegacao;
    int saida;
    COORD **posicao_projetil;
    int controla_desenho;
    int control_shoot;

}NAVE;

typedef struct _janela
{
    COORD maximiza_janela;
}MAX_JANELA;

typedef struct _inimigo
{
    int vida;
    COORD posicao_nave_inimiga;
    COORD posicao_disparo_inimigo;
    int colisor_inferior;
}NAVE_INIMIGA;

/*Referente ao meu bonus, que ao usuario pega-lo lhe dara mais velocidade no disparo*/
typedef struct _bonus_speed
{
    COORD posicao_bonus_speed;
    COORD mapa;
    int velocidade;
}BONUS;

/*Apaga nave inimiga gerada*/
void Apaga_inimigo(NAVE_INIMIGA *, int);

/*Apaga nave desenhada*/
void Apaga_nave(NAVE *);

/*Desenha nave*/
void Desenha_nave(NAVE *);

/*Dispara projetil da nave*/
void Dispara_projetil(NAVE *, NAVE_INIMIGA *);

/*Dispara projetil inimigo*/
void Disparo_inimigo(NAVE_INIMIGA *, NAVE *);

/*Comeco do meu jogo*/
void game(NAVE *, NAVE_INIMIGA *, MAX_JANELA *);

void Gera_bonus_velocidade(BONUS *);

/*Gera uma coordenada aleatoria na tela, aonde o inimigo surgir�*/
int Gera_inimigo(NAVE_INIMIGA *, MAX_JANELA *);

/*Inicializa os valores para minha nave*/
void Inicia_naves(NAVE *, NAVE_INIMIGA *, MAX_JANELA *);

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *);