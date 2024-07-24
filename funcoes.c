/*Logica dos prototipos de funcoes*/
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "console_v1.5.5.h"
# include "conio_v3.2.4.h"
# include "funcoes.h"


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
            printf(" ");
        }
        
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

/*Responsavel pelo disparo do inimigo*/
void Disparo_inimigo(NAVE_INIMIGA *nave_inimiga, NAVE *nave)
{
    int apaga = 0;
    
    /*O disparo somente é feito novamente caso atinja a posicao da nave*/
    if(nave_inimiga->posicao_disparo_inimigo.Y >= nave->posicao_nave.Y)
    {
        nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
        nave_inimiga->posicao_disparo_inimigo.X = nave_inimiga->posicao_nave_inimiga.X;
    }
    else
    {
        gotoxy(nave_inimiga->posicao_disparo_inimigo.X, ++nave_inimiga->posicao_disparo_inimigo.Y);
        textcolor(RED);
        printf("1"); 

        apaga = nave_inimiga->posicao_disparo_inimigo.Y - 1;
        gotoxy(nave_inimiga->posicao_disparo_inimigo.X, apaga);
        textcolor(BLACK);
        printf(" ");

    }

    Sleep(VELOCIDADE_GAME);

}

/*Responsavel pelo disparo da minha nave*/
void Dispara_projetil(NAVE *nave, NAVE_INIMIGA *nave_inimiga)
{
    int apaga = 0;
    if(nave->posicao_disparo.Y > 1 && nave->posicao_disparo.Y > nave_inimiga->colisor_inferior)
    {
        
        gotoxy(nave->posicao_disparo.X, --nave->posicao_disparo.Y);
        textcolor(YELLOW);
        printf("0");

        
        apaga = nave->posicao_disparo.Y;
        gotoxy(nave->posicao_disparo.X, ++apaga);
        textcolor(BLACK);
        printf(" ");
    }
    else
    {
        /*Reinicializa o disparo ao tocar no limite*/
        nave->posicao_disparo.X = nave->posicao_nave.X;
        nave->posicao_disparo.Y = nave->posicao_nave.Y;
    }

    Sleep(VELOCIDADE_GAME);
    
}

/*Comeca o jogo*/
void game(NAVE *nave, NAVE_INIMIGA *nave_inimiga, MAX_JANELA *Janela)
{
    int cont = 0;
    int x = 0;

    /*Gero meu inimigo em uma posicao aleatoria da tela*/
    x = Gera_inimigo(nave_inimiga, Janela);

    /*A coordenada recebida pela geracao aleatoria do inimigo, tera de ser recebida pelo disparo,
    pois a 1a vez necessita que inicialize o disparo no mesmo lugar que a geracao aleatoria do proprio*/
    nave_inimiga->posicao_disparo_inimigo.X = x;
  
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

        /*Dispara projetil do jogador e o apaga*/
        Dispara_projetil(nave, nave_inimiga);

        /*Dispara o projetil inimigo e o apaga*/
        Disparo_inimigo(nave_inimiga, nave);
        
        cont++;
        
    }while(nave->saida);
    
}

/*Gera uma coordenada aleatoria na tela, aonde o inimigo surgir�*/
int Gera_inimigo(NAVE_INIMIGA *nave_inimiga, MAX_JANELA *Janela)
{
    int i;

    /*Gera coordenada dentro do limite da Janela*/
    nave_inimiga->posicao_nave_inimiga.X = (1 + rand() % Janela->maximiza_janela.X);

    if(nave_inimiga->posicao_nave_inimiga.X >= 1 && nave_inimiga->posicao_nave_inimiga.X < Janela->maximiza_janela.X)
    {
        /*Desenha inimigo*/
        for(i = 0; i < nave_inimiga->colisor_inferior; i++)
        {
            gotoxy(nave_inimiga->posicao_nave_inimiga.X, nave_inimiga->posicao_nave_inimiga.Y + i);
            textcolor(RED);
            textbackground(BLACK);
            printf("XXX");
        }
    }
    else
    {
        /*Toda vez que a coordenada for acima do intervalo especificado, ele reseta pra posicao 1*/
        return 1;
    }

    /*Retorno da coordenada gerada*/
    return nave_inimiga->posicao_nave_inimiga.X;
    
}

/*Inicializa naves*/
void Inicia_naves(NAVE *nave, NAVE_INIMIGA *nave_inimiga, MAX_JANELA *janela)
{
    int i;
    nave->saida = 1;

    /*Inicializa nave jogador*/
    nave->vida = VIDA;
    nave->posicao_nave.X = janela->maximiza_janela.X/2;
    nave->posicao_nave.Y = janela->maximiza_janela.Y - 2;
    nave->posicao_disparo.X = nave->posicao_nave.X;
    nave->posicao_disparo.Y = nave->posicao_nave.Y;

    /*Alocacao de quantas balas estarao disponiveis simultaneamente*/
    nave->posicao_projetil = (COORD **)malloc(janela->maximiza_janela.X * janela->maximiza_janela.Y * sizeof(COORD *));

    /*Verificacao*/
    if(nave->posicao_projetil != NULL)
    {
        for(i = 0; i < janela->maximiza_janela.X; i++)
        {
            nave->posicao_projetil[i] = (COORD *)malloc(janela->maximiza_janela.X * sizeof(COORD));
            if(nave->posicao_projetil[i] == NULL)
            {
                printf("Alocao errada!");
                exit(0);
            }
        }
    }
    else
    {
        printf("\tAlocacao deu errado!");
        exit(0);
    }
    


    /*Inicializa nave inimiga*/
    nave_inimiga->vida = VIDA_INIMIGO;
    nave_inimiga->posicao_nave_inimiga.X = janela->maximiza_janela.X - 1;
    nave_inimiga->posicao_nave_inimiga.Y = 1;
    nave_inimiga->posicao_disparo_inimigo.X = nave_inimiga->posicao_nave_inimiga.X;
    nave_inimiga->posicao_disparo_inimigo.Y = nave_inimiga->posicao_nave_inimiga.Y;
    nave_inimiga->colisor_inferior = TAM_ENEMY_01;

    

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
                        if(nave->posicao_nave.X < 1)
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
                        if(nave->posicao_nave.X < 1)
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

                    /*case ESPACO:
                    {
                        Ao pressionar espa�o reinicializo a posicao do disparo na coordenada da nave, seu ponto de origem
                        nave->posicao_disparo.X = nave->posicao_nave.X;

                        Chama a funcao para diparar meu projetil da nave
                        Dispara_projetil(nave); 
                        break;
                    }*/
                }
            }
        }       
    }
}
    