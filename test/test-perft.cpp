#include <catch2/catch.hpp>

#include <vector>
#include <iostream>

#include <Board.h>
#include <Move.h>


uint64_t perft_test(Board& board, int depth) {

    uint64_t nodes = 0;

    board.generateMoves();

    //for (Move move : board.nextMoveList) {
    //    std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
    //}

    if (depth == 1) {
        return board.nextMoveList.size();
    }


    std::vector<Move> moveList;
    std::copy(board.nextMoveList.begin(), board.nextMoveList.end(),
        std::back_inserter(moveList));

    for (Move move : moveList) {

        //std::cout << "\nMove2: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
        Move testMove = board.makeMove(move);

        nodes += perft_test(board, depth-1);


        board.undoMove();

        board.generateMoves();

        //for (Move move : board.nextMoveList) {
         //   std::cout << "Move3: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
        //}
    }

    return nodes;

}

// Gives the number of nodes for each possible starting move
/*void perft_test_divide() {
    Board board = Board();

    board.makeMove(Move{Square::H2, Square::H4,1});
    board.makeMove(Move{Square::A7, Square::A6});
    board.generateMoves();

    uint64_t total_nodes = 0;



    for (Move& move : board.nextMoveList) {
        board.makeMove(move);
        uint64_t nodes = perft_test(board, 4);
        total_nodes += nodes;
        board.undoMove();
        board.generateMoves();
    }
    std::cout << "Total: " << total_nodes << "\n";
    CHECK(total_nodes == 9366);
}*/

TEST_CASE("Check Moves from starting position") {

    SECTION("Check 4 depth (2ply) moves") {
        Board board = Board();
        CHECK(perft_test(board, 4) == 197281);
    }

    //SECTION("Check 6 depth moves") {
    //    Board board = Board();
    //    CHECK(perft_test(board, 6) ==  119060324 );
    //}

}

/*TEST_CASE("Check moves from position 1") {
    Board board = Board();
    board.makeMove(Move{Square::A2, Square::A4});
    board.makeMove(Move{Square::A7, Square::A5});

    CHECK(perft_test(board, 1) == 20);
}*/

TEST_CASE("Check perft from position involving castling") {
    Board board = Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");

}

TEST_CASE("Dividing Perft") {
    Board board = Board();
    /*board.makeMove({Square::A2, Square::A3});
    CHECK(perft_test(board,4) == 181046);
    board.undoMove();

    board.makeMove({Square::B2, Square::B3});
    CHECK(perft_test(board,4) == 215255);
    board.undoMove();

    board.makeMove({Square::C2, Square::C3});
    CHECK(perft_test(board,4) == 222861);
    board.undoMove();*/

    //board.makeMove({Square::D2, Square::D3});
    //board.makeMove({Square::B7, Square::B5,1});
    //CHECK(perft_test(board,4) == 328511);
    //board.undoMove();

    /*board.makeMove({Square::E2, Square::E3});
    CHECK(perft_test(board,4) == 402988);
    board.undoMove();

    board.makeMove({Square::F2, Square::F3});
    CHECK(perft_test(board,4) == 178889);
    board.undoMove();

    board.makeMove({Square::G2, Square::G3});
    CHECK(perft_test(board,4) == 217210);
    board.undoMove();

    board.makeMove({Square::H2, Square::H3});
    CHECK(perft_test(board,4) == 181044);
    board.undoMove();

    board.makeMove({Square::A2, Square::A4, 1});
    CHECK(perft_test(board,4) == 217832);
    board.undoMove();

    board.makeMove({Square::B2, Square::B4, 1});
    CHECK(perft_test(board,4) == 216145);
    board.undoMove();

    board.makeMove({Square::C2, Square::C4, 1});
    CHECK(perft_test(board,4) == 240082);
    board.undoMove();

    board.makeMove({Square::D2, Square::D4, 1});
    CHECK(perft_test(board,4) == 361790);
    board.undoMove();

    board.makeMove({Square::E2, Square::E4, 1});
    CHECK(perft_test(board,4) == 405385);
    board.undoMove();

    board.makeMove({Square::F2, Square::F4, 1});
    CHECK(perft_test(board,4) == 198473);
    board.undoMove();

    board.makeMove({Square::G2, Square::G4, 1});
    CHECK(perft_test(board,4) == 214048);
    board.undoMove();

    board.makeMove({Square::H2, Square::H4, 1});
    CHECK(perft_test(board,4) == 218829);
    board.undoMove();

    board.makeMove({Square::B1, Square::A3});
    CHECK(perft_test(board,4) == 198572);
    board.undoMove();

    board.makeMove({Square::B1, Square::C3});
    CHECK(perft_test(board,4) == 234656);
    board.undoMove();

    board.makeMove({Square::G1, Square::F3});
    CHECK(perft_test(board,4) == 233491);
    board.undoMove();

    board.makeMove({Square::G1, Square::H3});
    CHECK(perft_test(board,4) == 198502);
    board.undoMove();*/


}

