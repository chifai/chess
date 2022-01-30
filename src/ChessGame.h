#if !defined(_CHESSGAME_H__INCLUDED_)
#define _CHESSGAME_H__INCLUDED_

#include "ChessDef.h"
#include "ChessRule.h"
#include "GameBoard.h"
#include "MoveLog.h"

class CChessGame
{
public:
    // constructor
    CChessGame();

    // destructor
    ~CChessGame();

    // initialize a new game
    void init();

    // move one piece
    bool moveOnePiece(const TPosition &From, const TPosition &To);

    // move a pawn to the end and promote to a piece
    bool promote(const TPosition &From, const EType PromoteType);

    // check if it is a valid piece move and the king is safe
    bool isSafePieceMove(const TPosition &From, const TPosition &To) const;

    // check if a piece is being attacked and show all of the attacking positions
    int getAttackers(const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM]) const;

    // show all valid move on particular piece, return the numbers
    int showAllValidMoves(const TPosition &From, TPosition ValidDest[]) const;

    // get the piece of particular position
    TSquareStatus getPiece(const TPosition &Pos) const;

    // is check?
    bool isCheck() const;

    // is checkmate?
    bool isCheckmate(ETeam Team) const;

private:
    // check if it is a valid move
    bool isValidPieceMove(const TPosition &From, const TPosition &To) const;

    // add a move to log
    void addMove(const TPosition &From, const TPosition &To);

    // try a move to see if king will be attacked
    bool isKingSafeAfterMove(const TPosition &From, const TPosition &To) const;

    // check if the piece trying to move is from correct team
    bool isCorrectTeamToMove(const TPosition &From) const;

    // check if promotion required
    bool isPromotionRequired(const TPosition &Piece) const;

    // check if a piece is trapped with no valid moves
    bool isTrapped(const TPosition &Piece) const;

    // current game state
    EGameState m_GameState;

    // game board
    CGameBoard m_GameBoard;

    // record move log
    CMoveLog m_MoveLog;
};
#endif // !defined(_CHESSGAME_H__INCLUDED_)
