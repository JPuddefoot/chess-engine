#include <iostream>

#include "WhitePawnSet.h"
#include "utils.h"


int main() {
    WhitePawnSet WhitePawns;

    WhitePawns.InitBitboard();
    std::cout << bitboard_to_string(WhitePawns.bitboard);


    return 0;
}