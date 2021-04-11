#ifndef King_H
#define King_H

#include <vector>

#include <utils.h>
#include <Move.h>
#include <KingLookup.h>

#include <Piece.h>

//////////
// King //
//////////

// Create King of specified color
// Have a lookup table with all possible moves from each square

// Need way to test for checks, castling etc

class King: public Piece {
    public:
        King(Color color);
        std::string name = "K";
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

    private:
        static constexpr const std::vector<bitboard_t>* KingLookup =
            &KingLookupTable;
};

#endif
