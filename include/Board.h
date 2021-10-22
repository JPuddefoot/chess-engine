#ifndef Board_H
#define Board_H

#include <vector>
#include <array>
#include <string>

#include <utils.h>
#include <Move.h>

#include <Piece.h>
#include <King.h>
#include <Queen.h>
#include <Pawns.h>
#include <Knight.h>
#include <Bishop.h>
#include <Rook.h>

// The board class

// Board_array - 8x8 array of position - each piece is represented by a enum
//   have a function that relates enum to relevant piece class

// nnumber of piece classes (blackKing, whiteKing etc)

// function - make move(from, to) - makes move and returns Move with additional info (captured piece etc)

// function - undo move(Move) - undos move by switching origin and destimation and replacing caputred piece

class Board {
    public:
        Board();
        bool whiteToMove;

        Move makeMove(Square origin, Square destination);
        Move undoMove();
        void generateMoves();


        std::string printBoard();

        std::vector<Piece*> boardArray =
            std::vector<Piece*>(64, nullptr);

        King whiteKing = King(Color::White);
        Queens whiteQueens = Queens(Color::White);
        Bishops whiteBishops = Bishops(Color::White);
        Knights whiteKnights = Knights(Color::White);
        Rooks whiteRooks = Rooks(Color::White);
        Pawns whitePawns = Pawns(Color::White);

        King blackKing = King(Color::Black);
        Queens blackQueens = Queens(Color::Black);
        Bishops blackBishops = Bishops(Color::Black);
        Knights blackKnights = Knights(Color::Black);
        Rooks blackRooks = Rooks(Color::Black);
        Pawns blackPawns = Pawns(Color::Black);

        std::vector<Piece*> capturedWhitePieces = {};
        std::vector<Piece*> capturedBlackPieces = {};

        std::vector<Move> moveHistory;

        std::vector<Move> nextMoveList;
        bitboard_t whitePieces;
        bitboard_t blackPieces;


};

#endif