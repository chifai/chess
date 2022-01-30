#include <iostream>
#include <cstring>
#include <cassert>
#include "ChessGame.h"

bool askValidMove(const CChessGame &Game);
void printBoard(const CChessGame &Game);
void printPieceName(const TSquareStatus &pPiece);

int main()
{
    CChessGame Game;
    printf("Game Start\n");

    printf("test pawn: ");
    printf("%d, ", Game.moveOnePiece({1, 1}, {1, 2}));  // white pawn forward
    printf("%d, ", Game.moveOnePiece({1, 6}, {1, 4}));  // black pawn forward
    printf("\n");

    printf("test knight: ");
    printf("%d, ", Game.moveOnePiece({1, 0}, {2, 2}));  // white knight forward
    printf("%d, ", Game.moveOnePiece({1, 7}, {0, 5}));  // black knight forward
    printf("\n");

    printf("invalid pawn move: ");
    printf("%d, ", Game.moveOnePiece({0, 1}, {1, 2}));  // invalid
    printf("%d, ", Game.moveOnePiece({0, 6}, {0, 4}));  // invalid
    printf("\n");

    printf("test bishop: ");
    printf("%d, ", Game.moveOnePiece({2, 0}, {0, 2}));
    printf("%d, ", Game.moveOnePiece({2, 7}, {1, 6}));
    printf("%d, ", Game.moveOnePiece({0, 2}, {4, 6}));
    printf("\n");

    printf("test Rook: ");
    printf("%d, ", Game.moveOnePiece({0, 7}, {2, 7}));
    printf("%d, ", Game.moveOnePiece({0, 0}, {1, 0}));
    printf("%d, ", Game.moveOnePiece({2, 7}, {2, 6}));  // invalid
    printf("%d, ", Game.moveOnePiece({2, 7}, {1, 7}));
    printf("%d, ", Game.moveOnePiece({1, 0}, {1, 1}));
    printf("\n");

    // black move
    printf("test queen: ");
    printf("%d, ", Game.moveOnePiece({3, 7}, {4, 6}));
    printf("%d, ", Game.moveOnePiece({3, 1}, {3, 3}));
    printf("%d, ", Game.moveOnePiece({4, 6}, {3, 3}));  // invalid
    printf("%d, ", Game.moveOnePiece({3, 0}, {7, 4}));  // invalid
    printf("%d, ", Game.moveOnePiece({4, 6}, {4, 2}));
    printf("\n");

    printf("test king: ");
    printf("%d, ", Game.moveOnePiece({5, 1}, {4, 2}));
    printf("%d, ", Game.moveOnePiece({4, 7}, {4, 6}));
    printf("%d, ", Game.moveOnePiece({4, 0}, {3, 1}));
    printf("\n");

    printf("test attacker check:\n");
    TPosition Attacker[PIECE_NUM] = {};
    int AttackerNum;

    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({3, 4}, Black, Attacker);
    printf("%d, {%d, %d}\n", AttackerNum, Attacker[0].x, Attacker[0].y);
    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({1, 4}, White, Attacker);
    printf("%d, {%d, %d}\n", AttackerNum, Attacker[0].x, Attacker[0].y);
    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({2, 1}, White, Attacker);
    printf("%d, {%d, %d}, {%d, %d}, {%d, %d}\n", AttackerNum,
    Attacker[0].x, Attacker[0].y,
    Attacker[1].x, Attacker[1].y,
    Attacker[2].x, Attacker[2].y
    );

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
            Pos.x = j;
            Pos.y = i;
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