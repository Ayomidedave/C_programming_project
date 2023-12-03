CC = gcc
CFLAGS = -Wall -Wextra

all: bplus_compiler

bplus_compiler: lexer.o main.o
	$(CC) $(CFLAGS) -o bplus_compiler lexer.o main.o

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o bplus_compiler

