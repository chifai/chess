#include "ChessGame.h"
#include <stdlib.h>
#include <cstring>
#include <cassert>

CChessGame::CChessGame()
{
    // init a new game
    init();
}

CChessGame::~CChessGame()
{
}

void CChessGame::init()
{
    // reset the state as white move
    m_GameState = WhiteMove;

    CPiece::setBoard(&m_GameBoard);

    // clear move log
    m_MoveLog.clear();

}

bool CChessGame::isValidMove(const TPosition &From, const TPosition &To) const
{
    const CPiece *pFromPiece = m_GameBoard[From];

    // piece exists
    if (pFromPiece == nullptr) return false;

    // call piece function to check if valid
    return pFromPiece->isValidMove(From, To);
}

bool CChessGame::move(const TPosition &From, const TPosition &To)
{
    const CPiece *pFromPiece = m_GameBoard[From];

    // piece exists
    if (pFromPiece == nullptr) return false;

    // check piece team matches with correct move state
    const ETeam FromTeam = pFromPiece->getTeam();
    if ((FromTeam == White) && (m_GameState != WhiteMove)) return false;
    if ((FromTeam == Black) && (m_GameState != BlackMove)) return false;

    // call piece function to check if valid
    return pFromPiece->isValidMove(From, To);
}

const CPiece *CChessGame::getPiece(const TPosition &Pos) const
{
    return m_GameBoard[Pos];
}