#include <RookLookup.h>
#include <iostream>

void RookLookup::fillAttackTableForSquare(Square origin) {
    // Using prefound magic nums, fill the attackTable
    uint64_t blockers[4096], attackSets[4096];
    std::array<uint64_t, 4096> hashTable;
    int m_bits = RookBits[static_cast<int>(origin)];

    uint64_t mask = rookMask(origin);
    int numBlockers = count_1s(mask);

    // Go through all possible blocker masks (i.e 0 to 2^numBlockers) and
    // put them and attackSet into arrays
    for (int i=0; i < (1 << numBlockers); i++) {
        blockers[i] = index_to_uint64(i, numBlockers, mask);
        attackSets[i] = rookAttack(origin, blockers[i]);
    }
    uint64_t magic = rookMagicNumbers[static_cast<size_t>(origin)];

    for (int i=0; i < (1 << numBlockers); i++) {
        int j = transform(blockers[i], magic, m_bits);
        hashTable[j] = attackSets[i];
    }

    attackTable[origin] = hashTable;
}

void RookLookup::fillAttackTable() {
    fillAttackTableForSquare(Square::A8);
    fillAttackTableForSquare(Square::B8);
    fillAttackTableForSquare(Square::C8);
    fillAttackTableForSquare(Square::D8);
    fillAttackTableForSquare(Square::E8);
    fillAttackTableForSquare(Square::F8);
    fillAttackTableForSquare(Square::G8);
    fillAttackTableForSquare(Square::H8);

    fillAttackTableForSquare(Square::A7);
    fillAttackTableForSquare(Square::B7);
    fillAttackTableForSquare(Square::C7);
    fillAttackTableForSquare(Square::D7);
    fillAttackTableForSquare(Square::E7);
    fillAttackTableForSquare(Square::F7);
    fillAttackTableForSquare(Square::G7);
    fillAttackTableForSquare(Square::H7);

    fillAttackTableForSquare(Square::A6);
    fillAttackTableForSquare(Square::B6);
    fillAttackTableForSquare(Square::C6);
    fillAttackTableForSquare(Square::D6);
    fillAttackTableForSquare(Square::E6);
    fillAttackTableForSquare(Square::F6);
    fillAttackTableForSquare(Square::G6);
    fillAttackTableForSquare(Square::H6);

    fillAttackTableForSquare(Square::A5);
    fillAttackTableForSquare(Square::B5);
    fillAttackTableForSquare(Square::C5);
    fillAttackTableForSquare(Square::D5);
    fillAttackTableForSquare(Square::E5);
    fillAttackTableForSquare(Square::F5);
    fillAttackTableForSquare(Square::G5);
    fillAttackTableForSquare(Square::H5);

    fillAttackTableForSquare(Square::A4);
    fillAttackTableForSquare(Square::B4);
    fillAttackTableForSquare(Square::C4);
    fillAttackTableForSquare(Square::D4);
    fillAttackTableForSquare(Square::E4);
    fillAttackTableForSquare(Square::F4);
    fillAttackTableForSquare(Square::G4);
    fillAttackTableForSquare(Square::H4);

    fillAttackTableForSquare(Square::A3);
    fillAttackTableForSquare(Square::B3);
    fillAttackTableForSquare(Square::C3);
    fillAttackTableForSquare(Square::D3);
    fillAttackTableForSquare(Square::E3);
    fillAttackTableForSquare(Square::F3);
    fillAttackTableForSquare(Square::G3);
    fillAttackTableForSquare(Square::H3);

    fillAttackTableForSquare(Square::A2);
    fillAttackTableForSquare(Square::B2);
    fillAttackTableForSquare(Square::C2);
    fillAttackTableForSquare(Square::D2);
    fillAttackTableForSquare(Square::E2);
    fillAttackTableForSquare(Square::F2);
    fillAttackTableForSquare(Square::G2);
    fillAttackTableForSquare(Square::H2);

    fillAttackTableForSquare(Square::A1);
    fillAttackTableForSquare(Square::B1);
    fillAttackTableForSquare(Square::C1);
    fillAttackTableForSquare(Square::D1);
    fillAttackTableForSquare(Square::E1);
    fillAttackTableForSquare(Square::F1);
    fillAttackTableForSquare(Square::G1);
    fillAttackTableForSquare(Square::H1);
}

