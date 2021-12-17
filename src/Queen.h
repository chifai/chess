#if !defined(_QUEEN_H__INCLUDED_)
#define _QUEEN_H__INCLUDED_

#include "Piece.h"

class CQueen : public CPiece
{
public:
    // constructor
    CQueen(const ETeam Team);

    // destructor
    ~CQueen();

    // return the type of the piece
    EType getType() const override;

    // check if valid move
    virtual bool isValidMove(const TPosition &From, const TPosition &To) const override;

};
#endif // !defined(_QUEEN_H__INCLUDED_)
