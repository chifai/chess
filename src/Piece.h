#if !defined(_PIECE_H__INCLUDED_)
#define _PIECE_H__INCLUDED_

#include "ChessDef.h"
#include <map>

using namespace Chess;

class CPiece
{
public:
    // constructor
    CPiece(const ETeam Team);

    // return the team
    ETeam getTeam() const;

    // associate board square status
    static void setBoard(std::map <TPosition, const CPiece *> *pPieceMap);

    // destructor
    virtual ~CPiece();

    // return the type of the piece
    virtual EType getType() const = 0;

    // check if valid move
    virtual bool isValidMove(const TPosition &From, const TPosition &To) const = 0;

protected:
    // team
    ETeam m_Team;

    // 64 position to hold pieces;
    static std::map <TPosition, const CPiece *> *m_pPieceMap;
};
#endif // !defined(_PIECE_H__INCLUDED_)
