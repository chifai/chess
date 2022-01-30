// check if the move is valid:
// 1. not being blocked on the way
// 2. target position not being blocked by its own team piece
// 3. some rules require previous move log
#pragma once
#include "ChessDef.h"
#include "MoveLog.h"
using namespace Chess;

class CChessRule {
public:
    // check piece move if valid, some requires MoveLog
    static bool movePiece(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To);

    // check if attacked
    static bool isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam);

    // get all attackers
    static int getAllAttackers(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM]);

private:
    // check pawn move if valid, en passant requires MoveLog
    static bool movePawn(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To);

    // check bishop move if valid
    static bool moveBishop(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check knight move if valid
    static bool moveKnight(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check rook move if valid
    static bool moveRook(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check queen move if valid
    static bool moveQueen(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check king move if valid, castle requires MoveLog
    static bool moveKing(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To);

    // check if any pieces blocked from two points
    static bool isBlocked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check if the move is one of the eight directions
    static bool isOctalMove(const TPosition &From, const TPosition &To);

    // check if the move is diagonal
    static bool isDiagonalMove(const TPosition &From, const TPosition &To);

    // check if the move is straight
    static bool isStraightMove(const TPosition &From, const TPosition &To);

    // check if attack success assuming no pieces in between, not including en passant
    static bool isAttackSuccess(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Predator, const TPosition &Prey);

    // get possible attacker
    static int getPossibleAttackers(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PLAYER_NUM]);
};