#include <catch2/catch.hpp>

#include <vector>
#include <iostream>

#include <Board.h>
#include <Move.h>


uint64_t perft_test(Board& board, int depth) {
    uint64_t nodes = 0;

    board.generateMoves();


    if (depth == 0) {
        return board.nextMoveList.size();
    }

    for (Move move : board.nextMoveList) {
        Move testMove = board.makeMove(move);
        if ((testMove.info >> 2) & 1UL) {
            std::cout << "Capture\n";
        }
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

}


