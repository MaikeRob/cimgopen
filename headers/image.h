#ifndef IMAGE_H
#define IMAGE_H

// Retorna o numero de digitos de um inteiro
#define NUM_OF_DIGITS(number) ((int)floor(log10(number)) + 1)

//ARRUMAR MACROS
#define MAX_HEIGHT 100 
#define MAX_WIDTH 100

typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} RGB;

typedef struct {
unsigned int height;//altura, numero de linhas
unsigned int width;//largura, numero de colunas
RGB media;
RGB **data_matriz;
} IMAGE;

//Posições de informações importantes no buffer da imagem PPM
#define EMPTY_BUFFER_SPACE 1
#define PPM_HEIGHT_BUFFER_POSITION 3
#define PPM_WIDTH_BUFFER_POSITION(IMAGE_HEIGHT) PPM_HEIGHT_BUFFER_POSITION + EMPTY_BUFFER_SPACE + NUM_OF_DIGITS(IMAGE_HEIGHT) 


//Protótipos das funções 
IMAGE* imageStructureBuilder(unsigned char* file_buffer);

void imagePainter(IMAGE* image);

void freeImage(IMAGE* image);

IMAGE *imageScaler(IMAGE *image, int new_width, int new_height);
#endif