#include <stdio.h>
#include "headers/image.h"
#include "headers/terminal_display.h"
#include "headers/utils.h"

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

  IMAGE *original_image = imageStructureBuilder(file_buffer);
  imagePainter(original_image);
  getchar();
  IMAGE *teste = imageScaler(original_image,50,50);
  imagePainter(teste);

  freeImage(original_image);
  freeImage(teste);

  return 0;
}