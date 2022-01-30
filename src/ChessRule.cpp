#include "ChessRule.h"
#include <cassert>
#include <cmath>

bool CChessRule::movePawn(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
{
    // check type
    if (PiecePos[From.y * BOARD_SIZE + From.x].PieceType != Pawn) return false;

    ETeam FromTeam = PiecePos[From.y * BOARD_SIZE + From.x].PieceTeam;
    ETeam OppoTeam = FromTeam == White ? Black : White;
    TSquareStatus ToSquare = PiecePos[To.y * BOARD_SIZE + To.x];
    // if pawn move one step forward
    if ((FromTeam == White && From.y + 1 == To.y) || (FromTeam == Black && From.y - 1 == To.y)) {
        // if go straight, no piece should be at target position
        if (From.x == To.x && ToSquare.PieceTeam == None) return true;
        // if go sideway, should be a capture
        if (abs(From.x - To.x) == 1 && ToSquare.PieceTeam == OppoTeam) return true;
        // #TODO: check sideway en passant
        // else return false
        return false;
    }
    else if (FromTeam == White && From.y == 1 && To.y == 3) {
        // white pawn moves two steps forward condition
        return From.x == To.x && ToSquare.PieceTeam == None && isBlocked(PiecePos, From, To) == false;
    }
    else if (FromTeam == Black && From.y == 6 && To.y == 4) {
        // black pawn moves two steps forward condition
        return From.x == To.x && ToSquare.PieceTeam == None && isBlocked(PiecePos, From, To) == false;
    }

    return false;
}

bool CChessRule::moveBishop(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.y * BOARD_SIZE + From.x];
    // check type
    if (SqFrom.PieceType != Bishop) return false;

    // check if diagonal move
    if (!isDiagonalMove(From, To)) return false;

    // check target position is not friendly
    if (PiecePos[To.y * BOARD_SIZE + To.x].PieceTeam == SqFrom.PieceTeam) return false;

    // check if blocked
    return !isBlocked(PiecePos, From, To);
}

bool CChessRule::moveKnight(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.y * BOARD_SIZE + From.x];
    // check type
    if (SqFrom.PieceType != Knight) return false;

    // check target position is not friendly
    if (PiecePos[To.y * BOARD_SIZE + To.x].PieceTeam == SqFrom.PieceTeam) return false;

    // check move
    if (abs(From.x - To.x) == 2 && abs(From.y - To.y) == 1) return true;
    if (abs(From.x - To.x) == 1 && abs(From.y - To.y) == 2) return true;

    return false;
}

bool CChessRule::moveRook(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.y * BOARD_SIZE + From.x];
    // check type
    if (SqFrom.PieceType != Rook) return false;

    // check if diagonal move
    if (!isStraightMove(From, To)) return false;

    // check target position is not friendly
    if (PiecePos[To.y * BOARD_SIZE + To.x].PieceTeam == SqFrom.PieceTeam) return false;

    // check if blocked
    return !isBlocked(PiecePos, From, To);
}

bool CChessRule::moveQueen(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.y * BOARD_SIZE + From.x];
    // check type
    if (SqFrom.PieceType != Queen) return false;

    // check if octal move
    if (!isOctalMove(From, To)) return false;

    // check target position is not friendly
    if (PiecePos[To.y * BOARD_SIZE + To.x].PieceTeam == SqFrom.PieceTeam) return false;

    // check if blocked
    return !isBlocked(PiecePos, From, To);
}

bool CChessRule::moveKing(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To)
{
    TSquareStatus SqFrom = PiecePos[From.y * BOARD_SIZE + From.x];
    // check type
    if (SqFrom.PieceType != King) return false;

    // #TODO: check castle rule

    // check if octal move and only move one step
    int RowDiff = To.x - From.x;
    int ColDiff = To.y - From.y;
    if (abs(RowDiff) > 1 || abs(ColDiff) > 1) return false;

    // check target position is not friendly
    if (PiecePos[To.y * BOARD_SIZE + To.x].PieceTeam == SqFrom.PieceTeam) return false;

    return true;
}

bool CChessRule::movePiece(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To) 
{
    EType FromType = PiecePos[From.y * BOARD_SIZE + From.x].PieceType;
    bool bValid;
    switch (FromType) {
    case Pawn: bValid = movePawn(PiecePos, Log, From, To); break;
    case Bishop: bValid = moveBishop(PiecePos, From, To); break;
    case Knight: bValid = moveKnight(PiecePos, From, To); break;
    case Rook: bValid = moveRook(PiecePos, From, To); break;
    case Queen: bValid = moveQueen(PiecePos, From, To); break;
    case King: bValid = moveKing(PiecePos, Log, From, To); break;
    case Undef: bValid = false; break;
    default: bValid = false; assert(false); break;
    }

    return bValid;
}

bool CChessRule::isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Piece)
{
    return false;
}

bool CChessRule::isBlocked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To)
{
    if (From.x == To.x && From.y == To.y) return false;
    assert(isOctalMove(From, To));

    // get steps in between
    int RowDiff = To.y - From.y;
    int ColDiff = To.x - From.x;
    int RowStep, ColStep, StepNumBetween;

    RowStep = RowDiff == 0 ? 0 : RowDiff > 0 ? 1 : -1;
    ColStep = ColDiff == 0 ? 0 : ColDiff > 0 ? 1 : -1;

    StepNumBetween = RowDiff == 0 ? ColDiff - 1 : RowDiff - 1;
    TPosition CurPos = From;
    for (int i = 0; i < StepNumBetween; i++) {
        CurPos.y += RowStep;
        CurPos.x += ColStep;
        if (PiecePos[CurPos.y * BOARD_SIZE + CurPos.x].PieceTeam != None) return true;
    }

    return false;
}

bool CChessRule::isOctalMove(const TPosition &From, const TPosition &To) 
{
    return isDiagonalMove(From, To) || isStraightMove(From, To);
}

bool CChessRule::isDiagonalMove(const TPosition &From, const TPosition &To)
{
    int RowDiff = To.y - From.y;
    int ColDiff = To.x - From.x;
    return RowDiff != 0 && abs(RowDiff) == abs(ColDiff);
}

bool CChessRule::isStraightMove(const TPosition &From, const TPosition &To)
{
    int RowDiff = To.y - From.y;
    int ColDiff = To.x - From.x;
    return RowDiff * ColDiff == 0 && RowDiff + ColDiff != 0;
}