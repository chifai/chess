#if !defined(_CHESSDEF_H__INCLUDED_)
#define _CHESSDEF_H__INCLUDED_

//#include "Pawn.h"

namespace Chess {
    const int PIECE_NUM = 32;
    const int BOARD_SIZE = 8;
    const int SQUARE_NUM = BOARD_SIZE * BOARD_SIZE;
    const int PAWN_NUM = 8;
    const int KNIGHT_NUM = 2;
    const int BISHOP_NUM = 2;
    const int ROOK_NUM = 2;
    const int QUEEN_NUM = 1;
    const int KING_NUM = 1;

    struct TPosition {
        int x;
        int y;
    };

    enum ETeam {
        White = 0,
        Black,
        Num,
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
        Ongoing = 0,
        WhiteCheck,
        BlackCheck,
        WhiteCheckmate,
        BlackCheckmate,
        Stalemate,
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


    struct TProps {
        ETeam Team;
        EType Type;
        TPosition Pos;
    };
}

#endif // !defined(_CHESSDEF_H__INCLUDED_)
