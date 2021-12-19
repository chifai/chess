#include <iostream>
#include <cassert>
#include "Piece.h"
#include "Pawn.h"
#include "ChessGame.h"

bool askValidMove(const CChessGame &Game);
void printBoard(const CChessGame &Game);
void printPieceName(const CPiece *pPiece);

int main()
{
    CChessGame Game;
    printf("Game Start\n");
    printBoard(Game);

    while(askValidMove(Game) == true) {}
    return 0;
}

bool askValidMove(const CChessGame &Game)
{
    TPosition From, To;
    int nValidScanNum;
    printf("Enter From Pos: (x,y), or nothing for quit\n");
    nValidScanNum = scanf("%d,%d", &From.x, &From.y);
    if (nValidScanNum != 2) {
        printf("Quit\n");
        return false;
    }

    printf("Enter To Pos: (x,y), or nothing for quit\n");
    nValidScanNum = scanf("%d,%d", &To.x, &To.y);
    if (nValidScanNum != 2) {
        printf("Quit\n");
        return false;
    }

    printf("Move from (%d, %d) to (%d, %d): %d\n\n", From.x, From.y, To.x, To.y, Game.isValidMove(From, To));
    return true;
}

void printBoard(const CChessGame &Game)
{
    TPosition Pos;
    const CPiece *pPiece = nullptr;
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        printf("| ");
        for (int j = 0; j < BOARD_SIZE; j++) {
            Pos.x = i;
            Pos.y = j;
            pPiece = Game.getPiece(Pos);

            printPieceName(pPiece);
            printf(" | ");
        }
        printf("\n");
    }
}

void printPieceName(const CPiece *pPiece)
{
    if (pPiece == nullptr) {
        printf("----    ");
        return;
    }

    // print team
    if (pPiece->getTeam() == White) {
        printf("W.");
    }
    else {
        printf("B.");
    }

    EType PieceType = pPiece->getType();
    switch (PieceType)
    {
    case EType::Pawn:
        printf("Pawn  ");
        break;

    case EType::Knight:
        printf("Knight");
        break;

    case EType::Bishop:
        printf("Bishop");
        break;

    case EType::Rook:
        printf("Rook  ");
        break;

    case EType::Queen:
        printf("Queen ");
        break;

    case EType::King:
        printf("King  ");
        break;

    default:
        assert(false);
        break;
    }
}