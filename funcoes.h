/*Declara‡äes e prototipos*/

# include "console_v1.5.5.h"

# define VIDA 10
# define VIDA_INIMIGO 20

typedef struct nave
{
    int vida;
    COORD posicao_nave;
    COORD posicao_disparo;
    EVENTO ship_navegacao;

}NAVE;

typedef struct janela
{
    COORD maximiza_janela;
}MAX_JANELA;

typedef struct inimigo
{
    int vida;
    COORD posicao_nave_inimiga;
    COORD posicao_disparo_inimigo;
    int colisor_inferior;
}NAVE_INIMIGA;

/*Apaga nave desenhada*/
void Apaga_nave(NAVE *);

/*Desenha nave*/
void Desenha_nave(NAVE *);

/*Desenha nave inimiga*/
void Desenha_inimigo(NAVE_INIMIGA *);

/*Apaga projetil lancado*/
void Apaga_projetil(NAVE *, NAVE_INIMIGA *);

/*Dispara projetil da nave*/
void Dispara_projetil(NAVE *, NAVE_INIMIGA *);

/*Comeco do meu jogo*/
void game(NAVE *, NAVE_INIMIGA *);

/*Inicializa os valores para minha nave*/
void Inicia_naves(NAVE *, NAVE_INIMIGA *, MAX_JANELA *);

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *);