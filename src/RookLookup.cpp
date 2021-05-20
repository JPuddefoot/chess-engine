#include <RookLookup.h>
#include <iostream>


// For a given square, add a 1 to bitboard vertically/horizontally until
// reach the edge
bitboard_t generateRookBlockerMask(Square origin) {

    bitboard_t blockerMask = generateBitboard(std::vector<Square>{});

 //   std::cout << bitboard_to_string(blockerMask);

    std::size_t int_origin = static_cast<size_t>(origin);


    // get row start and end
    int row_start = int_origin/8 * 8; // int division to get multiple of 8
    int row_end = row_start + 7;

    // get column
    int col = int_origin - row_start;

    // fill whole row
    for (row_start; row_start<row_end-1; row_start++) {
        blockerMask.set(row_start+1);
    }

    // fill whole column
    for (int i=1; i<7; i++) {
        blockerMask.set(col+i*8);
    }

    // finally, flip the origin square bit back to 0
    blockerMask.flip(int_origin);

    std::cout << bitboard_to_string(blockerMask);

    return blockerMask;
}

std::vector<bitboard_t> generateBlockerBoards(bitboard_t blockerMask) {
    // To generate all possible blockerboards, need to get all possible
    // combinations of 1s and 0s from relevant squares. To do this,
    // can create bitsets for each number from 0 to 2^no.bits, and
    // use these to generate the bitboards by placing each bit on the relevant
    // square

    std::vector<bitboard_t> blockerBoards = {};

    // Create a vector of squares used in blocker, in order of index
    std::vector<Square> relevantSquares = {};
    for (size_t bit=0; bit<blockerMask.size(); bit++) {
        if (blockerMask.test(bit)) {
            relevantSquares.push_back(static_cast<Square>(bit));
        }
    }


    // loop through numbers from 0 to 2^bits, convert to binary and assign
    // each true bit to the relevant blocking square, then create the bitboard
    const int num_bits = blockerMask.count();
    for (size_t i=0; i<std::pow(2,num_bits); i++) {
        std::bitset<12> blockingBitset{i};  // 12 should be the maximum number of blocking pieces
        // go through bitset, for each turned on bit, add relevant square to vector

        std::vector<Square> blockingSquares = {};
        for (size_t j=0; j<num_bits; j++) {
            if (blockingBitset.test(j)) {
                blockingSquares.push_back(relevantSquares.at(j));
            }
        }
        std::cout << bitboard_to_string(generateBitboard(blockingSquares));
        blockerBoards.push_back(generateBitboard(blockingSquares));

    }

    return blockerBoards;

}