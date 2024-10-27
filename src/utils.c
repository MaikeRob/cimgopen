#include <stdio.h>
#include "../headers/utils.h"

/*Devolve o tamanho de um arquivo*/
long fsize(FILE *file_pointer) {
  fseek(file_pointer, 0, SEEK_END);
  long temp = ftell(file_pointer);
  fseek(file_pointer, 0, SEEK_SET);
  return temp;
}