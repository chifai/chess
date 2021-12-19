#include "Piece.h"
#include <cassert>

std::map <TPosition, const CPiece *> *CPiece::m_pPieceMap = nullptr;

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

void CPiece::setBoard(std::map <TPosition, const CPiece *> *pPieceMap)
{
    m_pPieceMap = pPieceMap;
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

bool CPiece::isAlive() const
{
    return m_bAlive;
}