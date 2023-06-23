#include <Rook.h>

#include <iostream>

Rooks::Rooks(Color color) {
    this->color = color;
    this->name = (color==Color::White) ? "R" : "r";
};

void Rooks::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    if (currentPos.any()) {
        for (std::size_t bit=0; bit<currentPos.size(); bit++) {
            if (currentPos.test(bit)) {
                Square origin = static_cast<Square>(bit);

                uint64_t rookMask = RookLookup::rookMask(origin);
                uint64_t rookBlocker = rookMask &
                    (white_pieces.to_ulong() | black_pieces.to_ulong());

                // get hash for specific square and blockers
                int hash = rookBlocker*magicNums[bit] >>
                    (64-RookLookup::RookBits[bit]);

                bitboard_t attackSet = RookLookup::attackTable[origin][hash];

                // Remove same color pieces from being able to be taken
                bitboard_t blocking_pieces = (color==Color::White) ?
                    white_pieces : black_pieces;

                attackSet = attackSet ^ (attackSet & blocking_pieces);

                // For each allowed move, create a move and add to moveList
                for (std::size_t allowed_bit=0;
                    allowed_bit<attackSet.size(); allowed_bit++) {

                    if (attackSet.test(allowed_bit)) {
                        Square destination = static_cast<Square>(allowed_bit);
                        moveList.push_back(Move {origin, destination});
                    }
                }
                // TODO - need to rule out ability to take own color pieces
            }
        }
    }
}