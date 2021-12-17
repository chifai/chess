#include "Knight.h"

CKnight::CKnight(const ETeam Team) : CPiece(Team)
{
}

CKnight::~CKnight()
{
}

EType CKnight::getType() const
{
    return Knight;
}

bool CKnight::isValidMove(const TPosition &From, const TPosition &To) const
{
    
    return false;
}
