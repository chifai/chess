#include "Rook.h"

CRook::CRook(const ETeam Team) : CPiece(Team)
{
}

CRook::~CRook()
{
}

EType CRook::getType() const
{
    return Rook;
}
