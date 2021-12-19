#include "GameBoard.h"
#include <cstring>

CGameBoard::CGameBoard() :
m_PlayerPiece({TPlayerPiece(White), TPlayerPiece(Black)})
{
    init();
}

CGameBoard::~CGameBoard()
{
}

void CGameBoard::init()
{
    // set all pieces to be alive, to original positions and update to m_pPiecePos map
    m_PlayerPiece[White].reset();
    m_PlayerPiece[Black].reset();

    updatePiecePos();
}

void CGameBoard::updatePiecePos()
{
    // reset to nullptr
    memset(m_pPiecePos, 0, sizeof(m_pPiecePos));

    // get every piece positions and assign to m_pPiecePos
    for (auto &Player : m_PlayerPiece) {
        for (auto &pPiece : Player.pPiece) {
            if (pPiece->isAlive() == true)
                m_pPiecePos[pPiece->getPos().x][pPiece->getPos().y] = pPiece;
        }
    }
}

void CGameBoard::move(const TPosition &From, const TPosition &To)
{
    
}

const CPiece* CGameBoard::operator[](const TPosition &Pos) const
{
    return m_pPiecePos[Pos.x][Pos.y];
}

TPlayerPiece::TPlayerPiece(const ETeam Team)
{
    this->Team = Team;

    // new pieces
    int nPieceCnt = 0;
    pPiece[nPieceCnt++] = pKing = new CKing(Team);
    pPiece[nPieceCnt++] = pQueen = new CQueen(Team);

    for (auto &ele : pBishop) pPiece[nPieceCnt++] = ele = new CBishop(Team);
    for (auto &ele : pKnight) pPiece[nPieceCnt++] = ele = new CKnight(Team);
    for (auto &ele : pRook) pPiece[nPieceCnt++] = ele = new CRook(Team);
    for (auto &ele : pPawn) pPiece[nPieceCnt++] = ele = new CPawn(Team);

    // reset to original position
    reset();
}

TPlayerPiece::~TPlayerPiece()
{
    for (auto &ele : pPiece) {
        delete ele;
    }
}

void TPlayerPiece::reset()
{
    int nPawnRow = Team == White ? 1 : 6;
    int nOtherPieceRow = Team == White ? 0 : 7;

    // set original position
    for (int i = 0; i < PAWN_NUM; i++) pPawn[i]->setPos({nPawnRow, i});
    pRook[0]->setPos({nOtherPieceRow, 0});
    pKnight[0]->setPos({nOtherPieceRow, 1});
    pBishop[0]->setPos({nOtherPieceRow, 2});
    pQueen->setPos({nOtherPieceRow, 3});
    pKing->setPos({nOtherPieceRow, 4});
    pBishop[1]->setPos({nOtherPieceRow, 5});
    pKnight[1]->setPos({nOtherPieceRow, 6});
    pRook[1]->setPos({nOtherPieceRow, 7});
}
