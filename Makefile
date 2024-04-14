.DEFAULT_GOAL := run

CC=/opt/g++-9.5.0/bin/g++

clean:
	@rm -f *.o
	@rm -f *.out

run:
	@echo "Compiling..."
	@ g++ -Wall -Wextra --pedantic -o cacheSim cache.cpp