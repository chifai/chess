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

    // reset move state: white to move
    m_MoveState = WhiteMove;

    CPiece::setBoard(&m_PieceMap);

    // set piece map to null
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            TPosition Pos = {i, j};
            m_PieceMap.emplace(Pos, nullptr);
        }
    }

    // create player pieces
    memset(m_pPieces, 0, sizeof(m_pPieces));
    createPieces(White, m_pPieces);
    createPieces(Black, m_pPieces + PLAYER_PIECE_NUM);

    // reposition both players' pieces to original positions
    resetPlayerPiece(White, m_pPieces);
    resetPlayerPiece(Black, m_pPieces + PLAYER_PIECE_NUM);

    // clear move log
    m_MoveLog.clear();

}

bool CChessGame::isValidMove(const TPosition &From, const TPosition &To) const
{
    const CPiece *pFromPiece = m_PieceMap.at(From);

    // piece exists
    if (pFromPiece == nullptr) return false;

    // check piece team matches with move state
    const ETeam FromTeam = pFromPiece->getTeam();
    if ((FromTeam == White) && (m_MoveState != WhiteMove)) return false;
    if ((FromTeam == Black) && (m_MoveState != BlackMove)) return false;

    // call piece function to check if valid
    return pFromPiece->isValidMove(From, To);
}

bool CChessGame::move(const TPosition &From, const TPosition &To)
{
    return false;
}

const CPiece *CChessGame::getPiece(const TPosition &Pos) const
{
    return m_GameBoard[Pos];
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
        TPosition Pos = {PawnRow, i};
        m_PieceMap[Pos] = m_pPieces[nPieceCount++];
    }

    // for rest of the pieces
    // in order of Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook
    for (int i = 0; i < 8; i++) {
        TPosition Pos = {OtherPieceRow, i};
        m_PieceMap[Pos] = m_pPieces[nPieceCount++];
    }
}

void CChessGame::updatePieceLocation() 
{
}
