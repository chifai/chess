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
    for(int i = 0; i < PIECE_NUM; i++) {
        delete m_pPieces[i];
    }
}

void CChessGame::init()
{
    // reset the state as ongoing
    m_GameState = Ongoing;

    // create player pieces
    memset(m_pPieces, 0, sizeof(m_pPieces));
    createPieces(White, m_pPieces);
    createPieces(Black, m_pPieces + PLAYER_PIECE_NUM);

    // reposition both players' pieces to original positions
    memset(m_pSquare, 0, sizeof(m_pSquare));
    resetPlayerPiece(White, m_pPieces);
    resetPlayerPiece(Black, m_pPieces + PLAYER_PIECE_NUM);

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

void CChessGame::createPieces(const ETeam Team, const CPiece **pStartPiece)
{
    int nPieceNum = 0;

    // create 8 pawns
    for (int i = 0; i < PAWN_NUM; i++ ) {
        pStartPiece[nPieceNum++] = new CPawn(Team);
    }

    // create in order of Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook
    pStartPiece[nPieceNum++] = new CRook(Team);
    pStartPiece[nPieceNum++] = new CKnight(Team);
    pStartPiece[nPieceNum++] = new CBishop(Team);
    pStartPiece[nPieceNum++] = new CQueen(Team);
    pStartPiece[nPieceNum++] = new CKing(Team);
    pStartPiece[nPieceNum++] = new CBishop(Team);
    pStartPiece[nPieceNum++] = new CKnight(Team);
    pStartPiece[nPieceNum++] = new CRook(Team);
}

void CChessGame::resetPlayerPiece(const ETeam Team, const CPiece **m_pPieces)
{
    int PawnRow;
    int OtherPieceRow;

    // assign the row number
    if (Team == White) {
        OtherPieceRow = 0;
        PawnRow = 1;
    }
    else if (Team == Black) {
        OtherPieceRow = 7;
        PawnRow = 6;
    }
    else {
        assert( false );
    }

    int nPieceCount = 0;
    // first 8 pawns
    for (int i = 0; i < PAWN_NUM; i++) {
        m_pSquare[PawnRow][i] = m_pPieces[i];
        nPieceCount++;
    }

    // in order of Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook
    m_pSquare[OtherPieceRow][0] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][1] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][2] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][3] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][4] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][5] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][6] = m_pPieces[nPieceCount++];
    m_pSquare[OtherPieceRow][7] = m_pPieces[nPieceCount++];
}

void CChessGame::updatePieceLocation() 
{
}
