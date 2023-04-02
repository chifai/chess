#include "ChessGame.h"
#include "ChessAPI.h"

static CChessGame g_ChessGame;

void ChessAPI::resetBoard()
{
    g_ChessGame.init();
}

bool ChessAPI::moveOnePiece(const int FromInd, const int ToInd)
{
    TPosition FromPos, ToPos;
    FromPos.x = FromInd % BOARD_SIZE;
    FromPos.y = FromInd / BOARD_SIZE;
    ToPos.x = ToInd % BOARD_SIZE;
    ToPos.y = ToInd / BOARD_SIZE;

    return g_ChessGame.moveOnePiece(FromPos, ToPos);
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

EPieceType ChessAPI::getPiece(const int PosInd)
{
    TPosition Pos;
    Pos.x = PosInd % BOARD_SIZE;
    Pos.y = PosInd / BOARD_SIZE;
    TSquareStatus SqStatus = g_ChessGame.getPiece(Pos);

    if (SqStatus.isOccupied() == false) {
        return EPieceType::None;
    }

    return (EPieceType)(((int)SqStatus.PieceType + 1) + ((int)SqStatus.PieceTeam * 6));
}

Chess::EGameState ChessAPI::getState()
{
    return g_ChessGame.getState();
}