/*TEST_CASE("Check moves from d2d3 b7b5") {
    Board board = Board();

    board.makeMove({Square::D2, Square::D3});
    board.makeMove({Square::B7, Square::B5,1});


    board.makeMove({Square::A2, Square::A3});
    CHECK(perft_test(board,2) == 545);
    board.undoMove();

    board.makeMove({Square::B2, Square::B3});
    CHECK(perft_test(board,2) == 586);
    board.undoMove();

    board.makeMove({Square::C2, Square::C3});
    CHECK(perft_test(board,2) == 587);
    board.undoMove();

    board.makeMove({Square::E2, Square::E3});
    CHECK(perft_test(board,2) == 608);
    board.undoMove();

    board.makeMove({Square::F2, Square::F3});
    CHECK(perft_test(board,2) == 544);
    board.undoMove();

    board.makeMove({Square::G2, Square::G3});
    CHECK(perft_test(board,2) == 586);
    board.undoMove();

    board.makeMove({Square::H2, Square::H3});
    CHECK(perft_test(board,2) == 544);
    board.undoMove();

    board.makeMove({Square::D3, Square::D4});
    CHECK(perft_test(board,2) == 587);
    board.undoMove();

    board.makeMove({Square::A2, Square::A4, 1});
    CHECK(perft_test(board,2) == 633);
    board.undoMove();

    board.makeMove({Square::B2, Square::B4, 1});
    CHECK(perft_test(board,2) == 541);
    board.undoMove();

    board.makeMove({Square::C2, Square::C4, 1});
    CHECK(perft_test(board,2) == 656);
    board.undoMove();

    board.makeMove({Square::E2, Square::E4, 1});
    CHECK(perft_test(board,2) == 692);
    board.undoMove();

    board.makeMove({Square::F2, Square::F4, 1});
    CHECK(perft_test(board,2) == 504);
    board.undoMove();

    board.makeMove({Square::G2, Square::G4, 1});
    CHECK(perft_test(board,2) == 587);
    board.undoMove();

    board.makeMove({Square::H2, Square::H4, 1});
    CHECK(perft_test(board,2) == 586);
    board.undoMove();

    board.makeMove({Square::B1, Square::D2});
    CHECK(perft_test(board,2) == 482);
    board.undoMove();

    board.makeMove({Square::B1, Square::A3});
    CHECK(perft_test(board,2) == 544);
    board.undoMove();

    board.makeMove({Square::B1, Square::C3});
    CHECK(perft_test(board,2) == 586);
    board.undoMove();

    board.makeMove({Square::G1, Square::F3});
    CHECK(perft_test(board,2) == 628);
    board.undoMove();

    board.makeMove({Square::G1, Square::H3});
    CHECK(perft_test(board,2) == 565);
    board.undoMove();

    board.makeMove({Square::C1, Square::D2});
    CHECK(perft_test(board,2) == 585);
    board.undoMove();

    board.makeMove({Square::C1, Square::E3});
    CHECK(perft_test(board,2) == 626);
    board.undoMove();

    board.makeMove({Square::C1, Square::F4});
    CHECK(perft_test(board,2) == 648);
    board.undoMove();

    board.makeMove({Square::C1, Square::G5});
    CHECK(perft_test(board,2) == 619);
    board.undoMove();

    board.makeMove({Square::C1, Square::H6});
    CHECK(perft_test(board,2) == 565);
    board.undoMove();

    board.makeMove({Square::D1, Square::D2});
    CHECK(perft_test(board,2) == 585);
    board.undoMove();

    board.makeMove({Square::E1, Square::D2});
    CHECK(perft_test(board,2) == 481);
    board.undoMove();

}*/

/*TEST_CASE("Check moves from d2d3 b7b5 e1d2") {
    Board board = Board();

    board.makeMove({Square::D2, Square::D3});
    board.makeMove({Square::B7, Square::B5,1});
    board.makeMove({Square::E1, Square::D2});

    board.makeMove({Square::B5, Square::B4});
    CHECK(perft_test(board,1) == 21);
    board.undoMove();

    /*board.makeMove({Square::A7, Square::A6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::C7, Square::C6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::D7, Square::D6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::E7, Square::E6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::F7, Square::F6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::G7, Square::G6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::H7, Square::H6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::A7, Square::A5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::C7, Square::C5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::D7, Square::D5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::E7, Square::E5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::F7, Square::F5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::G7, Square::G5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::H7, Square::H5, 1});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::B8, Square::A6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::B8, Square::C6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::G8, Square::F6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::G8, Square::H6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();
    board.makeMove({Square::C8, Square::A6});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

    board.makeMove({Square::C8, Square::B7});
    CHECK(perft_test(board,1) == 23);
    board.undoMove();

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
*/

TEST_CASE("Check position including castling rules") {
    Board board();
}

//TEST_CASE("Starting positions and divide") {
//    perft_test_divide();
//}


