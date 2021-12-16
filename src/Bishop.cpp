#include "Bishop.h"

CBishop::CBishop(const ETeam Team) : CPiece(Team)
{
}

CBishop::~CBishop()
{
}

EType CBishop::getType() const
{
    return Bishop;
}
