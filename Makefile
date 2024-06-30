all: main

CC = gcc
override CFLAGS += -g -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(SRCS) $(CFLAGS)  -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(SRCS) -o "$@" -O0 $(CFLAGS) 

clean:
	rm -f main main-debug
