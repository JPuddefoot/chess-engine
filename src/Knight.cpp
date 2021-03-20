#include <iostream>

#include <Knight.h>
#include <KnightLookup.h>


Knights::Knights(Color color) {
    this->color = color;
    if (color == Color::White)
        this->initialPos = generateBitboard(std::vector<Square>{Square::B1, Square::G1});
    if (color == Color::Black)
        this->initialPos = generateBitboard(std::vector<Square>{Square::B8, Square::G8});
};


void Knights::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {
       for (int i=0; i<KnightLookup->size(); i++) {
           std::cout << bitboard_to_string(KnightLookup->at(i));
       }
};


