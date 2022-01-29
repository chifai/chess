// check if the move is valid:
// 1. not being blocked on the way
// 2. target position not being blocked by its own team piece
// 3. some rules require previous move log
#pragma once
#include "ChessDef.h"
#include "MoveLog.h"
using namespace Chess;

namespace ChessRule {
    // check pawn move if valid, en passant requires MoveLog
    bool movePawn(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To);

    // check bishop move if valid
    bool moveBishop(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check knight move if valid
    bool moveKnight(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check rook move if valid
    bool moveRook(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check queen move if valid
    bool moveQueen(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &From, const TPosition &To);

    // check king move if valid, castle requires MoveLog
    bool moveKing(const TSquareStatus PiecePos[SQUARE_NUM], const CMoveLog &Log, const TPosition &From, const TPosition &To);

    // check if attacked
    bool isAttacked(const TSquareStatus PiecePos[SQUARE_NUM], const TPosition &Piece);
};