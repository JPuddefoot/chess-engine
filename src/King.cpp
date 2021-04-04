#include <King.h>
#include <KingLookup.h>

King::King(Color color) {
    this->color = color;
    if (color == Color::White)
        initialPos = generateBitboard(
            std::vector<Square>{Square::E1});
    if (color == Color::Black)
        initialPos = generateBitboard(
            std::vector<Square>{Square::E8});
    currentPos = initialPos;
}


// TODO - does it make sense to have a bitboard for just one piece = could just store position?
void King::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    for (std::size_t bit=0; bit<currentPos.size(); bit++) {
        if (currentPos.test(bit)) {
            Square origin = static_cast<Square>(bit);
            // Get moves from lookup table
            bitboard_t possible_moves = KingLookup->at(bit);
            // White king blocked by white pieces and opposite for black
            bitboard_t blocking_pieces = (color==Color::White) ?
                white_pieces : black_pieces;
            bitboard_t allowed_moves =
                possible_moves ^ (possible_moves & blocking_pieces);

            // for each allowed move create a Move and add to moveList
            for (std::size_t allowed_bit=0; allowed_bit<allowed_moves.size();
                allowed_bit++) {

                if (allowed_moves.test(allowed_bit)) {
                    Square destination = static_cast<Square>(allowed_bit);
                    moveList.push_back(Move {origin, destination});
                }
            }
        }
    }
};

