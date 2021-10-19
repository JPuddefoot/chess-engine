#ifndef BishopLookup_H
#define BishopLookup_H

#include <cmath>
#include <random>
#include <unordered_map>

#include <utils.h>
#include <Move.h>

class BishopLookup {
    public:

        static const uint64_t bishopMagicNumbers[64];

        static std::unordered_map<Square, std::array<uint64_t,4096>>attackTable;

        static uint64_t bishopMask(Square origin);
        static uint64_t bishopAttack(Square origin, uint64_t blocker);
        static uint64_t findMagic(Square origin);
        static int count_1s(uint64_t bitboard);
        static int transform(uint64_t blocker, uint64_t magic, int bits);
        static int BishopBits[64];
        static int BitTable[64];

    private:

        static uint64_t index_to_uint64(int index, int bits, uint64_t m);

        static uint64_t random_uint64_fewbits();

        static uint64_t random_uint64();

        static int pop_1st_bit(uint64_t * bb);

        
};

#endif