#if !defined(_CHESSGAME_H__INCLUDED_)
#define _CHESSGAME_H__INCLUDED_

#include "_Chess.h"

#include <vector>
#include <map>

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
    int showAllValidMoves(const TPosition &From, TPosition AllValidDest[] ) const;

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
    // reset particular player pieces
    void repositionPlayerPiece(const ETeam Team);

    // update all pieces location to m_pSquare
    void updatePieceLocation();

    struct TPlayer {
        CPawn Pawn[PAWN_NUM];
        CKnight Knight[KNIGHT_NUM];
        CBishop Bishop[BISHOP_NUM];
        CRook Rook[ROOK_NUM];
        CQueen Queen;
        CKing King;
    };

    // 64 squares to hold pieces
    const CPiece *m_pSquare[BOARD_SIZE][BOARD_SIZE];

    // current game state
    EGameState m_GameState;

    // player white
    TPlayer m_PlayerWhite;

    // player black
    TPlayer m_PlayerBlack;

    // pieces array
    CPiece *m_pPieces;

    // every move log
    std::vector <TMoveLog> m_MoveLog;

    // position to piece map
    std::map <TPosition, CPiece*> m_PieceMap;
};
#endif // !defined(_CHESSGAME_H__INCLUDED_)
