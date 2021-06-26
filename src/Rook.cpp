#include <Rook.h>
#include <iostream>

Rooks::Rooks(Color color) {
    this->color = color;
    if (color == Color::White) {
        initialPos = generateBitboard(
            std::vector<Square>{Square::A1, Square::H1});
    }
    if (color == Color::Black) {
        initialPos = generateBitboard(
            std::vector<Square>{Square::A8, Square::H8});
    }
    currentPos = initialPos;
};

void Rooks::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {



    // Go through bitboard to find a rook position
    if (currentPos.any()) {
        for (std::size_t bit=0; bit<currentPos.size(); bit++) {
            // For each rook, create the blockerBoard from white & black pieces
            // Get the magic number for the origin square, then create the hash
            // Finally get the moveSet for that particular hash
            if (currentPos.test(bit)) {
                Square origin = static_cast<Square>(bit);
                bitboard_t rookBlockerMask = RookLookup::generateRookBlockerMask(
                    origin);

                // AND mask with black and white pieces to get blockerBoard
                bitboard_t blockerBoard = (rookBlockerMask & white_pieces) |
                    (rookBlockerMask & black_pieces);

                std::cout << bitboard_to_string(blockerBoard);

                size_t originNum = static_cast<size_t>(origin);

                uint64_t magicNum = RookLookup::rookMagicNumbers.at(originNum);
                std::cout << "Magic Num: " << magicNum << "\n";

                // get hash from blocker and magic number
                uint64_t hash = (blockerBoard.to_ullong() * magicNum) >>
                    (64-blockerBoard.count() + 3);
                std::cout << hash << "\n";

                // check hash in map
                if (RookLookup::moveSets.at(originNum).count(hash)) {
                    std::cout << "Hash in map" << "\n";
                }
                else {
                    std::cout << "Damn, start again";
                }
                //std::cout << "Move Set: " << bitboard_to_string(
                 //   RookLookup::moveSets.at(static_cast<size_t>(origin))[hash]);

            }
        }
    }
};
