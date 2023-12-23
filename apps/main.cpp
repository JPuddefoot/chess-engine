#include <iostream>
#include <vector>

#include <Board.h>

#include <Pawns.h>



int main() {


  Board board = Board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
  board.generateMoves();
  std::cout << board.printBoard() << "\n";

  std::cout << "no.moves = " << board.nextMoveList.size() << "\n";
  for (Move move : board.nextMoveList) {
    std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "with info: " << move.info << "\n";
  }




  return 0;
}