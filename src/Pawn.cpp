#include "Pawn.h"
#include <cassert>

CPawn::CPawn(const ETeam Team) : CPiece(Team)
{
    m_nRowToMoveEach = Team == White ? 1 : -1;
}

CPawn::~CPawn()
{
}

EType CPawn::getType() const
{
    return Chess::Pawn;
}

bool CPawn::isValidMove(const TPosition &From, const TPosition &To) const
{
    // check type
    // EType Type = m_pPiecePos[From.x][From.y].getType();
    // assert( m_pPiecePos[From.x][From.y].getType() == Chess::Pawn);

    return false;
}
