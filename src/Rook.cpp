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

bool CRook::isValidMove(const TPosition &From, const TPosition &To) const
{
    
    return false;
}
