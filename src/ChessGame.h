#if !defined(_CHESSGAME_H__INCLUDED_)
#define _CHESSGAME_H__INCLUDED_

#include "_Chess.h"
#include "GameBoard.h"

#include <vector>
#include <map>

typedef std::map <TPosition, const CPiece *> TPieceMap;

class CChessGame
{
public:
    // constructor
    CChessGame();

    // destructor
    ~CChessGame();

    // initialize a new game
    void init();

    // check if it is a valid move
    bool isValidMove(const TPosition &From, const TPosition &To) const;

    // show all valid move on particular piece, return the numbers
    int showAllValidMoves(const TPosition &From, TPosition AllValidDest[]) const;

    // move a piece
    bool move(const TPosition &From, const TPosition &To);

    // move a pawn to the end and promote to a piece
    bool promote(const TPosition &From, const EType PromoteType);

    // get the piece of particular position
    const CPiece *getPiece(const TPosition &Pos) const;

    // is check?
    bool isCheck() const;

    // is checkmate?
    bool isCheckmate() const;

private:
    // current game state
    EGameState m_GameState;

    // every move log
    std::vector <TMoveLog> m_MoveLog;

    // CGameBoard object to manipulate piece position and status
    CGameBoard m_GameBoard;

};
#endif // !defined(_CHESSGAME_H__INCLUDED_)
