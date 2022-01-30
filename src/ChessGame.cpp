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
    // reset the state as white move
    m_GameState = WhiteMove;

    // reset piece positions
    m_GameBoard.resetPiece();

    // clear move log
    m_MoveLog.clear();
}

bool CChessGame::isValidPieceMove(const TPosition &From, const TPosition &To) const
{
    const TSquareStatus *pBoard = m_GameBoard.getBoard();
    return CChessRule::movePiece(pBoard, m_MoveLog, From, To);
}

bool CChessGame::moveOnePiece(const TPosition &From, const TPosition &To)
{
    // check if correct team to move under current game state
    if (isCorrectTeamToMove(From) == false) return false;

    // check if piece move is valid and the king is safe
    if (isSafePieceMove(From, To) == false) return false;

    // the move is valid, move the piece
    m_GameBoard.movePiece(From, To);

    // update log
    addMove(From, To);

    // check if promotion required
    if (isPromotionRequired(To)) {
        m_GameState = m_GameState == WhiteMove ? WhitePromote : BlackPromote;
        return true;
    }

    // check if checkmate
    if (isCheckmate(m_GameBoard[From].PieceTeam)) {
        m_GameState = m_GameState == WhiteMove ? WhiteCheckmate : BlackCheckmate;
        return true;
    }

    // to next opponent move
    m_GameState = m_GameState == WhiteMove ? BlackMove : WhiteMove;
    return true;
}

bool CChessGame::isSafePieceMove(const TPosition &From, const TPosition &To) const
{
    return isValidPieceMove(From, To) && isKingAttackedAfterMove(From, To);
}

int CChessGame::getAttackers(const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM]) const
{
    return CChessRule::getAllAttackers(m_GameBoard.getBoard(), Prey, AttackerTeam, Attacker);
}

TSquareStatus CChessGame::getPiece(const TPosition &Pos) const
{
    return m_GameBoard[Pos];
}

bool CChessGame::isCheckmate(ETeam Team) const
{
    return false;
}

void CChessGame::addMove(const TPosition &From, const TPosition &To)
{
    
}

bool CChessGame::isKingAttackedAfterMove(const TPosition &From, const TPosition &To) const
{
    // get FromTeam
    ETeam FromTeam = m_GameBoard[From].PieceTeam;

    // try move a piece
    TSquareStatus TryPiece[SQUARE_NUM];
    m_GameBoard.tryMovePiece(From, To, TryPiece);

    // get king position
    TPosition KingPos = m_GameBoard.getKing(FromTeam);

    // return true if the king is not attacked
    return !CChessRule::isAttacked(TryPiece, KingPos, FromTeam == White ? Black : White);
}

bool CChessGame::isCorrectTeamToMove(const TPosition &From) const
{
    // check gamestate
    switch (m_GameBoard[From].PieceTeam) {
    case None:
        return false;

    case White:
        return m_GameState == WhiteMove;

    case Black:
        return m_GameState == BlackMove;
    }

    assert(false);
    return false;
}

bool CChessGame::isPromotionRequired(const TPosition &Piece) const
{
    if (m_GameBoard[Piece].PieceType != Pawn) return false;
    if (m_GameBoard[Piece].PieceTeam == White && Piece.x == BLACK_STARTROW) return true;
    if (m_GameBoard[Piece].PieceTeam == Black && Piece.x == WHITE_STARTROW) return true;

    return false;
}

bool CChessGame::isTrapped(const TPosition &Piece) const
{
    return false;
}
