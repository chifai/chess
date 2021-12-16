#if !defined(_PAWN_H__INCLUDED_)
#define _PAWN_H__INCLUDED_

#include "Piece.h"

class CPawn : public CPiece
{
public:
    // constructor
    CPawn(const ETeam Team);

    // destructor
    ~CPawn();

    // return the type of the piece
    EType getType() const override;

};
#endif // !defined(_PAWN_H__INCLUDED_)
