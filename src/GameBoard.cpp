#include "GameBoard.h"
#include <cstring>

CGameBoard::CGameBoard()
{
    init();
}

CGameBoard::~CGameBoard()
{
}

void CGameBoard::init()
{
    // set all pieces to be alive, to original positions
    resetPiece();

    // update piece position as regard as team
    updatePiecePos();
}

void CGameBoard::updatePiecePos()
{
    // #TODO: check every square status and assign to team's info
    for (auto &Square : m_Square) {
    }
}

void CGameBoard::resetPiece()
{
    // reset
    memset(m_Square, 0, sizeof(m_Square));

    // assign White pieces, set the start index
    int Index = 0;

    // assign team
    for (int j = 0; j < PLAYER_PIECE_NUM; j++) {
        m_Square[Index + j].PieceTeam = White;
    }

    // assign pieces besides pawns
    m_Square[Index++].PieceType = Rook;
    m_Square[Index++].PieceType = Knight;
    m_Square[Index++].PieceType = Bishop;
    m_Square[Index++].PieceType = Queen;
    m_Square[Index++].PieceType = King;
    m_Square[Index++].PieceType = Bishop;
    m_Square[Index++].PieceType = Knight;
    m_Square[Index++].PieceType = Rook;

    // assign pawns
    for (int j = 0; j < PAWN_NUM; j++) {
        m_Square[Index++].PieceType = Pawn;
    }

    // assign black pieces, reset the starting index
    Index = BOARD_SIZE * 6;

    // assign team
    for (int j = 0; j < PLAYER_PIECE_NUM; j++) {
        m_Square[Index + j].PieceTeam = Black;
    }

    // assign pawns
    for (int j = 0; j < PAWN_NUM; j++) {
        m_Square[Index++].PieceType = Pawn;
    }

    // assign pieces besides pawns
    m_Square[Index++].PieceType = Rook;
    m_Square[Index++].PieceType = Knight;
    m_Square[Index++].PieceType = Bishop;
    m_Square[Index++].PieceType = Queen;
    m_Square[Index++].PieceType = King;
    m_Square[Index++].PieceType = Bishop;
    m_Square[Index++].PieceType = Knight;
    m_Square[Index++].PieceType = Rook;
}

void CGameBoard::movePiece(const TPosition &From, const TPosition &To)
{
    m_Square[To.y * BOARD_SIZE + To.x] = m_Square[From.y * BOARD_SIZE + From.x];
    m_Square[From.y * BOARD_SIZE + From.x] = {};
}

void CGameBoard::tryMovePiece(const TPosition &From, const TPosition &To, TSquareStatus Piece[]) const
{
    
}

void CGameBoard::promotePawn(const TPosition &PawnPosition, const EType PromoteType)
{
}

const TSquareStatus *CGameBoard::getBoard() const
{
    return m_Square;
}

TPosition CGameBoard::getKing(ETeam Team) const
{
    return {0, 0};
}

TSquareStatus CGameBoard::operator[](const TPosition &Pos) const
{
    return m_Square[Pos.y * BOARD_SIZE + Pos.x];
}

