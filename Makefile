all: main.o

CC = gcc
override CFLAGS += -g -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main.o: $(SRCS) $(HEADERS)
	$(CC) $(SRCS) $(CFLAGS)  -o "$@"

main-debug.o: $(SRCS) $(HEADERS)
	$(CC) $(SRCS) -o "$@" -O0 $(CFLAGS) 

clean:
	rm -f main.o main-debug.o