uint64_t RookLookup::findMagic(Square origin) {
    // Finds a working magic number for a given square.
    // For every possible blocker board, gets the correct attackSet
    // With a trial magic number, generates hashes for each attackSet and
    // attempts to place. If colliding hashes for different attackSets, try a
    // different magic number.

    uint64_t blockers[4096], attackSets[4096];
    std::array<uint64_t, 4096> hashTable;
    int m_bits = RookBits[static_cast<int>(origin)];

    uint64_t mask = rookMask(origin);
    int numBlockers = count_1s(mask);

    // Go through all possible blocker masks (i.e 0 to 2^numBlockers) and
    // put them and attackSet into arrays
    for (int i=0; i < (1 << numBlockers); i++) {
        blockers[i] = index_to_uint64(i, numBlockers, mask);
        attackSets[i] = rookAttack(origin, blockers[i]);

    }

    // Go through many different trial magic numbers
    for (int k = 0; k<10000000; k++) {
        int fail = 0;
        uint64_t magic = random_uint64_fewbits();
        if (count_1s((mask * magic) & 0xFF00000000000000ULL) < 6) continue;
        for (int i=0; i<4096; i++) {
            hashTable[i] = 0ULL; // reset the array after last attempt
        }
        for (int i=0; !fail && i < (1 << numBlockers); i++) {
            int j = transform(blockers[i], magic, m_bits);
            // Check for collisions
            if (hashTable[j] == 0ULL) {
                // No collision - can assign to array
                hashTable[j] = attackSets[i];
            }
            else if (hashTable[j] != attackSets[i]) {
              //  std::cout << bitboard_to_string(hashTable[j]);
              //  std::cout << bitboard_to_string(attackSets[i]);
                fail = 1;
            }
        }
        // Trial number passed - is working magic number!!
        if (!fail) {
            attackTable[origin] = hashTable;
            return magic;
        }
    }
    return 0ULL;
}

std::unordered_map<Square, std::array<uint64_t,4096>> RookLookup::attackTable = {};

uint64_t RookLookup::random_uint64() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
  u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

int RookLookup::transform(uint64_t blocker, uint64_t magic, int bits) {
    return (int)((blocker*magic) >> (64-bits));
}

uint64_t RookLookup::random_uint64_fewbits() {
    return random_uint64() & random_uint64() & random_uint64();
}

uint64_t RookLookup::rookAttack(Square origin, uint64_t blocker) {
    // Returns the attack set for a rook on the origin square, given
    // a particular blocker board

    uint64_t attackSet = 0ULL;

    int origin_int = static_cast<int>(origin);

    int rank = origin_int/8;
    int file = origin_int % 8;

    // go through each possible move - if there is a piece on that square
    // then stop after adding that square to the attack set
    for (int r = rank, f = file+1; f<=7; f++) {
        attackSet |= (1ULL << (f+r*8));
        if (blocker & (1ULL << (f+r*8))) {
            break;
        }
    }
    for (int r = rank, f = file-1; f>=0; f--) {
        attackSet |= (1ULL << (f+r*8));
        if (blocker & (1ULL << (f+r*8))) {
            break;
        }
    }
    for (int r = rank+1, f = file; r<=7; r++) {
        attackSet |= (1ULL << (f+r*8));
        if (blocker & (1ULL << (f+r*8))) {
            break;
        }
    }
    for (int r = rank-1, f = file; r>=0; r--) {
        attackSet |= (1ULL << (f+r*8));
        if (blocker & (1ULL << (f+r*8))) {
            break;
        }
    }

    return attackSet;

}


int RookLookup::BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

