#include <Queen.h>

#include <iostream>

Queens::Queens(Color color) {
    this->color = color;
    this->name = (color==Color::White) ? "Q" : "q";
}

void Queens::generateMoves(const bitboard_t & white_pieces,
    const bitboard_t & black_pieces, std::vector<Move> & moveList) {

    if (currentPos.any()) {
        for (std::size_t bit=0; bit<currentPos.size(); bit++) {
            Square origin = static_cast<Square>(bit);
            if (currentPos.test(bit)) {
                ///////////////////////////////////////
                // Do horizontal movement (i.e rook) //
                ///////////////////////////////////////

                uint64_t rookMask = RookLookup::rookMask(origin);
                uint64_t rookBlocker = rookMask &
                    (white_pieces.to_ulong() | black_pieces.to_ulong());

                // get hash for specific square and blockers
                int hash = rookBlocker*RookLookup::rookMagicNumbers[bit] >>
                    (64-RookLookup::RookBits[bit]);

                bitboard_t rookAttackSet = RookLookup::attackTable[origin][hash];

                // Remove same color pieces from being able to be taken
                bitboard_t blocking_pieces = (color==Color::White) ?
                    white_pieces : black_pieces;

                rookAttackSet = rookAttackSet ^ (rookAttackSet & blocking_pieces);

                ///////////////////////////////////////
                // Do diagonal movement (i.e bishop) //
                ///////////////////////////////////////

                uint64_t bishopMask = BishopLookup::bishopMask(origin);

                uint64_t bishopBlocker = bishopMask &
                    (white_pieces.to_ulong() | black_pieces.to_ulong());

                // get the hash for specific square and blockers
                hash = bishopBlocker*BishopLookup::bishopMagicNumbers[bit] >>
                    (64-BishopLookup::BishopBits[bit]);

                bitboard_t bishopAttackSet = BishopLookup::attackTable[origin][hash];

                // Remove same color pieces from being able to be taken
                blocking_pieces = (color==Color::White) ?
                    white_pieces : black_pieces;

                bishopAttackSet = bishopAttackSet ^ (bishopAttackSet & blocking_pieces);

                // Combine rook and bishop attacks
                bitboard_t fullAttackSet = rookAttackSet | bishopAttackSet;

                // For each allowed move, create a move and add to moveList
                for (std::size_t allowed_bit=0;
                    allowed_bit<fullAttackSet.size(); allowed_bit++) {

                    if (fullAttackSet.test(allowed_bit)) {
                        Square destination = static_cast<Square>(allowed_bit);
                        moveList.push_back(Move {origin, destination});
                    }
                }
            }
        }
    }
}