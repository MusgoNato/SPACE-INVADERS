/*Declara‡äes e prototipos*/

# include "console_v1.5.5.h"


/*Constantes*/
# define VIDA 10
# define VIDA_INIMIGO 20
# define TAM_ENEMY_01 3
# define GERADOR_INIMIGO 150
# define VELOCIDADE_PROJETIL_INIMIGO 10
# define VELOCIDADE_GAME 25
# define DISPARA_PROJETEIS_INIMIGOS 5


/*Registros*/
typedef struct _nave
{
    int vida;
    COORD posicao_nave;
    COORD posicao_disparo;
    EVENTO ship_navegacao;
    int saida;
    COORD **posicao_projetil;

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

/*Gera uma coordenada aleatoria na tela, aonde o inimigo surgir */
int Gera_inimigo(NAVE_INIMIGA *, MAX_JANELA *);

/*Inicializa os valores para minha nave*/
void Inicia_naves(NAVE *, NAVE_INIMIGA *, MAX_JANELA *);

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *);