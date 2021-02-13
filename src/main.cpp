#include <iostream>

#include "WhitePawnSet.h"
#include "utils.h"


int main() {

    bitboard_t white_pieces = bitboard_t(std::string("1111111111111111000000000000000000000000000000000000000000000000"));
    bitboard_t black_pieces = bitboard_t(std::string("0000000000000000100000010000000000000000000000001111111111111111"));

   // std::cout << bitboard_to_string(white_pieces);
    std::cout << bitboard_to_string(black_pieces);

    WhitePawnSet WhitePawns;

    WhitePawns.initBitboard();
    WhitePawns.attackRight(white_pieces, black_pieces);


    return 0;
}