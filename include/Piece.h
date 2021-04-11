#ifndef Piece_H
#define Piece_H


#include <vector>
#include <string>

#include <utils.h>
#include <Move.h>
// Abstract class for all piece types

// Provides virtual method for generateMoves, and defines shared functions such
// capture_piece and data members initialPos/currentPos

class Piece {
    public:

        Color color;
        bitboard_t initialPos;
        bitboard_t currentPos;

        std::string name;

        virtual void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList) = 0;

        void makeMove(const Square & origin, const Square & destination);

        void capturePiece(const Square & capture_square);

        void addPiece(const Square & destination);


};

#endif