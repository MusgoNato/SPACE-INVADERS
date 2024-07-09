/*Logica dos prototipos de funcoes*/
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "console_v1.5.5.h"
# include "conio_v3.2.4.h"
# include "funcoes.h"

/*Inicializa naves*/
void Inicia_naves(NAVE *nave, NAVE_INIMIGA *nave_inimiga, MAX_JANELA *janela)
{
    /*Inicializa nave jogador*/
    nave->vida = VIDA;
    nave->posicao_nave.X = janela->maximiza_janela.X/2;
    nave->posicao_nave.Y = janela->maximiza_janela.Y - 2;
    nave->posicao_disparo.X = nave->posicao_nave.X;
    nave->posicao_disparo.Y = nave->posicao_nave.Y;


    /*Inicializa nave inimiga*/
    nave_inimiga->vida = VIDA_INIMIGO;
    nave_inimiga->posicao_nave_inimiga.X = janela->maximiza_janela.X/2;
    nave_inimiga->posicao_nave_inimiga.Y = 1;
    nave_inimiga->posicao_disparo_inimigo.X = nave_inimiga->posicao_nave_inimiga.X;
    nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
    nave_inimiga->colisor_inferior = 4;

}

/*Comeca o jogo*/
void game(NAVE *nave, NAVE_INIMIGA *nave_inimiga)
{
    do
    {
        /*Navegacao da nave*/
        Navega_nave(nave);

        /*Chama a funcao para diparar meu projetil da nave*/
        Dispara_projetil(nave, nave_inimiga);

        /*Apaga projeti disparado*/
        Apaga_projetil(nave, nave_inimiga);
        
    }while(1);
    
}

/*Responsavel por desenhar minha nave inimiga*/
void Desenha_inimigo(NAVE_INIMIGA *nave_inimiga)
{   
    int i, j;

    /*Colisor inferior eh quando for colidir o disparo com a parte inferior do inimigo, quando acontecer isso decrementa essa variavel e 
    chama novamente a funcao Desenha_Inimigo(), assim ele redesenha porem com uma linha a menos, como se fosse cortando o inimigo*/
    for(i = 0; i < nave_inimiga->colisor_inferior; i++)
    {
        for(j = 0; j < nave_inimiga->colisor_inferior; j++)
        {
            textcolor(RED);
            gotoxy(nave_inimiga->posicao_nave_inimiga.X + j, nave_inimiga->posicao_nave_inimiga.Y + i);
            printf("*");
        }
        
    }
}

/*Desenha minha nave na tela*/
void Desenha_nave(NAVE *nave)
{
    int i;

    /*Desenha nave*/
    for(i = 0; i < 3; i++)
    {
        textcolor(YELLOW);
        gotoxy(nave->posicao_nave.X, nave->posicao_nave.Y + i);
        printf("***");
    }
    
}

/*Responsavel por apagar nave desenhada*/
void Apaga_nave(NAVE *nave)
{
    int i;

    /*Apaga nave*/
    for(i = 0; i < 3; i++)
    {
        textcolor(BLACK);
        gotoxy(nave->posicao_nave.X, nave->posicao_nave.Y + i);
        printf("   ");
    }
}

/*Responsavel pelo disparo da minha nave*/
void Dispara_projetil(NAVE *nave, NAVE_INIMIGA *nave_inimiga)
{
    if(nave->posicao_disparo.Y > 1 && nave->posicao_disparo.Y > nave_inimiga->colisor_inferior)
    {
        textbackground(BLUE);
        textcolor(WHITE);
        gotoxy(nave->posicao_disparo.X, --nave->posicao_disparo.Y);
        putchar(167);
    }
    else
    {
        /*Reinicializa o disparo ao tocar no limite*/
        nave->posicao_disparo.X = nave->posicao_nave.X;
        nave->posicao_disparo.Y = nave->posicao_nave.Y;
    }

    Sleep(10);
    
}

/*Apaga projetil*/
void Apaga_projetil(NAVE *nave, NAVE_INIMIGA *nave_inimiga)
{
    if(nave->posicao_disparo.Y > 1 && nave->posicao_disparo.Y > nave_inimiga->colisor_inferior)
    {
        textbackground(BLACK);
        textcolor(BLACK);
        gotoxy(nave->posicao_disparo.X, nave->posicao_disparo.Y);
        putchar(167);
    }
    else
    {
        /*Reinicializa o disparo ao tocar no limite*/
        nave->posicao_disparo.X = nave->posicao_nave.X;
        nave->posicao_disparo.Y = nave->posicao_nave.Y;
    }
    Sleep(10);
    
}

/*Controla a navegacao da minha nave*/
void Navega_nave(NAVE *nave)
{
    /*Pega acao do teclado*/
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
                        textbackground(BLACK);
                        textcolor(LIGHTGRAY);
                        setCursorStatus(LIGAR);
                        exit(0);
                        break;
                    }

                    case SETA_PARA_DIREITA:
                    {
                        if(nave->posicao_nave.X < nave->posicao_disparo.Y)
                        {
                            /*Apaga posicao de disparo*/
                            nave->posicao_disparo.X++;
                        }

                        /*Apaga minha nave na posicao atual*/
                        Apaga_nave(nave);

                        /*Desenha minha um posicao a frente da anterior*/
                        nave->posicao_nave.X++;
                        Desenha_nave(nave);
                        break;
                    }

                    case SETA_PARA_ESQUERDA:
                    {
                        /*Verificacao, somente quando a posicao da nave for inferior ao disparo ele entra atualizando a origem do disparo*/
                        if(nave->posicao_nave.X < nave->posicao_disparo.Y)
                        {
                            /*Atualiza posicao de disparo*/
                            nave->posicao_disparo.X--;
                        }

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
    