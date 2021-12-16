#if !defined(_PIECE_H__INCLUDED_)
#define _PIECE_H__INCLUDED_

#include "ChessDef.h"

using namespace Chess;

class CPiece
{
public:
    // constructor
    CPiece();

    // destructor
    virtual ~CPiece();

    // init the piece with team and position
    void init(const ETeam Team, const TPosition &Pos);

    // return position
    const TPosition &getPosition() const;

    // return the type of the piece
    virtual EType getType() const = 0;

private:
    TPosition m_Position;

    ETeam m_Team;
};
#endif // !defined(_PIECE_H__INCLUDED_)
