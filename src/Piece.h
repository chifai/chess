#if !defined(_PIECE_H__INCLUDED_)
#define _PIECE_H__INCLUDED_

#include "ChessDef.h"

using namespace Chess;

class CGameBoard;

class CPiece
{
public:
    // constructor
    CPiece(const ETeam Team);

    // return the team
    ETeam getTeam() const;

    // associate board square status
    static void setBoard(const CGameBoard *pGameBoard);

    // destructor
    virtual ~CPiece();

    // set position
    void setPos(const TPosition &Pos);

    // get position
    const TPosition &getPos() const;

    // set alive status
    void setAlive(const bool bAlive);

    // is alive
    bool isAlive() const;

    // return the type of the piece
    virtual EType getType() const = 0;

    // check if valid move
    virtual bool isValidMove(const TPosition &From, const TPosition &To) const = 0;

protected:
    // team
    ETeam m_Team;

    // alive status
    bool m_bAlive;

    // position, if alive==false, then save the last position
    TPosition m_Pos;

    // GameBoard object to hold all pieces info;
    static const CGameBoard *m_pGameBoard;
};
#endif // !defined(_PIECE_H__INCLUDED_)
