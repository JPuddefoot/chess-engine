#include <iostream>
#include <vector>

#include <Board.h>


int main() {

    Board board = Board();

    board.generateMoves();
  //  for (Move move : board.moveList) {
  //      std::cout << "origin: " << Square_array[static_cast<std::size_t>(move.origin)]
  //          << "destination: " << Square_array[static_cast<std::size_t>(move.destination)]
 //           << "\n";
 //   }

    std::cout << board.printBoard();
    std::cout << bitboard_to_string(board.white_pieces);

    Move move = board.moveList[4];
    std::cout << "Moving: " << Square_array[static_cast<std::size_t>(move.origin)];
    board.makeMove(move.origin, move.destination);


    board.generateMoves();
    move = board.moveList[4];
    std::cout << "Moving: " << Square_array[static_cast<std::size_t>(move.origin)];
    board.makeMove(move.origin, move.destination);

    std::cout << board.printBoard();

    board.generateMoves();
    move = board.moveList[9];
    board.makeMove(move.origin, move.destination);

    std::cout << board.printBoard();



    return 0;
}