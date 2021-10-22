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

  board.makeMove(Square::E2, Square::E4);
  board.makeMove(Square::D7, Square::D5);
  board.makeMove(Square::E4, Square::D5);
  std::cout << board.printBoard();
  board.makeMove(Square::D8, Square::D5);

  std::cout << board.printBoard();

  board.undoMove();

  std::cout << board.printBoard();

  std::cout << bitboard_to_string(board.whitePieces);

  board.undoMove();

  std::cout << board.printBoard();

  board.undoMove();

  std::cout << board.printBoard();

  board.undoMove();

  std::cout << board.printBoard();










  return 0;
}