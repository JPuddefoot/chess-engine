#include <iostream>
#include <vector>

#include <Board.h>

#include <Pawns.h>



int main() {


  Board board = Board();
  board.makeMove({Square::C2, Square::C3});
    board.makeMove({Square::A7, Square::A6});
    board.makeMove({Square::D1, Square::A4});

  std::cout << board.printBoard() << "\n";

  board.generateMoves();

  for (Move move : board.nextMoveList) {
    std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
  }

  //std::cout << "No.moves: " << board.nextMoveList.size() << "\n";


  return 0;
}