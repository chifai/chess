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
    // reset the state as ongoing
    m_GameState = Ongoing;

    // reset move state: white to move
    m_MoveState = WhiteMove;

    CPiece::setBoard(&m_GameBoard);

    // clear move log
    m_MoveLog.clear();

}

bool CChessGame::isValidMove(const TPosition &From, const TPosition &To) const
{
    const CPiece *pFromPiece = m_GameBoard[From];

    // piece exists
    if (pFromPiece == nullptr) return false;

    // check piece team matches with move state
    const ETeam FromTeam = pFromPiece->getTeam();
    if ((FromTeam == White) && (m_MoveState != WhiteMove)) return false;
    if ((FromTeam == Black) && (m_MoveState != BlackMove)) return false;

    // call piece function to check if valid
    return pFromPiece->isValidMove(From, To);
}

bool CChessGame::move(const TPosition &From, const TPosition &To)
{
    return false;
}

const CPiece *CChessGame::getPiece(const TPosition &Pos) const
{
    return m_GameBoard[Pos];
}