#if !defined(_KING_H__INCLUDED_)
#define _KING_H__INCLUDED_

#include "Piece.h"

class CKing : public CPiece
{
public:
    // constructor
    CKing(const ETeam Team);

    // destructor
    ~CKing();

    // return the type of the piece
    EType getType() const override;

    // check if valid move
    virtual bool isValidMove(const TPosition &From, const TPosition &To) const override;

};
#endif // !defined(_KING_H__INCLUDED_)
