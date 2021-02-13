#include <stdint.h>
#include <iostream>
#include "WhitePawnSet.h"

void WhitePawnSet::initBitboard() {
    this->currentPos = this->initialPos;
    //std::cout << bitboard_to_string(this->currentPos);
};

// Produce bitboard (or list?) of all possible pawn pushes in given position
void WhitePawnSet::pushPawns(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

    // single push
    bitboard_t shifted_bitboard = this->currentPos >> 8;
    shifted_bitboard ^= (shifted_bitboard & black_pieces) ;

    // double push
    // check which pawns are in initial position
    bitboard_t allowed_double = this->currentPos & this->initialPos;
    // shift by 2 rows
    allowed_double = (allowed_double >> 16);
    std::cout << bitboard_to_string(allowed_double);
    // shift black pieces back a row to test if piece blocking pawn from moving
    allowed_double = (allowed_double & (black_pieces >> 8)) ^ allowed_double;
    // add double pushes to total bitboard
    shifted_bitboard |= allowed_double;
    std::cout << bitboard_to_string(allowed_double);

};
// Produce bitboard (or list?) of all possible pawn attacks to the left
void WhitePawnSet::attackLeft(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t leftFileMask = bitboard_t(std::string("1000000010000000100000001000000010000000100000001000000010000000"));
        // mask A-file pawns (can't attack left)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & leftFileMask);
        shifted_bitboard >>= 7;
        shifted_bitboard &= black_pieces;
        std::cout << bitboard_to_string(shifted_bitboard);
}

void WhitePawnSet::attackRight(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t rightFileMask = bitboard_t(std::string("0000000100000001000000010000000100000001000000010000000100000001"));
        // mask H-file pawns (can't attack right)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & rightFileMask);
        shifted_bitboard >>= 9;
        shifted_bitboard &= black_pieces;
        std::cout << bitboard_to_string(shifted_bitboard);
    }

