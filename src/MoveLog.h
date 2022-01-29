#if !defined(_MOVELOG_H__INCLUDED_)
#define _MOVELOG_H__INCLUDED_

#include "ChessDef.h"
#include <vector>

using namespace Chess;

class CMoveLog
{
public:
    // constructor
    CMoveLog();

    // destructor
    ~CMoveLog();

    // clear log
    void clear();

private:
    // continuous move number of no pawn moves or capture
    int nContNoPawnMoveOrCaptureMoveNum;

    // true if king has been moved
    bool bKingMoved[PLAYER_NUM];

    // true if short Rook has been moved
    bool bQueenRookMoved[PLAYER_NUM];

    // true if long Rook has been moved
    bool bKingRookMoved[PLAYER_NUM];

    // log record
    std::vector<TMoveLog> m_LogRecord;
};
#endif // !defined(_MOVELOG_H__INCLUDED_)
