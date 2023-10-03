#ifndef King_H
#define King_H

#include <vector>

#include <utils.h>
#include <Move.h>
#include <KingLookup.h>

#include <Piece.h>

//////////
// King //
//////////

// Create King of specified color
// Have a lookup table with all possible moves from each square

// Need way to test for checks, castling etc

class King: public Piece {
    public:
        King(Color color);
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

    private:

        bitboard_t defaultStartPos = 576460752303423496;

        static constexpr const std::vector<bitboard_t>* KingLookup =
            &KingLookupTable;

        void generateStandardMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        void generateCastlingMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        bitboard_t whiteKingsideCastleCheck = generateBitboard(
            std::vector<Square>{Square::F1, Square::G1});
        bitboard_t whiteQueensideCastleCheck = generateBitboard(
            std::vector<Square>{Square::B1, Square::C1, Square::D1});

        bitboard_t blackKingsideCastleCheck = generateBitboard(
            std::vector<Square>{Square::F8, Square::G8});
        bitboard_t blackQueensideCastleCheck = generateBitboard(
            std::vector<Square>{Square::B8, Square::C8, Square::D8});


};

#endif
