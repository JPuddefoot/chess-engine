#include <iostream>
#include <vector>

#include <Board.h>

#include <Bishop.h>



int main() {

    //Board board = Board();

   // board.generateMoves();

 //   std::cout << board.printBoard();

  //  board.makeMove(Square::E2, Square::E4);
  //  board.makeMove(Square::D7, Square::D5);

//    std::cout << board.printBoard();

  //  board.generateMoves();

 //   std::cout << bitboard_to_string(board.whitePieces);

  //  for (Move move : board.moveList) {
  //    std::cout << "origin: " << Square_array[static_cast<std::size_t>(move.origin)]
  //      << "destination: " << Square_array[static_cast<std::size_t>(move.destination)]
  //      << "\n";
  //  }

  //  generateRookBlockerMask(Square::E1);
  //  generateBlockerBoards(generateRookBlockerMask(Square::A1));



  //RookLookup::generateRookMoveSetforSquare(Square::H7);
  //generateRookMoveSetforSquare(Square::A1);

   // for (auto const & magicNum : RookLookup::rookMagicNumbers) {
   //     std::cout << magicNum << "\n";
   // }

    Bishops whiteBishops = Bishops(Color::White);

    for (int i = 0 ; i < 64; i++) {
        std::cout << whiteBishops.magicNums[i] << "\n";
    }







    return 0;
}