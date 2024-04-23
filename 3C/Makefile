.all: clean

CC = gcc
CFLAGS = -O3 -Wall -Wextra --pedantic

clean: run
	@rm -f *.out

run:
	@$(CC) main.cpp $(CFLAGS) -lstdc++
	@./a.out