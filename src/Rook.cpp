#include <Rook.h>

#include <iostream>

Rooks::Rooks(Color color) {
    this->color = color;
    if (color == Color::White)
        initialPos = generateBitboard(
            std::vector<Square>{Square::A1, Square::H1});
    if (color == Color::Black)
        initialPos = generateBitboard(
            std::vector<Square>{Square::A8, Square::H8});
    currentPos = initialPos;
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

                //std::cout << "hash: " << hash << "\n";

                bitboard_t attackSet = RookLookup::attackTable[origin][hash];

                std::cout << bitboard_to_string(attackSet);

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