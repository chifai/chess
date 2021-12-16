# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = g++
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o ChessGame.o Piece.o
	$(CC) $(CFLAGS) -o main main.o ChessGame.o Piece.o

# The main.o target can be written more simply

main.o: main.cpp ChessGame.h Piece.h
	$(CC) $(CFLAGS) -c main.cpp

ChessGame.o: ChessGame.h

Piece.o: Piece.h ChessGame.h