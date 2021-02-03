#include <stdint.h>
#include <iostream>
#include "WhitePawnSet.h"

void WhitePawnSet::initBitboard() {
    this->bitboard = bitboard_t(std::string("0000000011111111000000000000000000000000000000000000000000000000"));
};

// Push White pawns by one, intersect with full pieces bitboard and produce list of possible moves
void WhitePawnSet::pushPawns(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {
    bitboard_t shifted_bitboard = this->bitboard >> 8;
    shifted_bitboard = (shifted_bitboard & black_pieces) ^ shifted_bitboard;
    std::cout << bitboard_to_string(shifted_bitboard);
};

