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

    // check if valid move
    virtual bool isValidMove(const TPosition &From, const TPosition &To) const override;

private:
    // row number to move each time (white: 1, black: -1)
    int m_nRowToMoveEach;
};
#endif // !defined(_PAWN_H__INCLUDED_)
