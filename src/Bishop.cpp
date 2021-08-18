#include <Bishop.h>

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

void Bishops::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {
        int i = 1;
    }


