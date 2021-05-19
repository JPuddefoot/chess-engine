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

    return generateBitboard(std::vector<Square>{Square::E1});
}