#include "Piece.h"

CPiece::CPiece(const ETeam Team)
{
    m_Team = Team;
}

ETeam CPiece::getTeam() const
{
    return m_Team;
}

CPiece::~CPiece()
{
}