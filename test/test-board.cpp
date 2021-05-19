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
    CHECK(board.boardArray[static_cast<int>(Square::E8)]->getName() == "K");
    CHECK(board.whitePieces.test(static_cast<int>(Square::E1)));
    CHECK(board.blackPieces.test(static_cast<int>(Square::E8)));

}

TEST_CASE("Check can move white piece") {
    Board board = Board();

    // Generate starting moves for white and make a move
    board.generateMoves();
    Move move = board.moveList[2];
    board.makeMove(move.origin, move.destination);

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
    Move move_black = board.moveList[2];
    board.makeMove(move_black.origin, move_black.destination);

    // Check whitePieces bitboard has stayed the same
    CHECK(!board.whitePieces[static_cast<int>(move.origin)]);
    CHECK(board.whitePieces[static_cast<int>(move.destination)]);

}

TEST_CASE("Check can take pieces") {
    Board board = Board();

    // Move pieces such that white will have a pawn on e5 that can take a pawn
    // d6 and check this move is allowed
    board.makeMove(Square::E2, Square::E4);
    board.makeMove(Square::D7, Square::D5);

    board.generateMoves();

    Move testMoveWhite = Move({Square::E4, Square::D5});

    // Check capturing move is in moveList
    bool moveIsIn = false;
    for (Move move : board.moveList) {
        if (move == testMoveWhite)
            moveIsIn = true;
    }
    CHECK(moveIsIn);

    // Capture and check that black piece is removed from board

    board.makeMove(Square::E4, Square::D5);

    CHECK(!board.blackPieces[static_cast<int>(Square::D5)]);

}