#include <cassert>
#include "GameBoard.h"
#include "Piece.h"

const CGameBoard *CPiece::m_pGameBoard = nullptr;

#define UNDEF_POS   ( -1 )

CPiece::CPiece(const ETeam Team)
{
    m_Team = Team;
    m_Pos.x = UNDEF_POS;
    m_Pos.y = UNDEF_POS;
    m_bAlive = true;
}

ETeam CPiece::getTeam() const
{
    return m_Team;
}

void CPiece::setBoard(const CGameBoard *pGameBoard)
{
    m_pGameBoard = pGameBoard;
}

CPiece::~CPiece()
{
}

void CPiece::setPos(const TPosition &Pos)
{
    assert(Pos.x >= 0 && Pos.x < BOARD_SIZE);
    assert(Pos.y >= 0 && Pos.y < BOARD_SIZE);

    m_Pos = Pos;
}

const TPosition& CPiece::getPos() const
{
    return m_Pos;
}

void CPiece::setAlive(const bool bAlive)
{
    m_bAlive = bAlive;
}

bool CPiece::isAlive() const
{
    return m_bAlive;
}