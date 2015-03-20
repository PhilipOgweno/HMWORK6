# My makefile for Programm Homework6.cpp
# the compiler to use.
CC = g++
CFLAGS = -Wall

all: hw6

hw6: philip.cpp

	${CC} ${CFLAGS} philip.cpp -o philip

clean:
	rm  -rf philip
