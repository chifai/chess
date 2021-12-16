#if !defined(_KING_H__INCLUDED_)
#define _KING_H__INCLUDED_

#include "Piece.h"

class CKing : public CPiece
{
public:
    // constructor
    CKing();

    // destructor
    ~CKing();

    // return the type of the piece
    EType getType() const override;

};
#endif // !defined(_KING_H__INCLUDED_)
