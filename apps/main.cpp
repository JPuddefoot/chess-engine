#include <iostream>
#include <vector>

#include "WhitePawnSet.h"
#include "Knight.h"
#include "utils.h"
#include <Move.h>


int main() {

    bitboard_t white_pieces = bitboard_t(std::string("1111111111111111000000000000000000000000000000000000000000000000"));
    bitboard_t black_pieces = bitboard_t(std::string("0000000000000000100000010000000000000000000000001111111111111111"));

   // std::cout << bitboard_to_string(white_pieces);
    std::cout << bitboard_to_string(black_pieces);

    WhitePawnSet WhitePawns;

    WhitePawns.initBitboard();

    std::vector<Move> moveList = {};
    //WhitePawns.generateMoves(white_pieces, black_pieces, moveList);


    Knights BlackKnights = Knights(Color::Black);
    std::cout << bitboard_to_string(BlackKnights.initialPos);
    BlackKnights.generateMoves(white_pieces, black_pieces, moveList);

    Knights WhiteKnights = Knights(Color::White);
    std::cout << bitboard_to_string(WhiteKnights.initialPos);
    WhiteKnights.generateMoves(white_pieces, black_pieces, moveList);


    for (Move move : moveList) {
        std::cout << "Origin: " << Square_array[static_cast<int>(move.origin)] <<
        " Destination: " << Square_array[static_cast<int>(move.destination)] << "\n";
    }

    return 0;
}