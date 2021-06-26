#ifndef RookLookup_H
#define RookLookup_H

// Generates the attack set for a horizontally/vertically moving piece
// using magic bitboard:

// Magic Bitboards

// For each square:
//  generate the blocker mask (all squares that could block piece)
//  generate all possible combos of blocking boards
//  For each blocking board:
//      Generate the move board
//      using random 64bit numbers, try (blockerboard*number) >> (64-numbits)
//      if two different blocker boards have same index, try a new number
//      Finally, store move board at that index

#include <cmath>
#include <random>
#include <unordered_map>

#include <utils.h>
#include <Move.h>

class RookLookup {
    public:

        // Lookup table of Rook moves - Each square has a map of a hash and a moveboard
        static std::vector<std::unordered_map<uint64_t, uint64_t>>moveSets;

        // Lookup table of Rook Magic Numbers
        static const std::vector<uint64_t>rookMagicNumbers;

        // Generate the mapping and magic number for a given square
        static uint64_t generateRookMoveSetforSquare(Square const & origin);

        // Generate the blocker mask for a given square
        static bitboard_t generateRookBlockerMask(Square const & origin);

        // Generate all combinations of blocker boards for a given blocker mask
        static std::vector<bitboard_t> generateBlockerBoards(
            bitboard_t const & blockerMask);

        // For a given blocker board, generate the move board
        static bitboard_t generateRookMoveBoard(bitboard_t const & blockerBoard,
            Square const & origin);


};


#endif