#include "GameBoard.h"
#include <cassert>
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
    // assign ETeam::White pieces, set the start index
    int Index = 0;

    // assign team
    for (int j = 0; j < PLAYER_PIECE_NUM; j++) {
        m_Square[Index + j].PieceTeam = ETeam::White;
    }

    // assign pieces besides pawns
    m_Square[Index++].PieceType = EType::Rook;
    m_Square[Index++].PieceType = EType::Knight;
    m_Square[Index++].PieceType = EType::Bishop;
    m_Square[Index++].PieceType = EType::Queen;
    m_Square[Index++].PieceType = EType::King;
    m_Square[Index++].PieceType = EType::Bishop;
    m_Square[Index++].PieceType = EType::Knight;
    m_Square[Index++].PieceType = EType::Rook;

    // assign pawns
    for (int j = 0; j < PAWN_NUM; j++) {
        m_Square[Index++].PieceType = EType::Pawn;
    }

    // assign black pieces, reset the starting index
    Index = BOARD_SIZE * 6;

    // assign team
    for (int j = 0; j < PLAYER_PIECE_NUM; j++) {
        m_Square[Index + j].PieceTeam = ETeam::Black;
    }

    // assign pawns
    for (int j = 0; j < PAWN_NUM; j++) {
        m_Square[Index++].PieceType = EType::Pawn;
    }

    // assign pieces besides pawns
    m_Square[Index++].PieceType = EType::Rook;
    m_Square[Index++].PieceType = EType::Knight;
    m_Square[Index++].PieceType = EType::Bishop;
    m_Square[Index++].PieceType = EType::Queen;
    m_Square[Index++].PieceType = EType::King;
    m_Square[Index++].PieceType = EType::Bishop;
    m_Square[Index++].PieceType = EType::Knight;
    m_Square[Index++].PieceType = EType::Rook;

    // reset king position
    m_KingPos[(int)ETeam::White] = {0, 4};
    m_KingPos[(int)ETeam::Black] = {7, 4};
}

void CGameBoard::movePiece(const TPosition &From, const TPosition &To)
{
    int FromInd = From.to1D();
    int ToInd = To.to1D();
    m_Square[ToInd] = m_Square[FromInd];
    m_Square[FromInd] = {};

    // record the king position if it moves
    if (m_Square[ToInd].PieceType == EType::King) {
        m_KingPos[(int)m_Square[ToInd].PieceTeam] = To;
    }
}

void CGameBoard::tryMovePiece(const TPosition &From, const TPosition &To, TSquareStatus Piece[]) const
{
    memcpy(Piece, m_Square, sizeof(m_Square));
    Piece[To.to1D()] = m_Square[From.to1D()];
    Piece[From.to1D()] = {};
}

void CGameBoard::changeType(const TPosition &Piece, const EType Type)
{
    if (m_Square[Piece.to1D()].PieceType != EType::Undef) {
        m_Square[Piece.to1D()].PieceType = Type;
    }
}

const TSquareStatus *CGameBoard::getBoard() const
{
    return m_Square;
}

TPosition CGameBoard::getKing(ETeam Team) const
{
    if (Team == ETeam::None) {
        assert(false);
        return {-1, -1};
    }
    return m_KingPos[(int)Team];
}

void CGameBoard::updateKingPos() 
{
    int KingNum = 0;
    for (int i = 0; i < SQUARE_NUM; i++) {
        if (m_Square[i].PieceType == EType::King) {
            m_KingPos[(int)m_Square[i].PieceTeam] = {i % BOARD_SIZE, i / BOARD_SIZE};
            KingNum++;
        }

        if (KingNum == PLAYER_NUM) return;
    }

    assert(KingNum != 2);
}

TSquareStatus CGameBoard::operator[](const TPosition &Pos) const
{
    return m_Square[Pos.to1D()];
}
