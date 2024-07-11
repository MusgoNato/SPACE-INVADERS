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
    nave_inimiga->posicao_nave_inimiga.X = janela->maximiza_janela.X - 1;
    nave_inimiga->posicao_nave_inimiga.Y = 1;
    nave_inimiga->posicao_disparo_inimigo.X = nave_inimiga->posicao_nave_inimiga.X;
    nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
    nave_inimiga->colisor_inferior = TAM_ENEMY_01;

}

/*Comeca o jogo*/
void game(NAVE *nave, NAVE_INIMIGA *nave_inimiga, MAX_JANELA *Janela)
{
    int cont = 0;
    int x = 0;
    nave->saida = 1;

    /*Gero meu inimigo em uma posicao aleatoria da tela*/
    x = Gera_inimigo(nave_inimiga, Janela);
    
    do
    {
        /*Navegacao da nave*/
        Navega_nave(nave);

        /*Apago a geracao anterior de acordo com o time pre-definido (GERADOR_INIMIGO)*/
        if(cont == GERADOR_INIMIGO)
        {
            Apaga_inimigo(nave_inimiga, x);
            x = Gera_inimigo(nave_inimiga, Janela);
            cont = 0;
        }

        /*Dispara o projetil inimigo e o apaga*/
        Disparo_inimigo(nave_inimiga, nave);

        Apaga_projetil_inimigo(nave, nave_inimiga);
        
        cont++;
        
    }while(nave->saida);
    
}

/*Responsavel pelo disparo do inimigo*/
void Disparo_inimigo(NAVE_INIMIGA *nave_inimiga, NAVE *nave)
{
    if(nave_inimiga->posicao_disparo_inimigo.Y < nave->posicao_nave.Y)
    {
        textcolor(RED);
        textbackground(BLACK);
        gotoxy(nave_inimiga->posicao_nave_inimiga.X, ++nave_inimiga->posicao_disparo_inimigo.Y);
        printf("A"); 
    }
    else
    {
        nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
    }

    Sleep(2);
    
}

/*Apaga projetil inimigo*/
void Apaga_projetil_inimigo(NAVE *nave, NAVE_INIMIGA *nave_inimiga)
{
    if(nave_inimiga->posicao_disparo_inimigo.Y < nave->posicao_nave.Y)
    {
        textcolor(RED);
        textbackground(BLACK);
        gotoxy(nave_inimiga->posicao_nave_inimiga.X, nave_inimiga->posicao_disparo_inimigo.Y);
        printf(" "); 
    }
    else
    {
        /*Reposiciona a coordenada do meu disparo*/
        nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
    }
    
}


/*Ao gerar aleatoriamente o inimigo pela primeira vez apago a geracao anterior*/
void Apaga_inimigo(NAVE_INIMIGA *nave_inimiga, int x)
{
    int i, j;
    for(i = 0; i < nave_inimiga->colisor_inferior; i++)
    {
        for(j = 0; j < nave_inimiga->colisor_inferior; j++)
        {
            textcolor(BLACK);
            textbackground(BLACK);
            gotoxy(x + j, nave_inimiga->posicao_nave_inimiga.Y + i);
            putchar(32);
        }
        
    }
}


/*Gera uma coordenada aleatoria na tela, aonde o inimigo surgirá*/
int Gera_inimigo(NAVE_INIMIGA *nave_inimiga, MAX_JANELA *Janela)
{
    int i, j;

    /*Gera coordenada dentro do limite da Janela*/
    while(1)
    {
        nave_inimiga->posicao_nave_inimiga.X = (1 + rand() % Janela->maximiza_janela.X);

        if(nave_inimiga->posicao_nave_inimiga.X >= 1 && nave_inimiga->posicao_nave_inimiga.X < Janela->maximiza_janela.X)
        {
            break;
        }
    }
    
   
    /*Desenha inimigo*/
    for(i = 0; i < nave_inimiga->colisor_inferior; i++)
    {
        for(j = 0; j < nave_inimiga->colisor_inferior; j++)
        {
            textcolor(RED);
            gotoxy(nave_inimiga->posicao_nave_inimiga.X + j, nave_inimiga->posicao_nave_inimiga.Y + i);
            putchar(4);
        }
        
    }

    /*Retorno da coordenada gerada*/
    return nave_inimiga->posicao_nave_inimiga.X;
    
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

/*Responsavel pelo disparo da minha nave, desenha e apaga projetil*/
void Dispara_projetil(NAVE *nave)
{
    while(nave->posicao_disparo.Y > 1)
    {
        gotoxy(nave->posicao_disparo.X, --nave->posicao_disparo.Y);
        textbackground(WHITE);
        textcolor(BLUE);
        putchar(179);

        /*Ao tocar no topo, volta apagando a bala ate sua origem*/
        if(nave->posicao_disparo.Y == 1)
        {
            while(nave->posicao_disparo.Y < nave->posicao_nave.Y - 1)
            {
                gotoxy(nave->posicao_disparo.X, ++nave->posicao_disparo.Y);
                textbackground(BLACK);
                textcolor(BLACK);
                putchar(179);
            }
            break;
        }
            
    }
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
            if(nave->ship_navegacao.teclado.status_tecla == PRESSIONADA)
            {
                switch(nave->ship_navegacao.teclado.key_code)
                {   
                    case ESC:
                    {
                        nave->saida = 0;
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

                    case ESPACO:
                    {
                        /*Ao pressionar espaço reinicializo a posicao do disparo na coordenada da nave, seu ponto de origem*/
                        nave->posicao_disparo.X = nave->posicao_nave.X;

                        /*Chama a funcao para diparar meu projetil da nave*/
                        Dispara_projetil(nave); 
                        break;
                    }
                }
            }
        }       
    }
}
    