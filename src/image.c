#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/image.h"


//Calcula a quantidade de digitos de um inteiro*/
int numberofDigits(int number) { return ((int)floor(log10(number)) + 1); }

/*Constrói uma estrutura imagem usando
 os dados do buffer retirado do arquivo*/
IMAGE *imageStructureBuilder(unsigned char *file_buffer_array) {
  IMAGE *image = (IMAGE *)malloc(sizeof(IMAGE));

  image->height = atoi((const char *)&file_buffer_array[PPM_HEIGHT_BUFFER_POSITION]);
  image->width = atoi((const char *)&file_buffer_array[PPM_WIDTH_BUFFER_POSITION(image->height)]);

  // Aloca uma matriz para a imagem, usando o novo tipo RGB em cada posição da matriz
  image->data_matriz = malloc(image->height * sizeof(RGB *));
  for (int i = 0; i < image->height; i++)
    *(image->data_matriz + i) = malloc(image->width * sizeof(RGB));

  // Estrutura os dados dos pixels da imagem em uma matriz bidimensional
  int pixels_index = PPM_WIDTH_BUFFER_POSITION(image->height) + numberofDigits(image->width) + 5;
  unsigned int sum_red = 0, sum_green = 0, sum_blue = 0;
  int counter = 0;
  for (int i = 0; i < image->height; i++) {
    for (int j = 0; j < image->width; j++) {
      image->data_matriz[i][j].red =
          file_buffer_array[pixels_index + counter * 3];
      image->data_matriz[i][j].green =
          file_buffer_array[(pixels_index + 1) + counter * 3];
      image->data_matriz[i][j].blue =
          file_buffer_array[(pixels_index + 2) + counter * 3];
      counter++;
      // Calcula a média dos pixels da imagem
      sum_red += image->data_matriz[i][j].red;
      sum_green += image->data_matriz[i][j].green;
      sum_blue += image->data_matriz[i][j].blue;
    }
  }
  image->media.red = sum_red / (image->height * image->width);
  image->media.green = sum_green / (image->height * image->width);
  image->media.blue = sum_blue / (image->height * image->width);
  return image;
}

/*libera a memoria utilizada por uma extrutura imagem*/
void freeImage(IMAGE *image) {
  // libera as linhas da matriz de dados
  for (int i = 0; i < image->height; i++)
    free(*(image->data_matriz + i));
  // libera a matriz de dados
  free(image->data_matriz);
  // libera a Imagem
  free(image);
}

IMAGE *imageScaler(IMAGE *image, int new_width, int new_height){
  //Aloca uma nova estrutura imagem para receber a imagem redimensionada
  IMAGE *new_image = (IMAGE *)malloc(sizeof(IMAGE));
  new_image->width = new_width;
  new_image->height = new_height;

  // Aloca uma data_matriz para a nova imagem
  new_image->data_matriz = malloc(new_height * sizeof(RGB *));
  for (int i = 0; i < new_height; i++)
    *(new_image->data_matriz + i) = malloc(new_width * sizeof(RGB));


  unsigned int factor = 2;
  unsigned int sum_red = 0, sum_green = 0, sum_blue = 0;
  for(int new_y = 0; new_y < new_height; new_y++){
    for(int new_x = 0; new_x < new_width; new_x++){
      sum_red = 0, sum_green = 0, sum_blue = 0;
      for(int i = 0; i < factor; i++){
        for(int j = 0; j < factor; j++){
          sum_red += image->data_matriz[new_y*factor+i][new_x*factor+j].red;
          sum_green += image->data_matriz[new_y*factor+i][new_x*factor+j].green;
          sum_blue += image->data_matriz[new_y*factor+i][new_x*factor+j].blue;
        }
      }
      new_image->data_matriz[new_y][new_x].red = sum_red / (factor*factor);
      new_image->data_matriz[new_y][new_x].green = sum_green / (factor*factor);
      new_image->data_matriz[new_y][new_x].blue = sum_blue / (factor*factor);
    }
  }
  return new_image;
}

