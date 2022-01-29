#include <iostream>
#include <cassert>
#include "ChessGame.h"

bool askValidMove(const CChessGame &Game);
void printBoard(const CChessGame &Game);
void printPieceName(const TSquareStatus &pPiece);

int main()
{
    CChessGame Game;
    printf("Game Start\n");

    printf("move pawn: ");
    printf("%d, ", Game.moveOnePiece({1, 1}, {2, 1}));  // white pawn forward
    printf("%d, ", Game.moveOnePiece({6, 1}, {4, 1}));  // black pawn forward
    printf("\n");

    printf("move knight: ");
    printf("%d, ", Game.moveOnePiece({0, 1}, {2, 2}));  // white knight forward
    printf("%d, ", Game.moveOnePiece({7, 1}, {5, 0}));  // black knight forward
    printf("\n");

    printf("invalid pawn move: ");
    printf("%d, ", Game.moveOnePiece({1, 0}, {2, 1}));
    printf("%d, ", Game.moveOnePiece({6, 0}, {4, 0}));
    printf("\n");

    printf("move bishop: ");
    printf("%d, ", Game.moveOnePiece({0, 2}, {2, 0}));
    printf("%d, ", Game.moveOnePiece({7, 2}, {6, 1}));
    printf("%d, ", Game.moveOnePiece({2, 0}, {6, 4}));
    printf("\n");

    printf("move Rook: ");
    printf("%d, ", Game.moveOnePiece({7, 0}, {7, 2}));
    printf("%d, ", Game.moveOnePiece({0, 0}, {0, 1}));
    printf("%d, ", Game.moveOnePiece({7, 2}, {6, 2}));  // invalid
    printf("%d, ", Game.moveOnePiece({7, 2}, {7, 1}));
    printf("%d, ", Game.moveOnePiece({0, 1}, {1, 1}));
    printf("\n");

    // black move
    printf("move queen: ");
    printf("%d, ", Game.moveOnePiece({7, 3}, {6, 4}));
    printf("%d, ", Game.moveOnePiece({1, 3}, {3, 3}));
    printf("%d, ", Game.moveOnePiece({6, 4}, {3, 3}));
    printf("%d, ", Game.moveOnePiece({0, 3}, {4, 7}));
    printf("%d, ", Game.moveOnePiece({6, 4}, {2, 4}));
    printf("\n");

    printBoard(Game);

    // while(askValidMove(Game) == true) {}
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

    printf("Move from (%d, %d) to (%d, %d): %d\n\n", From.x, From.y, To.x, To.y, Game.isSafePieceMove(From, To));
    return true;
}

void printBoard(const CChessGame &Game)
{
    TPosition Pos;
    TSquareStatus Piece;
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        printf("| ");
        for (int j = 0; j < BOARD_SIZE; j++) {
            Pos.x = i;
            Pos.y = j;
            Piece = Game.getPiece(Pos);

            printPieceName(Piece);
            printf(" | ");
        }
        printf("\n");
    }
}

void printPieceName(const TSquareStatus &pPiece)
{
    if (pPiece.PieceTeam == None) {
        printf("----    ");
        return;
    }

    // print team
    if (pPiece.PieceTeam == White) {
        printf("W.");
    }
    else {
        printf("B.");
    }

    EType PieceType = pPiece.PieceType;
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