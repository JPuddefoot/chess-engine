#include <stdint.h>
#include <iostream>

#include <Pawns.h>

Pawns::Pawns(Color color) {
    this->color = color;
    if (color == Color::White)
        initialPos = generateBitboard(
            std::vector<Square>{Square::A2, Square::B2, Square::C2, Square::D2,
            Square::E2, Square::F2, Square::G2, Square::H2});
    if (color == Color::Black)
        initialPos = generateBitboard(
            std::vector<Square>{Square::A7, Square::B7, Square::C7, Square::D7,
            Square::E7, Square::F7, Square::G7, Square::H7});
    currentPos = initialPos;
}

// Produce moveList of all possible pawn single pushes in given position
void Pawns::pushSingle(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    bitboard_t shifted_bitboard;

    if (color == Color::White) {
        shifted_bitboard = currentPos >> 8;
    }
    if (color == Color::Black) {
        shifted_bitboard = currentPos << 8;
    }
    shifted_bitboard ^= (shifted_bitboard & (white_pieces | black_pieces));

    // Generate movelist for all allowed single pushes
    for (std::size_t bit=0; bit<shifted_bitboard.size(); bit++) {
        // if there is a valid move, get square and origin square
        // create and add Move to movelist
        if (shifted_bitboard.test(bit)) {
            Move move;
            move.destination = static_cast<Square>(bit);
            if (color == Color::White)
                move.origin = static_cast<Square>(bit+8);
            if (color == Color::Black)
                move.origin = static_cast<Square>(bit-8);
            moveList.push_back(move);
        }
    }

};

// Produce bitboard of double pawn pushes
void Pawns::pushDouble(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    // check which pawns are in initial position
    bitboard_t allowed_double = currentPos & initialPos;
    // shift by 2 rows
    if (color == Color::White) {
        allowed_double = (allowed_double >> 16);
        // Check for pieces between origin and target
        allowed_double ^= (allowed_double &
            (white_pieces >> 8 | black_pieces >> 8));
    }
    if (color == Color::Black) {
        allowed_double = (allowed_double << 16);
        // Check for pieces between origin and target
        allowed_double ^= (allowed_double &
            (white_pieces << 8 | black_pieces << 8));
    }
    allowed_double ^= (allowed_double & (white_pieces | black_pieces));

    // Generate movelist for all allowed double pushes
    for (std::size_t bit = 0; bit<allowed_double.size(); bit++) {
        // get origin and destination for each valid move
        if (allowed_double.test(bit)) {
            Move move;
            move.destination = static_cast<Square>(bit);
            if (color == Color::White)
                move.origin = static_cast<Square>(bit+16);
            if (color == Color::Black)
                move.origin = static_cast<Square>(bit-16);
            moveList.push_back(move);
        }
    }
}

// Produce bitboard (or list?) of all possible pawn attacks to the left
bitboard_t Pawns::attackLeft(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t leftFileMask = bitboard_t(std::string("1000000010000000100000001000000010000000100000001000000010000000"));
        // mask A-file pawns (can't attack left)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & leftFileMask);
        shifted_bitboard >>= 7;
        shifted_bitboard &= black_pieces;
        return shifted_bitboard;
}

bitboard_t Pawns::attackRight(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces) {

        bitboard_t rightFileMask = bitboard_t(std::string("0000000100000001000000010000000100000001000000010000000100000001"));
        // mask H-file pawns (can't attack right)
        bitboard_t shifted_bitboard = this->currentPos;
        shifted_bitboard ^= (shifted_bitboard & rightFileMask);
        shifted_bitboard >>= 9;
        shifted_bitboard &= black_pieces;
        return shifted_bitboard;
    }

void Pawns::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

        // Check if any pawns on the board still
        if (currentPos.any()) {
            pushSingle(white_pieces, black_pieces, moveList);
            pushDouble(white_pieces, black_pieces, moveList);
        }
    }