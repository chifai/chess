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
    m_GameState = EGameState::WhiteMove;

    // reset piece positions
    m_GameBoard.resetPiece();

    // clear move log
    m_MoveLog.clear();
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
        m_GameState = m_GameState == EGameState::WhiteMove ? EGameState::WhitePromote : EGameState::BlackPromote;
        return true;
    }

    // check if checkmate
    if (isCheckmate(m_GameBoard[From].PieceTeam)) {
        m_GameState = m_GameState == EGameState::WhiteMove ? EGameState::WhiteCheckmate : EGameState::BlackCheckmate;
        return true;
    }

    // to next opponent move
    m_GameState = m_GameState == EGameState::WhiteMove ? EGameState::BlackMove : EGameState::WhiteMove;
    return true;
}

bool CChessGame::promote(const TPosition &From, const EType PromoteType) 
{
    const TSquareStatus *pBoard = m_GameBoard.getBoard();
    const int FromInd = From.to1D();

    // check type
    if (pBoard[FromInd].PieceType != EType::Pawn) return false;

    // check PromoteType
    if (PromoteType == EType::Pawn || PromoteType == EType::King) return false;

    // check gamestate
    if ((m_GameState == EGameState::WhitePromote && pBoard[FromInd].PieceTeam == ETeam::White && From.y == BLACK_STARTROW) ||
        (m_GameState == EGameState::BlackPromote && pBoard[FromInd].PieceTeam == ETeam::Black && From.y == WHITE_STARTROW)) {
        m_GameBoard.changeType(From, PromoteType);

        // change to move state
        m_GameState = m_GameState == EGameState::WhitePromote ? EGameState::BlackMove : EGameState::WhiteMove;
        return true;
    }

    return false;
}

bool CChessGame::isSafePieceMove(const TPosition &From, const TPosition &To) const
{
    return isValidPieceMove(From, To) && isKingSafeAfterMove(From, To);
}

int CChessGame::getAttackers(const TPosition &Prey, const ETeam AttackerTeam, TPosition Attacker[PIECE_NUM]) const
{
    return CChessRule::getAllAttackers(m_GameBoard.getBoard(), Prey, AttackerTeam, Attacker);
}

TSquareStatus CChessGame::getPiece(const TPosition &Pos) const
{
    return m_GameBoard[Pos];
}

EGameState CChessGame::getState() const
{
    return m_GameState;
}

bool CChessGame::isCheck() const
{
    return false;
}

bool CChessGame::isCheckmate(ETeam Team) const
{
    return false;
}

bool CChessGame::isValidPieceMove(const TPosition &From, const TPosition &To) const
{
    const TSquareStatus *pBoard = m_GameBoard.getBoard();
    return CChessRule::movePiece(pBoard, m_MoveLog, From, To);
}

void CChessGame::addMove(const TPosition &From, const TPosition &To)
{
    
}

bool CChessGame::isKingSafeAfterMove(const TPosition &From, const TPosition &To) const
{
    // get FromTeam
    ETeam FromTeam = m_GameBoard[From].PieceTeam;
    ETeam AttackerTeam = FromTeam == ETeam::White ? ETeam::Black : ETeam::White;

    // try move a piece
    TSquareStatus TryPiece[SQUARE_NUM];
    m_GameBoard.tryMovePiece(From, To, TryPiece);

    // get king position
    TPosition KingPos;
    if (TryPiece[To.to1D()].PieceType == EType::King) {
        // move king at this case
        KingPos = To;
    }
    else {
        // if king is not moved, get the king from GameBoard
        KingPos = m_GameBoard.getKing(FromTeam);
    }

    // return true if the king is not attacked
    return !CChessRule::isAttacked(TryPiece, KingPos, AttackerTeam);
}

bool CChessGame::isCorrectTeamToMove(const TPosition &From) const
{
    // check gamestate
    switch (m_GameBoard[From].PieceTeam) {
    case ETeam::None:
        return false;

    case ETeam::White:
        return m_GameState == EGameState::WhiteMove;

    case ETeam::Black:
        return m_GameState == EGameState::BlackMove;
    }

    assert(false);
    return false;
}

bool CChessGame::isPromotionRequired(const TPosition &Piece) const
{
    if (m_GameBoard[Piece].PieceType != EType::Pawn) return false;
    if (m_GameBoard[Piece].PieceTeam == ETeam::White && Piece.y == BLACK_STARTROW) return true;
    if (m_GameBoard[Piece].PieceTeam == ETeam::Black && Piece.y == WHITE_STARTROW) return true;

    return false;
}

bool CChessGame::isTrapped(const TPosition &Piece) const
{
    return false;
}
