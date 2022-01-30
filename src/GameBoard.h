#if !defined(_GAMEBOARD_H__INCLUDED_)
#define _GAMEBOARD_H__INCLUDED_

// describe the piece positions on a game board

#include "ChessDef.h"
using namespace Chess;

// this struct is to store one player's all pieces
struct TPlayerPiece{
    ETeam Team;
    TPosition King;
    TPosition Queen;
    TPosition Bishop[BISHOP_NUM];
    TPosition Knight[KNIGHT_NUM];
    TPosition Rook[ROOK_NUM];
    TPosition Pawn[PAWN_NUM];
};

// this class is to
// 1. create pieces for players
// 2. manipulate players piece position, live-or-dead status
class CGameBoard
{
public:
    // constructor to create two teams of player pieces
    CGameBoard();

    // destructor
    ~CGameBoard();

    // reset a game board with initial piece position
    void init();

    // update position to m_pPiecePos
    void updatePiecePos();

    // reset piece to be all alive and to original positions
    void resetPiece();

    // move one piece to another position, and update players' status
    // do nothing if no piece is found at departing position
    void movePiece(const TPosition &From, const TPosition &To);

    // try to move a piece and output the positions
    void tryMovePiece(const TPosition &From, const TPosition &To, TSquareStatus Piece[]) const;

    // promote a pawn and update players' status
    // do nothing if no the pawn is not at the end of board or no pawn is found at departing position
    void changeType(const TPosition &Piece, const EType Type);

    // get board
    const TSquareStatus* getBoard() const;

    // get piece from the map by position
    TSquareStatus operator[](const TPosition &Pos) const;

    // get the king
    TPosition getKing(ETeam Team) const;

private:
    // update king pos
    void updateKingPos();

    // all squares status
    TSquareStatus m_Square[SQUARE_NUM];

    // player pieces
    TPlayerPiece m_PlayerPiece[PLAYER_NUM];

    // king position
    TPosition m_KingPos[PLAYER_NUM];
};
#endif // !defined(_GAMEBOARD_H__INCLUDED_)
