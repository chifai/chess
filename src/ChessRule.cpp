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

bool CChessRule::isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam)
{
    TPosition PossibleAttacker[PIECE_NUM];
    int PossibleAttackerNum = getPossibleAttackers(PiecePos, Prey, AttackerTeam, PossibleAttacker);
    for (int i = 0; i < PossibleAttackerNum; i++) {
        if (isAttackSuccess(PiecePos, PossibleAttacker[i], Prey)) return true;
    }

    return false;
}

int CChessRule::getAllAttackers(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM]) 
{
    TPosition PossibleAttacker[PIECE_NUM];
    int PossibleAttackerNum = getPossibleAttackers(PiecePos, Prey, AttackerTeam, PossibleAttacker);
    int AttackerNum = 0;
    for (int i = 0; i < PossibleAttackerNum; i++) {
        if (isAttackSuccess(PiecePos, PossibleAttacker[i], Prey)) Attacker[AttackerNum++] = PossibleAttacker[i];
    }

    return AttackerNum;
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

bool CChessRule::isAttackSuccess(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Predator, const TPosition &Prey)
{
    // assert false if same position
    if (Predator == Prey) {
        assert(false);
        return false;
    }

    TSquareStatus PredatorSq = PiecePos[Predator.y * BOARD_SIZE + Predator.x];

    // return false if predator pos is empty
    if (PredatorSq.isOccupied() == false) return false;

    // check if success according to different piece type
    int xDiff = Predator.x - Prey.x;
    int yDiff = Predator.y - Prey.y;
    switch (PredatorSq.PieceType) {
    case Pawn:
        if (abs(xDiff) != 1) return false;
        return PredatorSq.PieceTeam == White ? yDiff == -1 : yDiff== 1;

    case Knight:
        return (abs(xDiff) == 2 && abs(yDiff) == 1) || (abs(xDiff) == 1 && abs(yDiff) == 2);

    case Bishop:
        return abs(xDiff) == abs(yDiff);

    case Rook:
        return xDiff * yDiff == 0;

    case Queen:
        return abs(xDiff) == abs(yDiff) || xDiff * yDiff == 0;

    case King:
        return abs(xDiff) <= 1 && abs(yDiff) <= 1;

    default:
        assert(false);
    }

    return false;
}

int CChessRule::getPossibleAttackers(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM])
{
    ETeam DefenserTeam = AttackerTeam == White ? Black : White;
    TPosition Predator;

    // move one step each time at different direction to find out if there is opponent piece and correct piece type
    const int OCTAL_DIRNUM = 8;
    const TPosition OctDir[OCTAL_DIRNUM] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    int AttackerNum = 0;
    for (int i = 0; i < OCTAL_DIRNUM; i++) {
        Predator = Prey + OctDir[i];
        while (Predator.inRange()) {
            ETeam PredatorTeam = PiecePos[Predator.y * BOARD_SIZE + Predator.x].PieceTeam;
            if (PredatorTeam == DefenserTeam) {
                break;
            }
            else if (PredatorTeam == AttackerTeam) {
                Attacker[AttackerNum++] = Predator;
                break;
            }
            Predator += OctDir[i];
        }
    }

    // check knight attacked
    const int KNIGHT_DIRNUM = 8;
    const TPosition KnightDir[KNIGHT_DIRNUM] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int i = 0; i < KNIGHT_DIRNUM; i++) {
        Predator = Prey + KnightDir[i];
        if (!Predator.inRange()) continue;
        ETeam PredatorTeam = PiecePos[Predator.y * BOARD_SIZE + Predator.x].PieceTeam;
        if (PredatorTeam == DefenserTeam) continue;
        if (PredatorTeam == AttackerTeam) Attacker[AttackerNum++] = Predator;
    }

    return AttackerNum;
}