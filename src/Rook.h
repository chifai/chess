#if !defined(_ROOK_H__INCLUDED_)
#define _ROOK_H__INCLUDED_

#include "Piece.h"

class CRook : public CPiece
{
public:
    // constructor
    CRook(const ETeam Team);

    // destructor
    virtual ~CRook();

    // return the type of the piece
    EType getType() const override;

};
#endif // !defined(_ROOK_H__INCLUDED_)
