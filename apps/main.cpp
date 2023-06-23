#include <iostream>
#include <vector>

#include <Board.h>

#include <Pawns.h>



int main() {


  Board board = Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
  board.generateMoves();
  std::cout << board.printBoard() << "\n";

  std::cout << "no.moves = " << board.nextMoveList.size() << "\n";
  for (Move move : board.nextMoveList) {
    std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
  }
  return 0;
}