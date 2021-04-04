#ifndef KingLookup_H
#define KingLookup_H

#include <vector>

#include <utils.h>
#include <Move.h>

// Lookup table of possible king moves from a given position
// The index of the array sets the square position of king
// i.e Lookup[0] = positions for king on H8

const std::vector<bitboard_t>KingLookupTable {
    // H8
    generateBitboard(std::vector<Square>{Square::G8, Square::G7, Square::H7}),
    // G8
    generateBitboard(std::vector<Square>{Square::H8, Square::H7, Square::G7, Square::F8, Square::F7}),
    // F8
    generateBitboard(std::vector<Square>{Square::G8, Square::G7, Square::F7, Square::E8, Square::E7}),
    // E8
    generateBitboard(std::vector<Square>{Square::F8, Square::F7, Square::E7, Square::D8, Square::D7}),
    // D8
    generateBitboard(std::vector<Square>{Square::E8, Square::E7, Square::D7, Square::C8, Square::C7}),
    // C8
    generateBitboard(std::vector<Square>{Square::D8, Square::D7, Square::C7, Square::B8, Square::B7}),
    // B8
    generateBitboard(std::vector<Square>{Square::C8, Square::C7, Square::B7, Square::A8, Square::A7}),
    // A8
    generateBitboard(std::vector<Square>{Square::B8, Square::B7, Square::A7}),

    // H7
    generateBitboard(std::vector<Square>{Square::H8, Square::H6, Square::G8, Square::G7, Square::G6}),
    // G7
    generateBitboard(std::vector<Square>{Square::H8, Square::H7, Square::H6, Square::G8, Square::G6, Square::F8, Square::F7, Square::F6}),
    // F7
    generateBitboard(std::vector<Square>{Square::G8, Square::G7, Square::G6, Square::F8, Square::F6, Square::E8, Square::E7, Square::E6}),
    // E7
    generateBitboard(std::vector<Square>{Square::F8, Square::F7, Square::F6, Square::E8, Square::E6, Square::D8, Square::D7, Square::D6}),
    // D7
    generateBitboard(std::vector<Square>{Square::E8, Square::E7, Square::E6, Square::D8, Square::D6, Square::C8, Square::C7, Square::C6}),
    // C7
    generateBitboard(std::vector<Square>{Square::D8, Square::D7, Square::D6, Square::C8, Square::C6, Square::B8, Square::B7, Square::B6}),
    // B7
    generateBitboard(std::vector<Square>{Square::C8, Square::C7, Square::C6, Square::B8, Square::B6, Square::A8, Square::A7, Square::A6}),
    // A7
    generateBitboard(std::vector<Square>{Square::B8, Square::B7, Square::B6, Square::A8, Square::A6}),

    // H6
    generateBitboard(std::vector<Square>{Square::H7, Square::H5, Square::G7, Square::G6, Square::G5}),
    // G6
    generateBitboard(std::vector<Square>{Square::H7, Square::H6, Square::H5, Square::G7, Square::G5, Square::F7, Square::F6, Square::F5}),
    // F6
    generateBitboard(std::vector<Square>{Square::G7, Square::G6, Square::G5, Square::F7, Square::F5, Square::E7, Square::E6, Square::E5}),
    // E6
    generateBitboard(std::vector<Square>{Square::F7, Square::F6, Square::F5, Square::E7, Square::E5, Square::D7, Square::D6, Square::D5}),
    // D6
    generateBitboard(std::vector<Square>{Square::E7, Square::E6, Square::E5, Square::D7, Square::D5, Square::C7, Square::C6, Square::C5}),
    // C6
    generateBitboard(std::vector<Square>{Square::D7, Square::D6, Square::D5, Square::C7, Square::C5, Square::B7, Square::B6, Square::B5}),
    // B6
    generateBitboard(std::vector<Square>{Square::C7, Square::C6, Square::C5, Square::B7, Square::B5, Square::A7, Square::A6, Square::A5}),
    // A6
    generateBitboard(std::vector<Square>{Square::B7, Square::B6, Square::B5, Square::A7, Square::A5}),

    // H5
    generateBitboard(std::vector<Square>{Square::H6, Square::H4, Square::G6, Square::G5, Square::G4}),
    // G5
    generateBitboard(std::vector<Square>{Square::H6, Square::H5, Square::H4, Square::G6, Square::G4, Square::F6, Square::F5, Square::F4}),
    // F5
    generateBitboard(std::vector<Square>{Square::G6, Square::G5, Square::G4, Square::F6, Square::F4, Square::E6, Square::E5, Square::E4}),
    // E5
    generateBitboard(std::vector<Square>{Square::F6, Square::F5, Square::F4, Square::E6, Square::E4, Square::D6, Square::D5, Square::D4}),
    // D5
    generateBitboard(std::vector<Square>{Square::E6, Square::E5, Square::E4, Square::D6, Square::D4, Square::C6, Square::C5, Square::C4}),
    // C5
    generateBitboard(std::vector<Square>{Square::D6, Square::D5, Square::D4, Square::C6, Square::C4, Square::B6, Square::B5, Square::B4}),
    // B5
    generateBitboard(std::vector<Square>{Square::C6, Square::C5, Square::C4, Square::B6, Square::B4, Square::A6, Square::A5, Square::A4}),
    // A5
    generateBitboard(std::vector<Square>{Square::B6, Square::B5, Square::B4, Square::A6, Square::A4}),

    // H4
    generateBitboard(std::vector<Square>{Square::H5, Square::H3, Square::G5, Square::G4, Square::G3}),
    // G4
    generateBitboard(std::vector<Square>{Square::H5, Square::H4, Square::H3, Square::G5, Square::G3, Square::F5, Square::F4, Square::F3}),
    // F4
    generateBitboard(std::vector<Square>{Square::G5, Square::G4, Square::G3, Square::F5, Square::F3, Square::E5, Square::E4, Square::E3}),
    // E4
    generateBitboard(std::vector<Square>{Square::F5, Square::F4, Square::F3, Square::E5, Square::E3, Square::D5, Square::D4, Square::D3}),
    // D4
    generateBitboard(std::vector<Square>{Square::E5, Square::E4, Square::E3, Square::D5, Square::D3, Square::C5, Square::C4, Square::C3}),
    // C4
    generateBitboard(std::vector<Square>{Square::D5, Square::D4, Square::D3, Square::C5, Square::C3, Square::B5, Square::B4, Square::B3}),
    // B4
    generateBitboard(std::vector<Square>{Square::C5, Square::C4, Square::C3, Square::B5, Square::B3, Square::A5, Square::A4, Square::A3}),
    // A4
    generateBitboard(std::vector<Square>{Square::B5, Square::B4, Square::B3, Square::A5, Square::A3}),

    // H3
    generateBitboard(std::vector<Square>{Square::H4, Square::H2, Square::G4, Square::G3, Square::G2}),
    // G3
    generateBitboard(std::vector<Square>{Square::H4, Square::H3, Square::H2, Square::G4, Square::G2, Square::F4, Square::F3, Square::F2}),
    // F3
    generateBitboard(std::vector<Square>{Square::G4, Square::G3, Square::G2, Square::F4, Square::F2, Square::E4, Square::E3, Square::E2}),
    // E3
    generateBitboard(std::vector<Square>{Square::F4, Square::F3, Square::F2, Square::E4, Square::E2, Square::D4, Square::D3, Square::D2}),
    // D3
    generateBitboard(std::vector<Square>{Square::E4, Square::E3, Square::E2, Square::D4, Square::D2, Square::C4, Square::C3, Square::C2}),
    // C3
    generateBitboard(std::vector<Square>{Square::D4, Square::D3, Square::D2, Square::C4, Square::C2, Square::B4, Square::B3, Square::B2}),
    // B3
    generateBitboard(std::vector<Square>{Square::C4, Square::C3, Square::C2, Square::B4, Square::B2, Square::A4, Square::A3, Square::A2}),
    // A3
    generateBitboard(std::vector<Square>{Square::B4, Square::B3, Square::B2, Square::A4, Square::A2}),

    // H2
    generateBitboard(std::vector<Square>{Square::H3, Square::H1, Square::G3, Square::G2, Square::G1}),
    // G2
    generateBitboard(std::vector<Square>{Square::H3, Square::H2, Square::H1, Square::G3, Square::G1, Square::F3, Square::F2, Square::F1}),
    // F2
    generateBitboard(std::vector<Square>{Square::G3, Square::G2, Square::G1, Square::F3, Square::F1, Square::E3, Square::E2, Square::E1}),
    // E2
    generateBitboard(std::vector<Square>{Square::F3, Square::F2, Square::F1, Square::E3, Square::E1, Square::D3, Square::D2, Square::D1}),
    // D2
    generateBitboard(std::vector<Square>{Square::E3, Square::E2, Square::E1, Square::D3, Square::D1, Square::C3, Square::C2, Square::C1}),
    // C2
    generateBitboard(std::vector<Square>{Square::D3, Square::D2, Square::D1, Square::C3, Square::C1, Square::B3, Square::B2, Square::B1}),
    // B2
    generateBitboard(std::vector<Square>{Square::C3, Square::C2, Square::C1, Square::B3, Square::B1, Square::A3, Square::A2, Square::A1}),
    // A2
    generateBitboard(std::vector<Square>{Square::B3, Square::B2, Square::B1, Square::A3, Square::A1}),

    // H1
    generateBitboard(std::vector<Square>{Square::H2, Square::G2, Square::G1}),
    // G1
    generateBitboard(std::vector<Square>{Square::H2, Square::H1, Square::G2, Square::F2, Square::F1}),
    // F1
    generateBitboard(std::vector<Square>{Square::G2, Square::G1, Square::F2, Square::E2, Square::E1}),
    // E1
    generateBitboard(std::vector<Square>{Square::F2, Square::F1, Square::E2, Square::D2, Square::D1}),
    // D1
    generateBitboard(std::vector<Square>{Square::E2, Square::E1, Square::D2, Square::C2, Square::C1}),
    // C1
    generateBitboard(std::vector<Square>{Square::D2, Square::D1, Square::C2, Square::B2, Square::B1}),
    // B1
    generateBitboard(std::vector<Square>{Square::C2, Square::C1, Square::B2, Square::A2, Square::A1}),
    // A1
    generateBitboard(std::vector<Square>{Square::B2, Square::B1, Square::A2})
};

#endif
