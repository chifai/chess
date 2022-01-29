#include "ChessRule.h"
#include <cmath>

bool ChessRule::movePawn(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
{
    // check type
    if (PiecePos[From.x * BOARD_SIZE + From.y].PieceType != Pawn) return false;

    ETeam FromTeam = PiecePos[From.x * BOARD_SIZE + From.y].PieceTeam;
    ETeam OppoTeam = FromTeam == White ? Black : White;
    TSquareStatus ToSquare = PiecePos[To.x * BOARD_SIZE + To.y];
    // if pawn move one step forward
    if ((FromTeam == White && From.x + 1 == To.x) || (FromTeam == Black && From.x - 1 == To.x)) {
        // if go straight, no piece should be at target position
        if (From.y == To.y && ToSquare.PieceTeam == None) return true;
        // if go sideway, should be a capture
        if (abs(From.y - To.y) == 1 && ToSquare.PieceTeam == OppoTeam) return true;
        // #TODO: check sideway en passant
        // else return false
        return false;
    }
    else if (FromTeam == White && From.x == 1 && To.x == 3) {
        // white pawn moves two steps forward condition
        return From.y == To.y && ToSquare.PieceTeam == None;
    }
    else if (FromTeam == Black && From.x == 6 && To.x == 4) {
        // black pawn moves two steps forward condition
        return From.y == To.y && ToSquare.PieceTeam == None;
    }

    return false;
}

bool ChessRule::moveBishop(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    return false;
}

bool ChessRule::moveKnight(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.x * BOARD_SIZE + From.y];
    // check type
    if (SqFrom.PieceType != Knight) return false;

    // check target position is not friendly
    if (PiecePos[To.x * BOARD_SIZE + To.y].PieceTeam == SqFrom.PieceTeam) return false;

    // check move
    if (abs(From.x - To.x) == 2 && abs(From.y - To.y) == 1) return true;
    if (abs(From.x - To.x) == 1 && abs(From.y - To.y) == 2) return true;

    return false;
}

bool ChessRule::moveRook(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    return false;
}

bool ChessRule::moveQueen(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    return false;
}

bool ChessRule::moveKing(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
{
    return false;
}

bool ChessRule::isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Piece)
{
    return false;
}