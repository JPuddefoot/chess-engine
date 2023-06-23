#ifndef Bishop_H
#define Bishop_H

#include <vector>

#include <Move.h>
#include <utils.h>
#include <BishopLookup.h>

#include <Piece.h>

////////////
// Bishop //
////////////

class Bishops: public Piece {
    public:
        Bishops(Color color);
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

        static constexpr const uint64_t *magicNums =
            BishopLookup::bishopMagicNumbers;

};

#endif