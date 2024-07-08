/*Logica dos prototipos de funcoes*/
# include <stdio.h>
# include <stdlib.h>
# include "console_v1.5.5.h"
# include "conio_v3.2.4.h"
# include "funcoes.h"

/*Inicializa os valores para minha nave*/
void Inicia_nave(NAVE *nave, MAX_JANELA *janela)
{
    nave->vida = VIDA;
    nave->velocidade_disparo = VELOCIDADE_DISPARO;
    nave->posicao_nave.X = janela->maximiza_janela.X/2;
    nave->posicao_nave.Y = janela->maximiza_janela.Y - 2;
}

/*Comeca o jogo*/
void game(NAVE *nave)
{

    /*Chamada da funcao para desenho da minha nave*/
    Desenha_nave(nave);

    do
    {
        /*Navegacao da nave*/
        Navega_nave(nave);

    }while(1);
    
    
}

/*Desenha minha nave na tela*/
void Desenha_nave(NAVE *nave)
{
    int i;

    /*Desenha nave*/
    for(i = 0; i < 3; i++)
    {
        gotoxy(nave->posicao_nave.X, nave->posicao_nave.Y + i);
        printf("***");
    }
    
}

void Apaga_nave(NAVE *nave)
{
    int i;

    /*Apaga nave*/
    for(i = 0; i < 3; i++)
    {
        gotoxy(nave->posicao_nave.X, nave->posicao_nave.Y + i);
        printf("   ");
    }
}

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *nave)
{
    if(hit(KEYBOARD_HIT))
    {
        nave->ship_navegacao = Evento();
        if(nave->ship_navegacao.tipo_evento & KEY_EVENT)
        {
            if(nave->ship_navegacao.teclado.status_tecla == LIBERADA)
            {
                switch(nave->ship_navegacao.teclado.key_code)
                {
                    case ESC:
                    {
                        exit(0);
                        break;
                    }

                    case SETA_PARA_DIREITA:
                    {
                        /*Apaga minha nave na posicao atual*/
                        Apaga_nave(nave);

                        /*Desenha minha um posicao a frente da anterior*/
                        nave->posicao_nave.X++;
                        Desenha_nave(nave);
                        break;
                    }

                    case SETA_PARA_ESQUERDA:
                    {
                        /*Apaga minha nave na posicao atual*/
                        Apaga_nave(nave);

                        /*Desenha minha um posicao a frente da anterior*/
                        nave->posicao_nave.X--;
                        Desenha_nave(nave);

                        break;
                    }
                }
            }
        }       
    }
}
    