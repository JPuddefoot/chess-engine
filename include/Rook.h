#ifndef Rook_H
#define Rook_H

#include <vector>

#include <Move.h>
#include <utils.h>
#include <RookLookup.h>

#include <Piece.h>

//////////
// Rook //
//////////

class Rooks: public Piece {
    public:
        Rooks(Color color);
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

        static constexpr const uint64_t *magicNums =
            RookLookup::rookMagicNumbers;
};




#endif