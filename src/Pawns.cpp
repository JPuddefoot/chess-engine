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

// Add all possible pawn single pushes to moveList
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

// Add double pawn pushes to moveList
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

// Add all possible pawn attacks to the left to moveList
void Pawns::attackLeft(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    bitboard_t leftFileMask = generateBitboard(std::vector<Square>{Square::A8,
        Square::A7, Square::A6, Square::A5, Square::A4, Square::A3, Square::A2,
        Square::A1});

    bitboard_t shifted_bitboard;
    shifted_bitboard = currentPos ^ (currentPos & leftFileMask);
    if (color == Color::White) {
        shifted_bitboard >>= 7;
        shifted_bitboard &= black_pieces;
    }
    if (color == Color::Black) {
        shifted_bitboard <<= 9; // from white's perspective black attacks left
        shifted_bitboard &= white_pieces;
    }
    // Generate movelist for all attacks to left
    for (std::size_t bit = 0; bit<shifted_bitboard.size(); bit++) {
        // Get origin and destination for each valid move
        if (shifted_bitboard.test(bit)) {
            Move move;
            move.destination = static_cast<Square>(bit);
            if (color == Color::White)
                move.origin = static_cast<Square>(bit+7);
            if (color == Color::Black)
                move.origin = static_cast<Square>(bit-9);
            moveList.push_back(move);
        }
    }
}

void Pawns::attackRight(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    bitboard_t rightFileMask = generateBitboard(std::vector<Square>{Square::H8,
        Square::H7, Square::H6, Square::H5, Square::H4, Square::H3, Square::H2,
        Square::H1});

    bitboard_t shifted_bitboard;

    shifted_bitboard = currentPos ^ (currentPos & rightFileMask);
    if (color == Color::White) {
        shifted_bitboard >>= 9;
        shifted_bitboard &= black_pieces;
    }
    if (color == Color::Black) {
        shifted_bitboard <<= 7; // allows using same fileMask for both colors
        shifted_bitboard &= white_pieces;
    }
    // Generate moveList for all attacks to right
    for (std::size_t bit = 0; bit<shifted_bitboard.size(); bit++) {
        // Get origin and destination for each valid move
        if (shifted_bitboard.test(bit)) {
            Move move;
            move.destination = static_cast<Square>(bit);
            if (color == Color::White)
                // Already checked that this is a valid move
                move.origin = static_cast<Square>(bit+9);
            if (color == Color::Black)
                move.origin = static_cast<Square>(bit-7);
            moveList.push_back(move);
        }
    }
}


void Pawns::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

        // Check if any pawns on the board still
        if (currentPos.any()) {
            pushSingle(white_pieces, black_pieces, moveList);
            pushDouble(white_pieces, black_pieces, moveList);
            attackLeft(white_pieces, black_pieces, moveList);
            attackRight(white_pieces, black_pieces, moveList);
        }
    }