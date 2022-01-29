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
    };

    enum ETeam {
        None = 0,
        White,
        Black,
    };

    enum EType {
        Undef = 0,
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
    };

    struct TProps {
        ETeam Team;
        EType Type;
        TPosition Pos;
    };
}

#endif // !defined(_CHESSDEF_H__INCLUDED_)
