#include "King.h"

CKing::CKing(const ETeam Team) : CPiece(Team)
{
}

CKing::~CKing()
{
}

EType CKing::getType() const
{
    return King;
}
