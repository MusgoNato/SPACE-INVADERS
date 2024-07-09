/*gcc main.c -o main.exe -Wall -pedantic -Wextra -Werror funcoes.c conio_v3.2.4.c console_v1.5.5.c */
# include <stdio.h>
# include "conio_v3.2.4.h"
# include "console_v1.5.5.h"
# include "funcoes.h"

int main(int argc, char *argv[])
{
    NAVE nave;
    NAVE_INIMIGA nave_inimiga;
    MAX_JANELA janela;
    argc = argc;
    argv = argv;

    setCursorStatus(DESLIGAR);
    clrscr();

    /*Maximiza janela*/
    janela.maximiza_janela = MaxDimensaoJanela();
    setDimensaoJanela(janela.maximiza_janela.X, janela.maximiza_janela.Y);

    /*Inicializacao dos valores da nave*/
    Inicia_naves(&nave, &nave_inimiga, &janela);

    /*Faz a chamada do jogo*/
    game(&nave, &nave_inimiga);

    setCursorStatus(LIGAR);
    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    return 0;
}