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

bool CKing::isValidMove(const TPosition &From, const TPosition &To) const
{
    return false;
}
