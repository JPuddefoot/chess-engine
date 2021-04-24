#include <iostream>
#include <vector>

#include <Board.h>


int main() {

    Board board = Board();

    std::cout << board.printBoard();

    board.makeMove(Square::E1, Square::D1);

    std::cout << board.printBoard();

    board.makeMove(Square::E2, Square::E5);

    std::cout << board.printBoard();

    return 0;
}