#include <iostream>
#include <vector>

#include <Board.h>

#include <Bishop.h>
#include <BishopLookup.h>

#include <RookLookup.h>
#include <Rook.h>

#include <Queen.h>



int main() {

  RookLookup::fillAttackTable();

  Board board = Board();

  board.generateMoves();

  board.makeMove(Move{Square::A2, Square::A4});
  board.makeMove(Move{Square::A7, Square::A5});
  std::cout << board.printBoard();

  board.generateMoves();

  for (Move move : board.nextMoveList) {
    std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
  }

  std::cout << "No.moves: " << board.nextMoveList.size() << "\n";

  return 0;
}