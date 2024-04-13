.DEFAULT_GOAL := run

CC=/opt/g++-9.5.0/bin/g++

clean:
	@rm -f *.o
	@rm -f *.out

run:
	@echo "Compiling..."
	@g++ -w -o cacheSim cache.cpp
	@# @g++ -Wall -Wextra --pedantic -o cacheSim cache.cpp