.DEFAULT_GOAL := run

CC=gcc
CFLAGS= -Wall -Wextra --pedantic

clean:
	@rm -f cacheSim

run: cache.cpp
	@echo "Compiling..."
	@ $(CC) -o cacheSim cache.cpp $(CFLAGS) -lstdc++