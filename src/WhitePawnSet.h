#ifndef WhitePawnSet_h
#define WhitePawnSet_h



#include <vector>

#include "utils.h"
#include "Move.h"

class WhitePawnSet {
    public:
        bitboard_t currentPos;
        bitboard_t initialPos = bitboard_t(std::string("0000000011111111000000000000000000000000000000000000000000000000"));
        void initBitboard();
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
        bitboard_t pushPawns(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
        bitboard_t pushDouble(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
        void attackLeft(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
        void attackRight(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces);
};

#endif