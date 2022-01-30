#if !defined(_CHESSDEF_H__INCLUDED_)
#define _CHESSDEF_H__INCLUDED_

namespace Chess {
    const int PLAYER_PIECE_NUM = 16;
    const int PLAYER_NUM = 2;
    const int PIECE_NUM = 32;
    const int BOARD_SIZE = 8;
    const int SQUARE_NUM = BOARD_SIZE * BOARD_SIZE;
    const int PAWN_NUM = 8;
    const int KNIGHT_NUM = 2;
    const int BISHOP_NUM = 2;
    const int ROOK_NUM = 2;
    const int QUEEN_NUM = 1;
    const int KING_NUM = 1;
    const int WHITE_STARTROW = 0;
    const int BLACK_STARTROW = 7;

    struct TPosition {
        int x;
        int y;

        bool operator<(const TPosition &rhs) const
        {
            return (x * BOARD_SIZE + y < rhs.x * BOARD_SIZE + rhs.y);
        }

        TPosition& operator+=(const TPosition &rhs) 
        {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        TPosition operator+(const TPosition &rhs) const
        {
            return {x + rhs.x, y + rhs.y};
        }

        bool operator==(const TPosition &rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        bool inRange() const
        {
            return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
        }

        int to1D() const
        {
            return y * BOARD_SIZE + x;
        }
    };

    enum ETeam {
        None = -1,
        White = 0,
        Black = 1,
    };

    enum EType {
        Undef = -1,
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King,
    };

    enum EGameState {
        WhiteMove = 0,
        WhitePromote,
        WhiteCheckmate,
        BlackMove,
        BlackPromote,
        BlackCheckmate,
        DrawByStalemate,
        DrawByFiftyMoveRule,
    };

    struct TMoveLog {
        enum EMoveType {
            Normal,
            QueenCastle,
            KingCastle,
            Promotion,
        } MoveType;

        EType ChessType;
        EType PromoteType;
        TPosition ToPos;
        bool bCheck;
        bool bCapture;
        bool bCheckmate;
    };

    struct TPiece {
        bool bAlive;
        ETeam Team;
        TPosition Pos;
    };

    struct TSquareStatus {
        ETeam PieceTeam;
        EType PieceType;

        TSquareStatus() {
            PieceTeam = None;
            PieceType = Undef;
        }

        bool isOccupied() const
        {
            return PieceTeam != None;
        }
    };

    struct TProps {
        ETeam Team;
        EType Type;
        TPosition Pos;
    };
}

#endif // !defined(_CHESSDEF_H__INCLUDED_)
