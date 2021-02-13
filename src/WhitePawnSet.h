#include "utils.h"

class WhitePawnSet {
    public:
        bitboard_t currentPos;
        bitboard_t initialPos = bitboard_t(std::string("0000000011111111000000000000000000000000000000000000000000000000"));
        void initBitboard();
        void pushPawns(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
        void attackLeft(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
        void attackRight(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
};