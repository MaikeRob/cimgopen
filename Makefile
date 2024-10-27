all: cimg

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -lm
#-Wall e -Wextra ativam avisos de compição
#-pedantic força o compilador a aderir estritamente aos padrões da linguagem C, como ANSI C ou C99
#-lm biblioteca matematica

SRC_DIR = src
HEADERS_DIR = headers
OBJ_DIR := obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(HEADERS_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

cimg: $(OBJS)
	$(CC) -o $@ main.c $^ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) cimg
