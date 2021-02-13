#include <string>
#include <bitset>
#include <ios>
#include <sstream>


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