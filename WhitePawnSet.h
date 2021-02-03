#include "utils.h"

class WhitePawnSet {
    public:
       bitboard_t bitboard;
       void initBitboard();
       void pushPawns(const bitboard_t & white_pieces,
        const bitboard_t & black_pieces);
};