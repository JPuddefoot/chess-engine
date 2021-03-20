#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <Knight.h>

#include <utils.h>
#include <Move.h>


TEST_CASE("Check knights start in correct place for white and black") {
    Knights whiteKnights = Knights(Color::White);
    Knights blackKnights = Knights(Color::Black);

    bitboard_t whiteStart = generateBitboard(std::vector<Square>{
        Square::B1, Square::G1});

    bitboard_t blackStart = generateBitboard(std::vector<Square>{
        Square::B8, Square::G8});

    CHECK(whiteKnights.currentPos == whiteStart);
    CHECK(blackKnights.currentPos == blackStart);

}

TEST_CASE(std::string("Check knights can land on squares with opposing") +
    "color piece and can't land on square with same color piece") {

    Knights whiteKnights = Knights(Color::White);
    Knights blackKnights = Knights(Color::Black);

    std::vector<Move> moveListBlack = {};
    std::vector<Move> moveListWhite = {};

    bitboard_t white_pieces = generateBitboard(std::vector<Square>{
        Square::F6, Square::A3});
    bitboard_t black_pieces = generateBitboard(std::vector<Square>{
        Square::D2, Square::H6});

    whiteKnights.generateMoves(white_pieces, black_pieces, moveListWhite);
    blackKnights.generateMoves(white_pieces, black_pieces, moveListBlack);

    // Check white knight move to square with black piece is allowed
    bool moveIsIn = false;
    Move testmoveWhite = Move{Square::B1, Square::D2};

    for (Move move : moveListWhite) {
        if (move == testmoveWhite)
            moveIsIn = true;
    }
    CHECK(moveIsIn == true);

    // Check black knight move to square with white piece allowed
    moveIsIn = false;
    Move testmoveBlack = Move{Square::G8, Square::F6};
    for (Move move : moveListBlack) {
        if (move == testmoveBlack)
            moveIsIn = true;
    }
    CHECK(moveIsIn == true);

    // Check white knight cant move to square with white piece
    moveIsIn = false;
    Move testmoveWhite2 = Move{Square::B1, Square::A3};

    for (Move move : moveListWhite) {
        if (move == testmoveWhite2)
            moveIsIn = true;
    }
    CHECK(moveIsIn == false);

    // Check black knight can't move to square with black piece
    moveIsIn = false;
    Move testmoveBlack2 = Move{Square::G8, Square::H6};

    for (Move move : moveListBlack) {
        if (move == testmoveBlack2)
            moveIsIn = true;
    }
    CHECK(moveIsIn == false);




}

