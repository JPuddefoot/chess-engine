#include <iostream>
#include <vector>

#include <Board.h>

#include <Bishop.h>
#include <BishopLookup.h>

#include <RookLookup.h>
#include <Rook.h>

#include <Queen.h>



int main() {

  Board board = Board();

  board.generateMoves();

  std::cout << board.printBoard();

  board.makeMove(Square::E2, Square::E4);
  board.makeMove(Square::D7, Square::D5);
  board.makeMove(Square::E4, Square::E5);

  std::cout << board.printBoard();

  board.generateMoves();

 //   std::cout << bitboard_to_string(board.whitePieces);

  for (Move move : board.moveList) {
      std::cout << "origin: " << Square_array[static_cast<std::size_t>(move.origin)]
        << "destination: " << Square_array[static_cast<std::size_t>(move.destination)]
        << "\n";
  }




  return 0;
}