#ifndef Knight_H
#define Knight_H

#include <vector>

#include <utils.h>
#include <Move.h>

//////////
// KNIGHT
/////////

/// Create a knight of the specified colour
/// Have a lookup table that gives posible moves from each square
//  Go through board and look for knights, for each one lookup from position
//  and remove squares with friendly piece on


class Knights {
    public:
        Knights(Color color);
        Color color;
        bitboard_t initialPos;
        bitboard_t currentPos;
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
    private:
        std::vector<bitboard_t> lookupTable;
};




#endif

