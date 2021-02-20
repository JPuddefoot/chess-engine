#ifndef utils_h
#define utils_h

#include <string>
#include <bitset>


// define a bitboard type
typedef std::bitset<64> bitboard_t;

// define a enum for piece colour
enum class Color {
    Black,
    White,
};

// return a more realistic representation of bitboard
std::string bitboard_to_string(const bitboard_t & bitboard);


#endif

