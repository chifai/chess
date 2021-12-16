#include "Piece.h"

CPiece::CPiece()
{
}

CPiece::~CPiece()
{
}

void CPiece::init(const ETeam Team, const TPosition &Pos)
{
    m_Team = Team;
    m_Position = Pos;
}

const TPosition &CPiece::getPosition() const
{
    return m_Position;
}
