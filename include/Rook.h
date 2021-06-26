#ifndef ROOK_H
#define ROOK_H

#include <utils.h>
#include <Move.h>
#include <RookLookup.h>

#include <Piece.h>

//////////
// ROOK //
//////////

class Rooks: public Piece {
    public:
        Rooks(Color color);
        std::string name = "R";
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

};

#endif