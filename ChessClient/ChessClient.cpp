#include <iostream>
#include <cstring>
#include <cassert>
#include "ChessGame.h"

void printBoard(const CChessGame& Game);
void printPieceName(const TSquareStatus& pPiece);
void overallTest1(CChessGame& Game);
void checkKingSafeTest(CChessGame& Game);

int main()
{
    CChessGame Game;

    checkKingSafeTest(Game);
    printBoard(Game);

    system("pause");
    return 0;
}
void checkKingSafeTest(CChessGame& Game)
{
    printf("Game Start\n");

    printf("test pawn: ");
	printf("%d, ", Game.moveOnePiece({ 4, 1 }, { 4, 3 }));  // white pawn forward
    printf("%d, ", Game.moveOnePiece({ 4, 6 }, { 4, 5 }));  // black pawn forward
    printf("\n");
}

void overallTest1(CChessGame &Game)
{
    printf("Game Start\n");

    printf("test pawn: ");
    printf("%d, ", Game.moveOnePiece({ 1, 1 }, { 1, 2 }));  // white pawn forward
    printf("%d, ", Game.moveOnePiece({ 1, 6 }, { 1, 4 }));  // black pawn forward
    printf("\n");

    printf("test knight: ");
    printf("%d, ", Game.moveOnePiece({ 1, 0 }, { 2, 2 }));  // white knight forward
    printf("%d, ", Game.moveOnePiece({ 1, 7 }, { 0, 5 }));  // black knight forward
    printf("\n");

    printf("invalid pawn move: ");
    printf("%d, ", !Game.moveOnePiece({ 0, 1 }, { 1, 2 }));  // invalid
    printf("%d, ", !Game.moveOnePiece({ 0, 6 }, { 0, 4 }));  // invalid
    printf("\n");

    printf("test bishop: ");
    printf("%d, ", Game.moveOnePiece({ 2, 0 }, { 0, 2 }));
    printf("%d, ", Game.moveOnePiece({ 2, 7 }, { 1, 6 }));
    printf("%d, ", Game.moveOnePiece({ 0, 2 }, { 4, 6 }));
    printf("\n");

    printf("test Rook: ");
    printf("%d, ", Game.moveOnePiece({ 0, 7 }, { 2, 7 }));
    printf("%d, ", Game.moveOnePiece({ 0, 0 }, { 1, 0 }));
    printf("%d, ", !Game.moveOnePiece({ 2, 7 }, { 2, 6 }));  // invalid
    printf("%d, ", Game.moveOnePiece({ 2, 7 }, { 1, 7 }));
    printf("%d, ", Game.moveOnePiece({ 1, 0 }, { 1, 1 }));
    printf("\n");

    // black move
    printf("test queen: ");
    printf("%d, ", Game.moveOnePiece({ 3, 7 }, { 4, 6 }));
    printf("%d, ", Game.moveOnePiece({ 3, 1 }, { 3, 3 }));
    printf("%d, ", !Game.moveOnePiece({ 4, 6 }, { 3, 3 }));  // invalid
    printf("%d, ", !Game.moveOnePiece({ 3, 0 }, { 7, 4 }));  // invalid
    printf("%d, ", Game.moveOnePiece({ 4, 6 }, { 4, 2 }));
    printf("\n");

    printf("test king: ");
    printf("%d, ", Game.moveOnePiece({ 5, 1 }, { 4, 2 }));
    printf("%d, ", Game.moveOnePiece({ 4, 7 }, { 4, 6 }));
    printf("%d, ", Game.moveOnePiece({ 4, 0 }, { 3, 1 }));
    printf("\n");

    printf("test attacker check:\n");
    TPosition Attacker[PIECE_NUM] = {};
    int AttackerNum;

    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({ 3, 4 }, ETeam::Black, Attacker);
    printf("%d, {%d, %d}\n", AttackerNum, Attacker[0].x, Attacker[0].y);
    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({ 1, 4 }, ETeam::White, Attacker);
    printf("%d, {%d, %d}\n", AttackerNum, Attacker[0].x, Attacker[0].y);
    memset(Attacker, 0, sizeof(Attacker));
    AttackerNum = Game.getAttackers({ 2, 1 }, ETeam::White, Attacker);
    printf("%d, {%d, %d}, {%d, %d}, {%d, %d}\n", AttackerNum,
        Attacker[0].x, Attacker[0].y,
        Attacker[1].x, Attacker[1].y,
        Attacker[2].x, Attacker[2].y
    );

    printf("test king valid move\n");
    printf("%d, ", Game.moveOnePiece({ 0, 5 }, { 1, 3 }));
    printf("%d, ", !Game.moveOnePiece({ 3, 1 }, { 3, 2 }));  // invalid king move
    printf("%d, ", Game.moveOnePiece({ 2, 2 }, { 3, 4 }));
    printf("%d, ", !Game.moveOnePiece({ 2, 6 }, { 2, 5 }));  // invalid move, king is checked
    printf("%d, ", Game.moveOnePiece({ 1, 6 }, { 3, 4 }));  // bishop takes knight valid
    printf("\n");

    printf("test pawn promotion\n");
    printf("%d-%d, ", Game.moveOnePiece({ 2, 1 }, { 2, 3 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 6 }, { 2, 4 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 3 }, { 3, 4 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 4 }, { 2, 3 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 3, 4 }, { 3, 5 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 4, 6 }, { 4, 5 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 6, 1 }, { 6, 3 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 3 }, { 2, 2 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 3, 1 }, { 4, 0 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 2 }, { 2, 1 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 6, 3 }, { 6, 4 }), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 2, 1 }, { 2, 0 }), Game.getState());
    printf("%d-%d, ", !Game.moveOnePiece({ 3, 0 }, { 3, 1 }), Game.getState());
    printf("%d-%d, ", !Game.moveOnePiece({ 5, 6 }, { 5, 5 }), Game.getState());
    printf("%d-%d, ", !Game.moveOnePiece({ 2, 1 }, { 2, 0 }), Game.getState());
    printf("%d-%d, ", !Game.promote({ 0, 6 }, EType::Knight), Game.getState());
    printf("%d-%d, ", !Game.promote({ 2, 0 }, EType::King), Game.getState());
    printf("%d-%d, ", Game.promote({ 2, 0 }, EType::Queen), Game.getState());
    printf("%d-%d, ", Game.moveOnePiece({ 4, 2 }, { 4, 3 }), Game.getState());
}

void printBoard(const CChessGame& Game)
{
    TPosition Pos;
    TSquareStatus Piece;
    printf("\n----------\n");
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        printf("%d-| ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            Pos.x = j;
            Pos.y = i;
            Piece = Game.getPiece(Pos);

            printPieceName(Piece);
            printf(" | ");
        }
        printf("\n");
    }
    printf("--| 0------- | 1------- | 2------- | 3------- | 4------- | 5------- | 6------- | 7------- |\n");
}

void printPieceName(const TSquareStatus& pPiece)
{
    if (pPiece.PieceTeam == ETeam::None) {
        printf("----    ");
        return;
    }

    // print team
    if (pPiece.PieceTeam == ETeam::White) {
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