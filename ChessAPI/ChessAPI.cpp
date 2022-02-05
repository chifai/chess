#include "ChessGame.h"
#include "ChessAPI.h"

static CChessGame g_ChessGame;

void ChessAPI::resetBoard()
{
    g_ChessGame.init();
}

bool ChessAPI::moveOnePiece(const Chess::TPosition& From, const Chess::TPosition& To)
{
    return g_ChessGame.moveOnePiece(From, To);
}

bool ChessAPI::promote(const Chess::TPosition & From, const Chess::EType PromoteType)
{
    return g_ChessGame.promote(From, PromoteType);
}

bool ChessAPI::isSafePieceMove(const Chess::TPosition& From, const Chess::TPosition& To)
{
    return g_ChessGame.isSafePieceMove(From, To);
}

int ChessAPI::getAttackers(const Chess::TPosition& Prey, const Chess::ETeam AttackerTeam, Chess::TPosition Attacker[PIECE_NUM])
{
    return g_ChessGame.getAttackers(Prey, AttackerTeam, Attacker);
}

// int showAllValidMoves(const Chess::TPosition& From, Chess::TPosition ValidDest[])
// {
//    return g_ChessGame.showAllValidMoves(From, ValidDest);
// }

void ChessAPI::getPiece(const Chess::TPosition& Pos, Chess::TSquareStatus &SquareStatus)
{
    SquareStatus = g_ChessGame.getPiece(Pos);
}

Chess::EGameState ChessAPI::getState()
{
    return g_ChessGame.getState();
}