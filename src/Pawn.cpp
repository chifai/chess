#include "Pawn.h"

CPawn::CPawn(const ETeam Team) : CPiece(Team)
{
}

CPawn::~CPawn()
{
}

EType CPawn::getType() const
{
    return Chess::Pawn;
}
