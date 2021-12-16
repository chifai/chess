#if !defined(_KNIGHT_H__INCLUDED_)
#define _KNIGHT_H__INCLUDED_

#include "Piece.h"

class CKnight : public CPiece
{
public:
    // constructor
    CKnight(const ETeam Team);

    // destructor
    ~CKnight();

    // return the type of the piece
    EType getType() const override;

};
#endif // !defined(_KNIGHT_H__INCLUDED_)