int RookLookup::pop_1st_bit(uint64_t *bb) {
  uint64_t b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

uint64_t RookLookup::index_to_uint64(int index, int bits, uint64_t m) {
    uint64_t result = 0ULL;
    for (int i = 0; i<bits; i++) {
        int j = pop_1st_bit(&m);
        if (index & (1 << i)) {
            result |= (1ULL << j);
        }
    }
    return result;
}


int RookLookup::count_1s(uint64_t bitboard) {
    // Counts the number of 1s (i.e occupied squares) in a bitboard
    int r;
    for (r = 0; bitboard; r++, bitboard&=bitboard-1);
    return r;
}

uint64_t RookLookup::rookMask(Square origin) {
    // Returns a mask for given square - i.e bitboard covering all
    // possible moves for rook, except at board edges

    uint64_t mask = 0ULL;

    int origin_int = static_cast<int>(origin);

    int rank = origin_int/8;
    int file = origin_int % 8;

    for (int r = rank, f = file+1; f<=6; f++) {
        mask |= (1ULL << (f+r*8));
    }
    for (int r = rank, f = file-1; f>=1; f--) {
        mask |= (1ULL << (f+r*8));
    }
    for (int r = rank+1, f = file; r<=6; r++) {
        mask |= (1ULL << (f+r*8));
    }
    for (int r = rank-1, f = file; r>=1; r--) {
        mask |= (1ULL << (f+r*8));
    }

    return mask;
}


int RookLookup::RookBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

// Magic nums found using full magicNums function,
// using these cos the full function takes ages
uint64_t const RookLookup::rookMagicNumbers[64] = {
    756607761056301088,
    486389076241424385,
    72092778679042112,
    2630106649158748161,
    180146733941000192,
    648589814731636770,
    180146184134856832,
    2918332697065554048,
    11529355785708503092,
    1267187687899136,
    2490631468938694656,
    293015506591416352,
    288934097953489024,
    3096241940480520,
    2596606664451031552,
    281616710647938,
    9719133065330688,
    1193595738806829072,
    576745526890856466,
    360429257568030720,
    722829389795952768,
    9223513324166054400,
    144397214955930112,
    576744426307850385,
    140739637952517,
    1170971088563208264,
    19799803437186,
    942527774937055360,
    5070958365245568,
    72061994232053888,
    10385301842383864320,
    581848436590281801,
    329150075794096256,
    72128031505784833,
    5197155070050832448,
    288300890958333970,
    146649081425430530,
    581105115214119936,
    4828149286694814032,
    2323899487900144641,
    18049857767899136,
    9223654062661107744,
    9516248984046403600,
    1153765998257045536,
    577591050391027840,
    5066584209096708,
    1152939105383088648,
    4827859488876920833,
    180144604161573632,
    63067988042981952,
    35188671256320,
    2469116105206038656,
    2251817001949568,
    562984581857792,
    9227893237937669120,
    2305843628831998464,
    4647715366276964609,
    18014538100186369,
    2307340820539246849,
    360850989000950818,
    5231493951774524418,
    281767035013651,
    4611687186792841348,
    10696191184830530,
};

/*
uint64_t const RookLookup::rookMagicNumbers[64] = {
    findMagic(Square::H8),
    findMagic(Square::G8),
    findMagic(Square::F8),
    findMagic(Square::E8),
    findMagic(Square::D8),
    findMagic(Square::C8),
    findMagic(Square::B8),
    findMagic(Square::A8),

    findMagic(Square::H7),
    findMagic(Square::G7),
    findMagic(Square::F7),
    findMagic(Square::E7),
    findMagic(Square::D7),
    findMagic(Square::C7),
    findMagic(Square::B7),
    findMagic(Square::A7),

    findMagic(Square::H6),
    findMagic(Square::G6),
    findMagic(Square::F6),
    findMagic(Square::E6),
    findMagic(Square::D6),
    findMagic(Square::C6),
    findMagic(Square::B6),
    findMagic(Square::A6),

    findMagic(Square::H5),
    findMagic(Square::G5),
    findMagic(Square::F5),
    findMagic(Square::E5),
    findMagic(Square::D5),
    findMagic(Square::C5),
    findMagic(Square::B5),
    findMagic(Square::A5),

    findMagic(Square::H4),
    findMagic(Square::G4),
    findMagic(Square::F4),
    findMagic(Square::E4),
    findMagic(Square::D4),
    findMagic(Square::C4),
    findMagic(Square::B4),
    findMagic(Square::A4),

    findMagic(Square::H3),
    findMagic(Square::G3),
    findMagic(Square::F3),
    findMagic(Square::E3),
    findMagic(Square::D3),
    findMagic(Square::C3),
    findMagic(Square::B3),
    findMagic(Square::A3),

    findMagic(Square::H2),
    findMagic(Square::G2),
    findMagic(Square::F2),
    findMagic(Square::E2),
    findMagic(Square::D2),
    findMagic(Square::C2),
    findMagic(Square::B2),
    findMagic(Square::A2),

    findMagic(Square::H1),
    findMagic(Square::G1),
    findMagic(Square::F1),
    findMagic(Square::E1),
    findMagic(Square::D1),
    findMagic(Square::C1),
    findMagic(Square::B1),
    findMagic(Square::A1),
};
*/
