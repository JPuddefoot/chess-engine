#ifndef utils_h
#define utils_h

#include <string>
#include <bitset>
#include <vector>
#include <ios>
#include <sstream>


#include <Move.h>


// define a bitboard type
typedef std::bitset<64> bitboard_t;

// define a enum for piece colour
enum class Color {
    Black,
    White,
};

// define an enum for each piece
enum class PieceType {
    None,
    wPawn,
    bPawn,
    wKnight,
    bKnight,
    bBishop,
    wBishop,
    wRook,
    bRook,
    wQueen,
    bQueen,
    wKing,
    bKing
};

// return a more realistic representation of bitboard
std::string bitboard_to_string(const bitboard_t & bitboard);

// return a bitboard with 1s at desired squares
bitboard_t generateBitboard(std::vector<Square> squares);


#endif

