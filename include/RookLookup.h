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

#include <utils.h>
#include <Move.h>

// Generate the blocker mask for a given square
bitboard_t generateRookBlockerMask(Square origin);

// For a given blocker board, generate all possible blocker boards