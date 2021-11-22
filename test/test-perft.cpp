#include <catch2/catch.hpp>

#include <vector>
#include <iostream>

#include <Board.h>
#include <Move.h>


uint64_t perft_test(Board& board, int depth) {
    uint64_t nodes = 0;

    board.generateMoves();


    if (depth == 1) {
        return board.nextMoveList.size();
    }

    for (Move move : board.nextMoveList) {
        Move testMove = board.makeMove(move);
        nodes += perft_test(board, depth-1);
        board.undoMove();
        board.generateMoves();
    }

    return nodes;

}

TEST_CASE("Check Moves from starting position") {


    SECTION("Check 1 depth moves") {
        Board board = Board();
        uint64_t test = perft_test(board, 1);
        CHECK(test==20);
    }

    SECTION("Check 2 depth (i.e 1 ply) moves") {
        Board board = Board();
        uint64_t test = perft_test(board, 2);
        CHECK(test==400);
    }

    SECTION("Check 3 depth moves") {
        Board board = Board();
        CHECK(perft_test(board, 3) == 8902);
    }

    SECTION("Check 4 depth (2ply) moves") {
        Board board = Board();
        CHECK(perft_test(board, 4) == 197281);
    }

}

TEST_CASE("Check moves from position 1") {
    Board board = Board();
    board.makeMove(Move{Square::A2, Square::A4});
    board.makeMove(Move{Square::A7, Square::A5});

    std::cout << board.printBoard();

    CHECK(perft_test(board, 1) == 20);
}


