#include <BishopLookup.h>
#include <iostream>


uint64_t BishopLookup::findMagic(Square origin) {
    // Finds a working magic number for a given square.
    // For every possible blocker board, gets the correct attackSet
    // With a trial magic number, generates hashes for each attackSet and
    // attempts to place. If colliding hashes for different attackSets, try a
    // different magic number.

    uint64_t blockers[4096], attackSets[4096], hashTable[4096];
    int m_bits = BishopBits[static_cast<int>(origin)];
    int fail;

    uint64_t mask = bishopMask(origin);
    int numBlockers = count_1s(mask);

    // Go through all possible blocker masks (i.e 0 to 2^numBlockers) and
    // put them and attackSet into arrays
    for (int i=0; i < (1 << numBlockers); i++) {
        blockers[i] = index_to_uint64(i, numBlockers, mask);
        attackSets[i] = bishopAttack(origin, blockers[i]);
    }

    // Go through many different trial magic numbers
    for (int k = 0; k<100000; k++) {
        uint64_t magic = random_uint64_fewbits();
        if (count_1s((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
        for (int i=0; i<4096; i++) {
            hashTable[i] = 0ULL; // reset the array after last attempt
        }
        for (int i=0, fail=0; !fail && i < (1 << numBlockers); i++) {
            int j = transform(blockers[i], magic, m_bits);
            // Check for collisions
            if (hashTable[j] == 0ULL) {
                // No collision - can assign to array
                hashTable[j] = attackSets[i];
            }
            else if (hashTable[j] != attackSets[i]) {
                // collision with a non-equivalent attack set - try new number
                fail = 1;
            }
        }
        // Trial number passed - is working magic number!!
        if (!fail) {
            return magic;
        }
    }

    return 0ULL;
}

int BishopLookup::BishopBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

int BishopLookup::BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};


uint64_t BishopLookup::index_to_uint64(int index, int bits, uint64_t m) {
    uint64_t result = 0ULL;
    for (int i = 0; i<bits; i++) {
        int j = pop_1st_bit(&m);
        if (index & (1 << i)) {
            result |= (1ULL << j);
        }
    }
    return result;
}

uint64_t BishopLookup::random_uint64_fewbits() {
    return random_uint64() & random_uint64() & random_uint64();
}

uint64_t BishopLookup::random_uint64() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
  u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

int BishopLookup::pop_1st_bit(uint64_t *bb) {
  uint64_t b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}



int BishopLookup::count_1s(uint64_t bitboard) {
    // Counts the number of 1s (i.e occupied squares) in a bitboard
    int r;
    for (r = 0; bitboard; r++, bitboard&=bitboard-1);
    return r;
}

uint64_t BishopLookup::bishopMask(Square origin) {
    // Returns a mask for given square - i.e bitboard covering all
    // possible moves for bishop, except at board edges

    uint64_t mask = 0ULL;

    int origin_int = static_cast<int>(origin);

    int rank = origin_int/8;
    int file = origin_int % 8;


    for (int r = rank+1, f = file+1; r<=6 && f <=6; r++, f++) {
        mask |= (1ULL << (f + r*8));
    }
    for (int r = rank+1, f = file-1; r<=6 && f>=1; r++, f--) {
        mask |= (1ULL << (f+r*8));
    }
    for (int r = rank-1, f = file+1; r>=1 && f<=6; r--, f++) {
        mask |= (1ULL << (f+r*8));
    }
    for (int r = rank-1, f = file-1; r>=1 && f>=1; r--, f--) {
        mask |= (1ULL << (f+r*8));
    }

    return mask;
}

int BishopLookup::transform(uint64_t blocker, uint64_t magic, int bits) {
    return (int)((blocker*magic) >> (64-bits));
}

uint64_t BishopLookup::bishopAttack(Square origin, uint64_t blocker) {
    // Returns the attack set for a bishop on the origin square, given
    // a particular blocker board

    uint64_t attackSet = 0ULL;

    int origin_int = static_cast<int>(origin);

    int rank = origin_int/8;
    int file = origin_int % 8;

    // go through each possible move - if there is a piece on that square
    // then stop after adding that square to the attack set

    for (int r = rank+1, f = file+1; r<=7 && f <=7; r++, f++) {
        attackSet |= (1ULL << (f + r*8));

        if (blocker & (1ULL << (f + r*8))) {
            break;
        }
    }
    for (int r = rank+1, f = file-1; r<=7 && f>=0; r++, f--) {
        attackSet |= (1ULL << (f+r*8));

        if (blocker & (1ULL << (f + r*8))) {
            break;
        }
    }
    for (int r = rank-1, f = file+1; r>=0 && f<=7; r--, f++) {
        attackSet |= (1ULL << (f+r*8));

        if (blocker & (1ULL << (f + r*8))) {
            break;
        }
    }
    for (int r = rank-1, f = file-1; r>=0 && f>=0; r--, f--) {
        attackSet |= (1ULL << (f+r*8));

        if (blocker & (1ULL << (f + r*8))) {
            break;
        }
    }

    return attackSet;
}