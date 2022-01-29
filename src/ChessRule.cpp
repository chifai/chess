#include "ChessRule.h"
#include <cassert>
#include <cmath>

bool CChessRule::movePawn(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
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
        return From.y == To.y && ToSquare.PieceTeam == None && isBlocked(PiecePos, From, To) == false;
    }
    else if (FromTeam == Black && From.x == 6 && To.x == 4) {
        // black pawn moves two steps forward condition
        return From.y == To.y && ToSquare.PieceTeam == None && isBlocked(PiecePos, From, To) == false;
    }

    return false;
}

bool CChessRule::moveBishop(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.x * BOARD_SIZE + From.y];
    // check type
    if (SqFrom.PieceType != Bishop) return false;

    // check if diagonal move
    if (!isDiagonalMove(From, To)) return false;

    // check target position is not friendly
    if (PiecePos[To.x * BOARD_SIZE + To.y].PieceTeam == SqFrom.PieceTeam) return false;

    // check if blocked
    return !isBlocked(PiecePos, From, To);
}

bool CChessRule::moveKnight(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
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

bool CChessRule::moveRook(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    return false;
}

bool CChessRule::moveQueen(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    return false;
}

bool CChessRule::moveKing(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
{
    return false;
}

bool CChessRule::isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Piece)
{
    return false;
}

bool CChessRule::isBlocked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    if (From.x == To.x && From.y == To.y) return false;
    if (isOctalMove(From, To) == false) {
        assert(false);
        return true;
    }

    // get steps in between
    int RowDiff = To.x - From.x;
    int ColDiff = To.y - From.y;
    int RowStep, ColStep, StepNumBetween;

    RowStep = RowDiff == 0 ? 0 : RowDiff > 0 ? 1 : -1;
    ColStep = ColDiff == 0 ? 0 : ColDiff > 0 ? 1 : -1;

    StepNumBetween = RowDiff == 0 ? ColDiff - 1 : RowDiff - 1;
    TPosition CurPos = From;
    for (int i = 0; i < StepNumBetween; i++) {
        CurPos.x += RowStep;
        CurPos.y += ColStep;
        if (PiecePos[CurPos.x * BOARD_SIZE + CurPos.y].PieceTeam != None) return true;
    }

    return false;
}

bool CChessRule::isOctalMove(const TPosition &From, const TPosition &To) 
{
    return isDiagonalMove(From, To) || isStraightMove(From, To);
}

bool CChessRule::isDiagonalMove(const TPosition &From, const TPosition &To)
{
    int RowDiff = To.x - From.x;
    int ColDiff = To.y - From.y;
    return RowDiff != 0 && abs(RowDiff) == abs(ColDiff);
}

bool CChessRule::isStraightMove(const TPosition &From, const TPosition &To)
{
    int RowDiff = To.x - From.x;
    int ColDiff = To.y - From.y;
    return RowDiff * ColDiff == 0 && RowDiff + ColDiff != 0;
}