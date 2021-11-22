#include "utils.h"


std::string bitboard_to_string(std::bitset<64> const & bitboard) {
    // bitset access is from lsb to msb i.e for 011011, bitset[0] = 1
    std::stringstream ss;
    ss << "\n";
    for (int row=0; row<=7; row++) {
        for (int column=7; column>=0; column--){
            std::string marker = (bitboard[row*8 + column] == 1 ? "1" : ".");
            ss << marker << " ";
        }
        ss << "\n";
    }
    ss << "\n";
    return ss.str();
};

// return a bitboard with 1s at given squares
bitboard_t generateBitboard(std::vector<Square> squares) {
    bitboard_t board = bitboard_t(std::string("0000000000000000000000000000000000000000000000000000000000000000"));

    for (Square square : squares) {
        board.set(static_cast<size_t>(square));
    }
    return board;
}
