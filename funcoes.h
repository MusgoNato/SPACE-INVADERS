/*Declarações e prototipos*/

# include "console_v1.5.5.h"

# define VIDA 10
# define VELOCIDADE_DISPARO 10

typedef struct nave
{
    int vida;
    int velocidade_disparo;
    COORD posicao_nave;
    EVENTO ship_navegacao;

}NAVE;

typedef struct janela
{
    COORD maximiza_janela;
}MAX_JANELA;

void Apaga_nave(NAVE *);

/*Desenha nave*/
void Desenha_nave(NAVE *);

/*Comeco do meu jogo*/
void game(NAVE *);

/*Inicializa os valores para minha nave*/
void Inicia_nave(NAVE *, MAX_JANELA *);

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *);