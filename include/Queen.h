#ifndef Queen_H
#define Queen_H

#include <vector>
#include <algorithm>

#include <Move.h>
#include <utils.h>
#include <RookLookup.h>
#include <BishopLookup.h>

#include <Piece.h>

///////////
// Queen //
///////////

class Queens: public Piece {
    public:
        Queens(Color color);
        void generateMoves(const bitboard_t & white_pieces,
            const bitboard_t & black_pieces, std::vector<Move> & moveList);

        virtual std::string const & getName() {return name;}

};

#endif