#if !defined(_BISHOP_H__INCLUDED_)
#define _BISHOP_H__INCLUDED_

#include "Piece.h"

class CBishop : public CPiece
{
public:
    // constructor
    CBishop(const ETeam Team);

    // destructor
    ~CBishop();

    // return the type of the piece
    EType getType() const override;

};
#endif // !defined(_BISHOP_H__INCLUDED_)
