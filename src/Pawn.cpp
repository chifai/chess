#include "Pawn.h"
#include <cassert>
#include <cmath>

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
    const CPiece *pFrom = m_pPieceMap->at(From);
    const CPiece *pTo = m_pPieceMap->at(To);
    EType Type = pFrom->getType();
    assert( Type == Chess::Pawn);

    // check step
    if (From.x + m_nRowToMoveEach != To.x) return false;

    if (From.y == To.y) {
        // can only move forward to empty piece
        return pTo == nullptr;
    }
    else if (From.y - To.y == 1 || From.y - To.y == -1) {
        // can only take opponents pawn when moving diagonally
        return pTo != nullptr && pTo->getTeam() != m_Team;
    }

    // #TODO: check en passant
    return false;
}
