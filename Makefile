.DEFAULT_GOAL := run

CC=g++
CFLAGS= -Wall -Wextra --pedantic

clean:
	@rm -f *.o
	@rm -f *.out

run:
	@echo "Compiling..."
	@ $(CC) $(CFLAGS) -o cacheSim cache.cpp