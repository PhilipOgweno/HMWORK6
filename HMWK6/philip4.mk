# My makefile for Programm Homework6.cpp
# the compiler to use.
CC = g++
CFLAGS = -Wall

all: hw6

hw6: philip4.cpp

	${CC} ${CFLAGS} philip4.cpp -o philip4

clean:
	rm  -rf philip4
