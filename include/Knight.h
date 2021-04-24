#ifndef Knight_H
#define Knight_H

#include <vector>

#include <utils.h>
#include <Move.h>
#include <KnightLookup.h>

#include <Piece.h>

////////////
// KNIGHT //
////////////

/// Create all knights of the specified colour
/// Have a lookup table that gives posible moves from each square
//  Go through board and look for knights, for each one lookup from position
//  and remove squares with friendly piece on

// Way to add individual knight (for promotions)

class Knights: public Piece {
    public:
        Knights(Color color);
        std::string name = "N";
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

    private:
        static constexpr const std::vector<bitboard_t>* KnightLookup =
            &KnightLookupTable;

};

#endif
