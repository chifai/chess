#if !defined(_PIECE_H__INCLUDED_)
#define _PIECE_H__INCLUDED_

#include "ChessDef.h"

using namespace Chess;

class CPiece
{
public:
    // constructor
    CPiece(const ETeam Team);

    // return the team
    ETeam getTeam() const;

    // destructor
    virtual ~CPiece();

    // return the type of the piece
    virtual EType getType() const = 0;

private:
    // team
    ETeam m_Team;
};
#endif // !defined(_PIECE_H__INCLUDED_)
