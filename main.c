#include <stdio.h>
#include "headers/image.h"
#include "headers/terminal_display.h"

long fsize(FILE *file_pointer) {
  fseek(file_pointer, 0, SEEK_END);
  long temp = ftell(file_pointer);
  fseek(file_pointer, 0, SEEK_SET);
  return temp;
}

int main(int argc, char *argv[]){

  //Abre o arquivo dado pelo argumento e verifica se o arquivo existe
  FILE *arquivo = fopen( argv[1], "rb");
  if (arquivo == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo\n");
    return 1;
  } // criar função que trata os erros

  //Cria um buffer para armazenar o arquivo
  long file_size = fsize(arquivo);
  unsigned char file_buffer[file_size];
  size_t read_elements =
      fread(&file_buffer, sizeof(unsigned char), file_size, arquivo);
  if (read_elements != file_size) {
    fprintf(stderr, "Erro ao ler o arquivo\n");
    return 1;
  }
  fclose(arquivo);

  //Processa o buffer e cria uma estrutura de dados IMAGE
  IMAGE *original_image = imageStructureBuilder(file_buffer);
  //Imprime a imagem no terminal no modo padrão
  imagePainter(original_image);
  printPixel(1, 1, &original_image->media);
  //Libera Memoria
  freeImage(original_image);
  
  return 0;
}