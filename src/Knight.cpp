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
