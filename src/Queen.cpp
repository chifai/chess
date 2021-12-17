#include "Queen.h"

CQueen::CQueen(const ETeam Team) : CPiece(Team)
{
}

CQueen::~CQueen()
{
}

EType CQueen::getType() const
{
    return Queen;
}

bool CQueen::isValidMove(const TPosition &From, const TPosition &To) const
{
    return false;
}
