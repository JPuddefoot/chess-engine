#include <King.h>
#include <KingLookup.h>

King::King(Color color) {
    this->color = color;
    this->name = (color==Color::White) ? "K" : "k";
}


void King::generateStandardMoves(const bitboard_t & white_pieces,
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

}

void King::generateCastlingMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    bitboard_t* kingsideCastleCheck;
    bitboard_t* queensideCastleCheck;

    if (color == Color::White) {
        kingsideCastleCheck = &whiteKingsideCastleCheck;
        queensideCastleCheck = &whiteQueensideCastleCheck;

        if (!(*kingsideCastleCheck & (white_pieces | black_pieces)).any()) {
            moveList.push_back(Move{Square::E1, Square::G1, 2}); // 2 = kingside castle
        }

        if (!(*queensideCastleCheck & (white_pieces | black_pieces)).any()) {
            moveList.push_back(Move{Square::E1, Square::C1, 3}); // 3 = queenside castle
        }

    }
    else {
        kingsideCastleCheck = &blackKingsideCastleCheck;
        queensideCastleCheck = &blackQueensideCastleCheck;

        if (!(*kingsideCastleCheck & (white_pieces | black_pieces)).any()) {
            moveList.push_back(Move{Square::E8, Square::G8, 2}); // 2 = kingside castle
        }

        if (!(*queensideCastleCheck & (white_pieces | black_pieces)).any()) {
            moveList.push_back(Move{Square::E8, Square::C8, 3}); // 3 = queenside castle
        }
    }




}

// TODO - does it make sense to have a bitboard for just one piece = could just store position?
void King::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    generateStandardMoves(white_pieces, black_pieces, moveList);

    if ((currentPos & defaultStartPos).any()) {
        generateCastlingMoves(white_pieces, black_pieces, moveList);
    }

};

