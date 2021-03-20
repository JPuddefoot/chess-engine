#include <iostream>

#include <Knight.h>
#include <KnightLookup.h>


Knights::Knights(Color color) {
    this->color = color;
    if (color == Color::White)
        initialPos = generateBitboard(
            std::vector<Square>{Square::B1, Square::G1});
    if (color == Color::Black)
        initialPos = generateBitboard(
            std::vector<Square>{Square::B8, Square::G8});
    currentPos = this->initialPos;
};


void Knights::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    // Go through bitboard, when find a knight, get possible moves
    // and check for pieces in the way from the same color
    if (currentPos.any()) {
        for (std::size_t bit=0; bit<currentPos.size(); bit++) {
            // test if bit has a knight on it
            if (currentPos.test(bit)) {
                Square origin = static_cast<Square>(bit);
                // Get the moves from lookup table
                bitboard_t possible_moves = KnightLookup->at(bit);
                // White knight is blocked by white pieces and opposite for black
                bitboard_t blocking_pieces = (color==Color::White) ?
                    white_pieces : black_pieces;
                bitboard_t allowed_moves =
                    possible_moves ^ (possible_moves & blocking_pieces);

                // For each allowed move create a Move and add to moveList
                for (std::size_t allowed_bit=0; allowed_bit<allowed_moves.size();
                    allowed_bit++) {

                    if (allowed_moves.test(allowed_bit)) {
                        Square destination = static_cast<Square>(allowed_bit);
                        moveList.push_back(Move {origin, destination});
                    }
                }

            }
        }
    }

};

// todo - add way to add new knights (in case promotion)


