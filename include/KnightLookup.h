#ifndef KnightLookup_H
#define KnightLookup_H

#include <vector>

#include <utils.h>
#include <Move.h>


// Lookup table of possible knight moves from a given position
// The index of the array sets the square position of the knight
// i.e Lookup[0] = positions for knight on H8
// Lookup[63] = positions for knight on A1
const std::vector<bitboard_t>KnightLookupTable{
    // H8
    generateBitboard(std::vector<Square>{Square::F7, Square::G6}),
    // G8
    generateBitboard(std::vector<Square>{Square::H6, Square::F6, Square::E7}),
    // F8
    generateBitboard(std::vector<Square>{Square::H7, Square::G6, Square::E6, Square::D7}),
    // E8
    generateBitboard(std::vector<Square>{Square::G7, Square::F6, Square::D6, Square::C7}),
    // D8
    generateBitboard(std::vector<Square>{Square::F7, Square::E6, Square::C6, Square::B7}),
    // C8
    generateBitboard(std::vector<Square>{Square::E7, Square::D6, Square::B6, Square::A7}),
    // B8
    generateBitboard(std::vector<Square>{Square::D7, Square::C6, Square::A6}),
    // A8
    generateBitboard(std::vector<Square>{Square::C7, Square::B6}),

    // H7
    generateBitboard(std::vector<Square>{Square::G5, Square::F8, Square::F6}),
    // G7
    generateBitboard(std::vector<Square>{Square::H5, Square::F5, Square::E8, Square::E6}),
    // F7
    generateBitboard(std::vector<Square>{Square::H8, Square::H6, Square::G5, Square::E5, Square::D8, Square::D6}),
    // E7
    generateBitboard(std::vector<Square>{Square::G8, Square::G6, Square::F5, Square::D5, Square::C8, Square::C6}),
    // D7
    generateBitboard(std::vector<Square>{Square::F8,Square::F6, Square::E5, Square::C5, Square::B8, Square::B6}),
    // C7
    generateBitboard(std::vector<Square>{Square::E8,Square::E6, Square::D5, Square::B5, Square::A8, Square::A6}),
    // B7
    generateBitboard(std::vector<Square>{Square::D8,Square::D6, Square::C5, Square::A5}),
    // A7
    generateBitboard(std::vector<Square>{Square::C8, Square::C6, Square::B5}),

    // H6
    generateBitboard(std::vector<Square>{Square::G8, Square::G4, Square::F7, Square::F5}),
    // G6
    generateBitboard(std::vector<Square>{Square::H8, Square::H4, Square::F8, Square::F4, Square::E7, Square::E5}),
    // F6
    generateBitboard(std::vector<Square>{Square::H7, Square::H5, Square::G8, Square::G4, Square::E8, Square::E4, Square::D7, Square::D5}),
    // E6
    generateBitboard(std::vector<Square>{Square::G7, Square::G5, Square::F8, Square::F4, Square::D8, Square::D4, Square::C7, Square::C5}),
    // D6
    generateBitboard(std::vector<Square>{Square::F7, Square::F5, Square::E8, Square::E4, Square::C8, Square::C4, Square::B7, Square::B5}),
    // C6
    generateBitboard(std::vector<Square>{Square::E7, Square::E5, Square::D8, Square::D4, Square::B8, Square::B4, Square::A7, Square::A5}),
    // B6
    generateBitboard(std::vector<Square>{Square::D7, Square::D5, Square::C8, Square::C4, Square::A8, Square::A4}),
    // A6
    generateBitboard(std::vector<Square>{Square::C7, Square::C5, Square::B8, Square::B4}),

    // H5
    generateBitboard(std::vector<Square>{Square::G7, Square::G3, Square::F6, Square::F4}),
    // G5
    generateBitboard(std::vector<Square>{Square::H7, Square::H3, Square::F7, Square::F3, Square::E6, Square::E4}),
    // F5
    generateBitboard(std::vector<Square>{Square::H6, Square::H4, Square::G7, Square::G3, Square::E7, Square::E3, Square::D6, Square::D4}),
    // E5
    generateBitboard(std::vector<Square>{Square::G6, Square::G4, Square::F7, Square::F3, Square::D7, Square::D3, Square::C6, Square::C4}),
    // D5
    generateBitboard(std::vector<Square>{Square::F6, Square::F4, Square::E7, Square::E3, Square::C7, Square::C3, Square::B6, Square::B4}),
    // C5
    generateBitboard(std::vector<Square>{Square::E6, Square::E4, Square::D7, Square::D3, Square::B7, Square::B3, Square::A6, Square::A4}),
    // B5
    generateBitboard(std::vector<Square>{Square::D6, Square::D4, Square::C7, Square::C3, Square::A7, Square::A3}),
    // A5
    generateBitboard(std::vector<Square>{Square::C6, Square::C4, Square::B7, Square::B3}),

    // H4
    generateBitboard(std::vector<Square>{Square::G6, Square::G2, Square::F5, Square::F3}),
    // G4
    generateBitboard(std::vector<Square>{Square::H6, Square::H2, Square::F6, Square::F2, Square::E5, Square::E3}),
    // F4
    generateBitboard(std::vector<Square>{Square::H5, Square::H3, Square::G6, Square::G2, Square::E6, Square::E2, Square::D5, Square::D3}),
    // E4
    generateBitboard(std::vector<Square>{Square::G5, Square::G3, Square::F6, Square::F2, Square::D6, Square::D2, Square::C5, Square::C3}),
    // D4
    generateBitboard(std::vector<Square>{Square::F5, Square::F3, Square::E6, Square::E2, Square::C6, Square::C2, Square::B5, Square::B3}),
    // C4
    generateBitboard(std::vector<Square>{Square::E5, Square::E3, Square::D6, Square::D2, Square::B6, Square::B2, Square::A5, Square::A3}),
    // B4
    generateBitboard(std::vector<Square>{Square::D5, Square::D3, Square::C6, Square::C2, Square::A6, Square::A2}),
    // A4
    generateBitboard(std::vector<Square>{Square::C5, Square::C3, Square::B6, Square::B2}),

    // H3
    generateBitboard(std::vector<Square>{Square::G5, Square::G1, Square::F4, Square::F2}),
    // G3
    generateBitboard(std::vector<Square>{Square::H5, Square::H1, Square::F5, Square::F1, Square::E4, Square::E2}),
    // F3
    generateBitboard(std::vector<Square>{Square::H4, Square::H2, Square::G5, Square::G1, Square::E5, Square::E1, Square::D4, Square::D2}),
    // E3
    generateBitboard(std::vector<Square>{Square::G4, Square::G2, Square::F5, Square::F1, Square::D5, Square::D1, Square::C4, Square::C2}),
    // D3
    generateBitboard(std::vector<Square>{Square::F4, Square::F2, Square::E5, Square::E1, Square::C5, Square::C1, Square::B4, Square::B2}),
    // C3
    generateBitboard(std::vector<Square>{Square::E4, Square::E2, Square::D5, Square::D1, Square::B5, Square::B1, Square::A4, Square::A2}),
    // B3
    generateBitboard(std::vector<Square>{Square::D4, Square::D2, Square::C5, Square::C1, Square::A5, Square::A1}),
    // A3
    generateBitboard(std::vector<Square>{Square::C4, Square::C2, Square::B5, Square::B1}),

    // H2
    generateBitboard(std::vector<Square>{Square::G4, Square::F3, Square::F1}),
    // G2
    generateBitboard(std::vector<Square>{Square::H4, Square::F4, Square::E3, Square::E1}),
    // F2
    generateBitboard(std::vector<Square>{Square::H3, Square::H1, Square::G4, Square::E4, Square::D3, Square::D1}),
    // E2
    generateBitboard(std::vector<Square>{Square::G3, Square::G1, Square::F4, Square::D4, Square::C3, Square::C1}),
    // D2
    generateBitboard(std::vector<Square>{Square::F3, Square::F1, Square::E4, Square::C4, Square::B3, Square::B1}),
    // C2
    generateBitboard(std::vector<Square>{Square::E3, Square::E1, Square::D4, Square::B4, Square::A3, Square::A1}),
    // B2
    generateBitboard(std::vector<Square>{Square::D3, Square::D1, Square::C4, Square::A4}),
    // A2
    generateBitboard(std::vector<Square>{Square::C3, Square::C1, Square::B4}),

    // H1
    generateBitboard(std::vector<Square>{Square::G3, Square::F2}),
    // G1
    generateBitboard(std::vector<Square>{Square::H3, Square::F3, Square::E2}),
    // F1
    generateBitboard(std::vector<Square>{Square::H2, Square::G3, Square::E3, Square::D2}),
    // E1
    generateBitboard(std::vector<Square>{Square::G2, Square::F3, Square::D3, Square::C2}),
    // D1
    generateBitboard(std::vector<Square>{Square::F2, Square::E3, Square::C3, Square::B2}),
    // C1
    generateBitboard(std::vector<Square>{Square::E2, Square::D3, Square::B3, Square::A2}),
    // B1
    generateBitboard(std::vector<Square>{Square::D2, Square::C3, Square::A3}),
    // A1
    generateBitboard(std::vector<Square>{Square::C2, Square::B3})
};

#endif
