#ifndef Board_H
#define Board_H

#include <vector>
#include <array>

#include <utils.h>
#include <Move.h>

#include <King.h>
#include <Pawns.h>
#include <Knight.h>

// The board class

// Board_array - 8x8 array of position - each piece is represented by a enum
//   have a function that relates enum to relevant piece class

// nnumber of piece classes (blackKing, whiteKing etc)

// function - make move(from, to) - makes move and returns Move with additional info (captured piece etc)

// function - undo move(Move) - undos move by switching origin and destimation and replacing caputred piece

class Board {
    public:
        Color sideToMove;

        Move makeMove(Square origin, Square destination);
        void undoMove(Move move);

    private:
        std::vector<PieceType> board_array = std::vector<PieceType>(64, PieceType::none);

        King whiteKing = King(Color::White);
        Pawns whitePawns = Pawns(Color::White);
        Knights whiteKnights = Knights(Color::White);

        King blackKing = King(Color::Black);
        Pawns blackPawns = Pawns(Color::Black);
        Knights blackKnights = Knights(Color::Black);
};

#endif