#include <string>
#include <bitset>
#include <ios>
#include <sstream>


#include "utils.h"


std::string bitboard_to_string(std::bitset<64> const & bitboard) {
    // bitset access is from lsb to msb i.e for 011011, bitset[0] = 1
    std::stringstream ss;
    for (int column=0; column<=7; column++) {
        for (int row=0; row<8; row++){
            std::string marker = (bitboard[column*8+row-1] == 1 ? "1" : ".");
            ss << marker << " ";
        }
        ss << "\n";
    }
    return ss.str();
};