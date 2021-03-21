#include <iostream>
#include <vector>

#include <Pawns.h>
#include "Knight.h"
#include "utils.h"
#include <Move.h>


int main() {

    bitboard_t white_pieces = generateBitboard(
        std::vector<Square>{Square::A3, Square::E6});

    bitboard_t black_pieces = generateBitboard(
        std::vector<Square>{Square::G3, Square::C6});

   // std::cout << bitboard_to_string(white_pieces);
    std::cout << bitboard_to_string(black_pieces);

    Pawns WhitePawns = Pawns(Color::White);
    Pawns blackPawns = Pawns(Color::Black);

    std::vector<Move> moveList = {};
    //WhitePawns.generateMoves(white_pieces, black_pieces, moveList);
    blackPawns.generateMoves(white_pieces, black_pieces, moveList);

    /*
    Knights BlackKnights = Knights(Color::Black);
    std::cout << bitboard_to_string(BlackKnights.initialPos);
    BlackKnights.generateMoves(white_pieces, black_pieces, moveList);

    Knights WhiteKnights = Knights(Color::White);
    std::cout << bitboard_to_string(WhiteKnights.initialPos);
    WhiteKnights.generateMoves(white_pieces, black_pieces, moveList);
    */

    for (Move move : moveList) {
        std::cout << "Origin: " << Square_array[static_cast<int>(move.origin)] <<
        " Destination: " << Square_array[static_cast<int>(move.destination)] << "\n";
    }

    return 0;
}