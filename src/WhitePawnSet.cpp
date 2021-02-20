#include <stdint.h>
#include <iostream>

#include "WhitePawnSet.h"

void WhitePawnSet::initBitboard() {
    this->currentPos = this->initialPos;
};

// Produce bitboard (or list?) of all possible pawn pushes in given position
bitboard_t WhitePawnSet::pushPawns(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

    // single push
    bitboard_t shifted_bitboard = this->currentPos >> 8;
    shifted_bitboard ^= (shifted_bitboard & black_pieces);
    return shifted_bitboard;

};
// Produce bitboard of double pawn pushes
bitboard_t WhitePawnSet::pushDouble(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        // check which pawns are in initial position
        bitboard_t allowed_double = this->currentPos & this->initialPos;
        // shift by 2 rows
        allowed_double = (allowed_double >> 16);
        // shift black pieces back a row to test if piece blocking pawn from moving
        allowed_double = (allowed_double & (black_pieces >> 8)) ^ allowed_double;
        return allowed_double;
    }
// Produce bitboard (or list?) of all possible pawn attacks to the left
bitboard_t WhitePawnSet::attackLeft(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t leftFileMask = bitboard_t(std::string("1000000010000000100000001000000010000000100000001000000010000000"));
        // mask A-file pawns (can't attack left)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & leftFileMask);
        shifted_bitboard >>= 7;
        shifted_bitboard &= black_pieces;
        return shifted_bitboard;
}

bitboard_t WhitePawnSet::attackRight(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t rightFileMask = bitboard_t(std::string("0000000100000001000000010000000100000001000000010000000100000001"));
        // mask H-file pawns (can't attack right)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & rightFileMask);
        shifted_bitboard >>= 9;
        shifted_bitboard &= black_pieces;
        return shifted_bitboard;
    }

void WhitePawnSet::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

        // generate moves from pawn single push
        bitboard_t single_push_pawns = this->pushPawns(white_pieces,
            black_pieces);
        // check if any bits are set to 1 (i.e valid moves exist)
        if (single_push_pawns.any()) {
            // go through bitboard of possible pawn pushes
            for (std::size_t i=0; i< single_push_pawns.size(); i++) {
                // if there is a valid move, get square and origin square
                // create and add Move to movelist
                if (single_push_pawns.test(i)) {
                    int bit_num = static_cast<int>(i);
                    Square destination = static_cast<Square>(bit_num);
                    Square origin = static_cast<Square>(bit_num+8);
                    moveList.push_back(Move {origin, destination});
                }
            }
        }

        // generator moves from double pawn push
        bitboard_t double_push_pawns = this->pushDouble(white_pieces,
            black_pieces);

        if (double_push_pawns.any()) {
            for (std::size_t i=0; i<double_push_pawns.size(); i++) {
                if (double_push_pawns.test(i)) {
                    int bit_num = static_cast<int>(i);
                    Square destination = static_cast<Square>(bit_num);
                    Square origin = static_cast<Square>(bit_num+16);
                    moveList.push_back(Move {origin, destination});
                }
            }
        }
        // generate moves from left attack
        bitboard_t left_attack_pawns = this->attackLeft(white_pieces,
            black_pieces);
        if (left_attack_pawns.any()) {
            for (std::size_t i=0; i<left_attack_pawns.size(); i++) {
                if (left_attack_pawns.test(i)) {
                    int bit_num = static_cast<int>(i);
                    Square destination = static_cast<Square>(bit_num);
                    Square origin = static_cast<Square>(bit_num+7);
                    moveList.push_back(Move {origin, destination});
                }
            }
        }
        // generate moves from right attack
        bitboard_t right_attack_pawns = this->attackRight(white_pieces,
            black_pieces);
        if (right_attack_pawns.any()) {
            for (std::size_t i=0; i<right_attack_pawns.size(); i++) {
                if (right_attack_pawns.test(i)) {
                    int bit_num = static_cast<int>(i);
                    Square destination = static_cast<Square>(bit_num);
                    Square origin = static_cast<Square>(bit_num + 9);
                    moveList.push_back(Move {origin, destination});
                }
            }
        }
    }