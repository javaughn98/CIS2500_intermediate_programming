compile: a1p1 a1p2 a1p3 a1p4 tictactoe

tictactoe: ./src/tictactoe.c ./include/tictactoe.h
	gcc -Wall -ansi -pedantic -c ./src/tictactoe.c -o tictactoe.o

a1p1: ./src/a1p1.c tictactoe
	gcc -Wall -ansi -pedantic ./src/a1p1.c tictactoe.o -o a1p1

a1p2: ./src/a1p2.c tictactoe
	gcc -Wall -ansi -pedantic ./src/a1p2.c tictactoe.o -o a1p2

a1p3: ./src/a1p3.c tictactoe
	gcc -Wall -ansi -pedantic ./src/a1p3.c tictactoe.o -o a1p3

a1p4: ./src/a1p4.c tictactoe
	gcc -Wall -ansi -pedantic ./src/a1p4.c tictactoe.o -o a1p4

run: compile
