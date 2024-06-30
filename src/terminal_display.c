#include <stdio.h>
#include "../headers/terminal_display.h"
#include "../headers/image.h"

void clear() {
  printf("\033[2J");
} // Solução não portável(erro de linhas em console linux)

void gotoxy(int x, int y) { printf("\033[%d;%df", y, x); }

void printRGB(int r, int g, int b) {
  printf("\033[48;2;%d;%d;%dm \033[0;00m", r, g, b);
}

/*(SUBFUNÇÃO)Imprime um Pixel quadrado na tela,com posição e no padrão RGB*/
void printPixel(int x, int y, RGB *pixel) {
  gotoxy(x + 1, y + 1);
  printRGB(pixel->red, pixel->green, pixel->blue);
  gotoxy(x + 2, y + 1);
  printRGB(pixel->red, pixel->green, pixel->blue);
}

/*Imprime no console uma imagem recebida, com pixels quadrados*/
void imagePainter(IMAGE *image) {
  clear();
  //system("clear"); // Solução não portável
  for (int i = 0; i < image->height; i++) {
    for (int j = 0; j < image->width; j++) {
      printPixel(j * 2, i, &image->data_matriz[i][j]);
    }
  }
  printf("\n");
}