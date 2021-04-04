#ifndef Pawns_h
#define Pawns_h



#include <vector>

#include <utils.h>
#include <Move.h>

class Pawns {
    public:
        Pawns(Color color);
        Color color;
        bitboard_t initialPos;
        bitboard_t currentPos;
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

    private:
        void pushSingle(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
        void pushDouble(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
        void attackLeft(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
        void attackRight(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);
};

#endif