gol: gol.c gol.h
	gcc -o gol gol.c -Wall -Werror -pedantic -ggdb -lraylib -lm -lX11 -lpthread -lrt -ldl
