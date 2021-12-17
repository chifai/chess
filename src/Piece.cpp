#include "Piece.h"

std::map <TPosition, const CPiece *> *CPiece::m_pPieceMap = nullptr;

CPiece::CPiece(const ETeam Team)
{
    m_Team = Team;
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