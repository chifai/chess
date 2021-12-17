#if !defined(_CHESSGAME_H__INCLUDED_)
#define _CHESSGAME_H__INCLUDED_

#include "_Chess.h"

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
    // create 16 pieces of a team
    void createPieces(const ETeam Team, const CPiece **pStartPiece);

    // reset particular player pieces
    void resetPlayerPiece(const ETeam Team, const CPiece **m_pPieces);

    // update all pieces location to m_pPiecePos
    void updatePieceLocation();

    // current game state
    EGameState m_GameState;

    // pieces array
    const CPiece *m_pPieces[PIECE_NUM];

    // every move log
    std::vector <TMoveLog> m_MoveLog;

    // TPosition to CPiece* map
    TPieceMap m_PieceMap;

};
#endif // !defined(_CHESSGAME_H__INCLUDED_)
