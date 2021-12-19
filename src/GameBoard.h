#if !defined(_GAMEBOARD_H__INCLUDED_)
#define _GAMEBOARD_H__INCLUDED_


#include "_Chess.h"

// this struct is to store one player's all pieces
struct TPlayerPiece{
    CKing *pKing;
    CQueen *pQueen;
    CBishop *pBishop[BISHOP_NUM];
    CKnight *pKnight[KNIGHT_NUM];
    CRook *pRook[ROOK_NUM];
    CPawn *pPawn[PAWN_NUM];
    CPiece *pPiece[PLAYER_PIECE_NUM];
    ETeam Team;

    // constructor
    TPlayerPiece(const ETeam Team);

    // destructor
    ~TPlayerPiece();

    // reset original positions
    void reset();
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

    // move piece from one to another
    void move(const TPosition &From, const TPosition &To);

    // get piece from the map by position
    const CPiece *operator[](const TPosition &Pos) const;

private:
    const CPiece *m_pPiecePos[BOARD_SIZE][BOARD_SIZE];

    TPlayerPiece m_PlayerPiece[ETeam::Num];
};
#endif // !defined(_GAMEBOARD_H__INCLUDED_)
