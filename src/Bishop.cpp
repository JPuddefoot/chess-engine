#include <Bishop.h>

#include <iostream>

Bishops::Bishops(Color color) {
    this->color = color;
    if (color == Color::White)
        initialPos = generateBitboard(
            std::vector<Square>{Square::C1, Square::F1});
    if (color == Color::Black)
        initialPos = generateBitboard(
            std::vector<Square>{Square::C8, Square::F8});
    currentPos = initialPos;
};

// Generate the blocker board from the current board, retrieve magic number
// and produce hash, get move board from array with hash
void Bishops::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    if (currentPos.any()) {
        for (std::size_t bit=0; bit<currentPos.size(); bit++) {
            if (currentPos.test(bit)) {
                Square origin = static_cast<Square>(bit);
                std::cout << "origin " << Square_array[bit] << "\n";
                uint64_t bishopMask = BishopLookup::bishopMask(origin);

                uint64_t bishopBlocker = bishopMask &
                    (white_pieces.to_ulong() | black_pieces.to_ulong());

                std::cout << bitboard_to_string(bishopBlocker);
                // get the hash for specific square and blockers
                int hash = bishopBlocker*magicNums[bit] >>
                    (64-BishopLookup::BishopBits[bit]);

                bitboard_t attackSet = BishopLookup::attackTable[origin][hash];

                // For each allowed move, create a move and add to moveList
                for (std::size_t allowed_bit=0;
                    allowed_bit<attackSet.size(); allowed_bit++) {

                    if (attackSet.test(allowed_bit)) {
                        Square destination = static_cast<Square>(allowed_bit);
                        moveList.push_back(Move {origin, destination});
                    }
                }
            }
        }
    }
}


