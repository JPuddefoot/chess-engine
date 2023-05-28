#include <catch2/catch.hpp>

#include <vector>
#include <iostream>

#include <Board.h>
#include <Move.h>


uint64_t perft_test(Board& board, int depth) {
    uint64_t nodes = 0;

    //std::cout << "1" << board.printBoard() << "\n";
    board.generateMoves();

    //std::cout << "after" << board.printBoard() << "\n";
    if (depth == 1) {
        return board.nextMoveList.size();
    }

    //std::cout << "2" << board.printBoard() << "\n";
    for (Move move : board.nextMoveList) {
        //std::cout << "Depth: " << depth <<"\n";
        //std::cout << "MovePerft: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << " Info:" << move.info << "\n";
        Move testMove = board.makeMove(move);
        //std::cout << "3" <<  board.printBoard() << "\n";
        nodes += perft_test(board, depth-1);
        //std::cout << "4" << board.printBoard() << "\n";
        board.undoMove();
        board.generateMoves();
    }

    return nodes;

}

// Gives the number of nodes for each possible starting move
void perft_test_divide() {
    Board board = Board();

    board.makeMove(Move{Square::G2, Square::G4});
    board.makeMove(Move{Square::D7, Square::D6});
    board.makeMove(Move{Square::G4, Square::G5});
    board.generateMoves();

    uint64_t total_nodes = 0;



    for (Move& move : board.nextMoveList) {
        board.makeMove(move);
        uint64_t nodes = perft_test(board, 1);
        total_nodes += nodes;
        board.undoMove();
        board.generateMoves();
    }
    std::cout << "Total: " << total_nodes << "\n";
}

TEST_CASE("Check Moves from starting position") {

    //SECTION("Check 4 depth (2ply) moves") {
    //    Board board = Board();
    //    CHECK(perft_test(board, 4) == 197281);
    //}

    SECTION("Check 5 depth moves") {
        Board board = Board();
        CHECK(perft_test(board, 5) == 4865609);
    }

}

TEST_CASE("Check moves from position 1") {
    Board board = Board();
    board.makeMove(Move{Square::A2, Square::A4});
    board.makeMove(Move{Square::A7, Square::A5});

    CHECK(perft_test(board, 1) == 20);
}

/*TEST_CASE("Check moves after h2h4 h7h6 h4h5") {
    Board board = Board();
    board.makeMove({Square::H2, Square::H4, 1});
    board.makeMove({Square::H7, Square::H6});
    board.makeMove({Square::H4, Square::H5});
    board.makeMove({Square::G7, Square::G5, 1});

    CHECK(perft_test(board,1) == 22);
}*/

/*TEST_CASE("Check moves after g2g4 h7h5 g4g5") {
    Board board = Board();
    board.makeMove({Square::G2, Square::G4, 1});
    board.makeMove({Square::H7, Square::H5, 1});
    board.makeMove({Square::G4, Square::G5});

    CHECK(perft_test(board,2) == 22);
}*/

/*TEST_CASE("Check moves when in check") {

    SECTION("Check when check by Bishop piece") {
        Board board = Board();
        board.makeMove(Move{Square::E2, Square::E4});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::F1, Square::B5});

        CHECK(perft_test(board,1) == 5);
    }

    SECTION("Check when checked by Queen") {
        Board board = Board();
        board.makeMove(Move{Square::C2, Square::C3});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::D1, Square::A4});

        CHECK(perft_test(board,1) == 6);
    }

    SECTION("Check when Knight checks") {
        Board board = Board();
        board.makeMove(Move{Square::B1, Square::C3});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::C3, Square::D5});
        board.makeMove(Move{Square::H7, Square::H6});
        board.makeMove(Move{Square::D5, Square::C7});

        CHECK(perft_test(board, 1) == 2);

    }
}

TEST_CASE("Starting positions and divide") {
    perft_test_divide();
}*/


