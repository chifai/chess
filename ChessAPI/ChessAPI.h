#pragma once

#ifdef CHESSAPI_EXPORTS
#define CHESS_API __declspec(dllexport)
#else
#define CHESS_API __declspec(dllimport)
#endif

#include "ChessGame.h"

enum class EPieceType : int
{
    None = 0,
    W_Pawn,
    W_Knight,
    W_Bishop,
    W_Rook,
    W_Queen,
    W_King,
    B_Pawn,
    B_Knight,
    B_Bishop,
    B_Rook,
    B_Queen,
    B_King,
};

namespace ChessAPI {
    // initialize a new game
    extern "C" CHESS_API void resetBoard();

    // move one piece
    extern "C" CHESS_API bool moveOnePiece(const int FromInd, const int ToInd);

    // move a pawn to the end and promote to a piece
    extern "C" CHESS_API bool promote(const Chess::TPosition & From, const Chess::EType PromoteType);

    // check if it is a valid piece move and the king is safe
    extern "C" CHESS_API bool isSafePieceMove(const Chess::TPosition& From, const Chess::TPosition& To);

    // check if a piece is being attacked and show all of the attacking positions
    extern "C" CHESS_API int getAttackers(const Chess::TPosition& Prey, const Chess::ETeam AttackerTeam, Chess::TPosition Attacker[PIECE_NUM]);

    // show all valid move on particular piece, return the numbers
    // extern "C" CHESS_API int showAllValidMoves(const Chess::TPosition& From, Chess::TPosition ValidDest[]);

    // get the piece of particular position
    extern "C" CHESS_API EPieceType getPiece(const int PosInd);

    // get game state
    extern "C" CHESS_API Chess::EGameState getState();
}