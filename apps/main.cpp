#include <iostream>
#include <vector>

#include <Board.h>

#include <Pawns.h>



int main() {


  Board board = Board();
  board.makeMove({Square::H2, Square::H4, 1});
  board.makeMove({Square::H7, Square::H6});
  board.makeMove({Square::H4, Square::H5});
  board.makeMove({Square::G7, Square::G5, 1});

  std::cout << board.printBoard() << "\n";

  board.undoMove();

  std::cout << board.printBoard() << "\n";

  //board.generateMoves();

  //for (Move move : board.nextMoveList) {
  //  std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
 // }

  std::cout << "No.moves: " << board.nextMoveList.size() << "\n";



  return 0;
}