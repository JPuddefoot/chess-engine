#include <stdint.h>

#include "WhitePawnSet.h"

void WhitePawnSet::InitBitboard() {
    this->bitboard = std::bitset<64>(std::string("000000001111111100000000000000000000000000000000000000000000000"));
};



