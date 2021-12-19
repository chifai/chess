#include <cassert>
#include <cmath>
#include "GameBoard.h"
#include "Pawn.h"

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
    const CPiece *pFrom = (*m_pGameBoard)[From];
    const CPiece *pTo = (*m_pGameBoard)[To];
    assert(pFrom != nullptr);
    EType Type = pFrom->getType();
    assert(Type == Chess::Pawn);

    // check step
    if (From.x + m_nRowToMoveEach != To.x) return false;

    if (From.y == To.y) {
        // can only move forward to empty piece
        return pTo == nullptr;
    }
    else if (From.y - To.y == 1 || From.y - To.y == -1) {
        // can only move diagonally when opponent's piece is there
        return pTo != nullptr && pTo->getTeam() != m_Team;
    }

    // #TODO: check en passant
    return false;
}
