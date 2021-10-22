#ifndef Move_h
#define Move_h


#include <string>
#include <bitset>
// Define a move:
//
// origin square (0-63) where 63 is A1 and 0 is H8
// destination square (0-63)
// promotion piece type
// special move flag



enum class Square {
    H8, G8, F8, E8, D8, C8, B8, A8,
    H7, G7, F7, E7, D7, C7, B7, A7,
    H6, G6, F6, E6, D6, C6, B6, A6,
    H5, G5, F5, E5, D5, C5, B5, A5,
    H4, G4, F4, E4, D4, C4, B4, A4,
    H3, G3, F3, E3, D3, C3, B3, A3,
    H2, G2, F2, E2, D2, C2, B2, A2,
    H1, G1, F1, E1, D1, C1, B1, A1
};

const std::string Square_array[64] = {
    "H8", "G8", "F8", "E8", "D8", "C8", "B8", "A8",
    "H7", "G7", "F7", "E7", "D7", "C7", "B7", "A7",
    "H6", "G6", "F6", "E6", "D6", "C6", "B6", "A6",
    "H5", "G5", "F5", "E5", "D5", "C5", "B5", "A5",
    "H4", "G4", "F4", "E4", "D4", "C4", "B4", "A4",
    "H3", "G3", "F3", "E3", "D3", "C3", "B3", "A3",
    "H2", "G2", "F2", "E2", "D2", "C2", "B2", "A2",
    "H1", "G1", "F1", "E1", "D1", "C1", "B1", "A1"
};

struct Move
{
    Square origin;
    Square destination;
    uint16_t info;
};

// Method to compare if two moves are the same
bool operator==(Move const & lhs, Move const & rhs);


#endif