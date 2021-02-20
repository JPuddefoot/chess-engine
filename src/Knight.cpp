#include <Knight.h>

Knights::Knights(Color color) {
    this->color = color;
    if (color == Color::White)
        this->initialPos = bitboard_t(std::string("0100001000000000000000000000000000000000000000000000000000000000"));
    if (color == Color::Black)
        this->initialPos = bitboard_t(std::string("0000000000000000000000000000000000000000000000000000000001000010"));
};

