#include "ChessGame.h"
#include <stdlib.h>
#include <cstring>
#include <cassert>

CChessGame::CChessGame()
{
    // init a new game
    init();
}

CChessGame::~CChessGame()
{
}

void CChessGame::init()
{
    // init as nullptr array
    memset(m_pSquare, 0, sizeof(m_pSquare));

    // reset the state as ongoing
    m_GameState = Ongoing;

    repositionPlayerPiece(White);
    repositionPlayerPiece(Black);

    m_MoveLog.clear();
}

bool CChessGame::isValidMove(const TPosition &From, const TPosition &To) const
{
    // get piece object

    // check if valid
    return false;
}

bool CChessGame::move(const TPosition &From, const TPosition &To)
{
    return false;
}

const CPiece *CChessGame::getPiece(const TPosition &Pos) const
{
    return m_pSquare[Pos.x][Pos.y];
}

void CChessGame::repositionPlayerPiece(const ETeam Team)
{
    int PawnRow;
    int OtherPieceRow;
    const TPlayer *pPlayer = nullptr;

    // assign the row number
    if (Team == White) {
        OtherPieceRow = 0;
        PawnRow = 1;
        pPlayer = &m_PlayerWhite;
    }
    else if (Team == Black) {
        OtherPieceRow = 7;
        PawnRow = 6;
        pPlayer = &m_PlayerBlack;
    }
    else {
        assert( false );
    }

    // reset white pieces
    m_pSquare[OtherPieceRow][0] = &pPlayer->Rook[0];
    m_pSquare[OtherPieceRow][1] = &pPlayer->Knight[0];
    m_pSquare[OtherPieceRow][2] = &pPlayer->Bishop[0];
    m_pSquare[OtherPieceRow][3] = &pPlayer->Queen;
    m_pSquare[OtherPieceRow][4] = &pPlayer->King;
    m_pSquare[OtherPieceRow][5] = &pPlayer->Bishop[1];
    m_pSquare[OtherPieceRow][6] = &pPlayer->Knight[1];
    m_pSquare[OtherPieceRow][7] = &pPlayer->Rook[1];

    for (int i = 0; i < PAWN_NUM; i++) {
        m_pSquare[PawnRow][i] = &pPlayer->Pawn[i];
    }
}

void CChessGame::updatePieceLocation() 
{
}
