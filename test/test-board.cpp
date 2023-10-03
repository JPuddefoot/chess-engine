#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <Board.h>

#include <utils.h>
#include <Move.h>

TEST_CASE("Check Board correctly initialised") {
    Board board = Board();

    // Check white is to move
    CHECK(board.whiteToMove == true);

    // Check knights in correct place
    CHECK(board.boardArray[static_cast<int>(Square::B1)]->getName() == "N");
    CHECK(board.boardArray[static_cast<int>(Square::G1)]->getName() == "N");

    // Check Kings in correct place
    CHECK(board.boardArray[static_cast<int>(Square::E1)]->getName() == "K");
    CHECK(board.boardArray[static_cast<int>(Square::E8)]->getName() == "k");
    CHECK(board.whitePieces.test(static_cast<int>(Square::E1)));
    CHECK(board.blackPieces.test(static_cast<int>(Square::E8)));

}

TEST_CASE("Check can move white piece") {
    Board board = Board();

    // Generate starting moves for white and make a move
    board.generateMoves();
    Move move = board.nextMoveList[2];
    board.makeMove(move);

    // Check boardArray has updated
    CHECK(board.boardArray[static_cast<int>(move.origin)] == nullptr);
    CHECK(board.boardArray[static_cast<int>(move.destination)] != nullptr);

    // Check whitePieces bitboard has updated
    CHECK(!board.whitePieces[static_cast<int>(move.origin)]);
    CHECK(board.whitePieces[static_cast<int>(move.destination)]);

    // Check whiteToMove is now false
    CHECK(!board.whiteToMove);

    // Generate moves for black and make a move
    board.generateMoves();
    Move move_black = board.nextMoveList[2];
    board.makeMove(move_black);

    // Check whitePieces bitboard has stayed the same
    CHECK(!board.whitePieces[static_cast<int>(move.origin)]);
    CHECK(board.whitePieces[static_cast<int>(move.destination)]);

}

TEST_CASE("Check can take pieces") {
    Board board = Board();

    // Move pieces such that white will have a pawn on e5 that can take a pawn
    // d6 and check this move is allowed
    board.makeMove(Move{Square::E2, Square::E4});
    board.makeMove(Move{Square::D7, Square::D5});

    board.generateMoves();

    Move testMoveWhite = Move({Square::E4, Square::D5});

    // Check capturing move is in nextMoveList
    bool moveIsIn = false;
    for (Move move : board.nextMoveList) {
        if (move == testMoveWhite)
            moveIsIn = true;
    }
    CHECK(moveIsIn);

    // Capture and check that black piece is removed from board

    board.makeMove(Move{Square::E4, Square::D5});

    CHECK(!board.blackPieces[static_cast<int>(Square::D5)]);
    CHECK(!board.capturedBlackPieces.empty());

    if (!board.capturedBlackPieces.empty())
        CHECK(board.capturedBlackPieces.back()->getName() == "p");

}

TEST_CASE("Check enPassant moves") {



    SECTION("Check basic en passant for white") {
        // Move pieces so white will have an en passant option
        Board board = Board();
        board.makeMove(Move{Square::E2, Square::E4});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::E4, Square::E5});
        board.makeMove(Move{Square::F7, Square::F5, 1});



        board.generateMoves();

       // for (Move move : board.nextMoveList) {
       //     std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
       // }

       // std::cout << board.printBoard();

        Move testMoveWhite = Move({Square::E5, Square::F6});
        // Check capturing move is in nextMoveList
        bool moveIsIn = false;
        for (Move move : board.nextMoveList) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn);
    }

    SECTION("Check can undo an enpassant move") {
        Board board = Board();
        board.makeMove(Move{Square::E2, Square::E4});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::E4, Square::E5});
        board.makeMove(Move{Square::F7, Square::F5, 1});
    }

    /*SECTION("Check en passant not an option if after first move") {
        // Move pieces so white will have an en passant option
        board.makeMove(Move{Square::E2, Square::E4});
        board.makeMove(Move{Square::D7, Square::D5});
        board.makeMove(Move{Square::E4, Square::E5});
        board.makeMove(Move{Square::F7, Square::F5});
        board.makeMove(Move{Square::A2, Square::A4});
        board.makeMove(Move{Square::H7, Square::H5});

        board.generateMoves();

        Move testMoveWhite = Move({Square::E5, Square::F6});
        // Check capturing move is in nextMoveList
        bool moveIsIn = false;
        for (Move move : board.nextMoveList) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(!moveIsIn);*/

    //}
}

TEST_CASE("Check kings don't move into pawn capture") {

    SECTION("WHite king black pawn on left") {
        Board board = Board();

        board.makeMove({Square::D2, Square::D3});
        board.makeMove({Square::B7, Square::B5,1});
        board.makeMove({Square::E1, Square::D2});

        board.makeMove({Square::B5, Square::B4});
        board.generateMoves();
        CHECK(board.nextMoveList.size() == 21);
    }

    SECTION("White king black pawn on right") {
        Board board = Board();

        board.makeMove({Square::D2, Square::D3});
        board.makeMove({Square::F7, Square::F5, 1});
        board.makeMove({Square::E1, Square::D2});
        board.makeMove({Square::F5, Square::F4});
        board.generateMoves();
        CHECK(board.nextMoveList.size() == 21);

    }

}

TEST_CASE("Check castles") {

}

TEST_CASE("Check promotions") {

}

