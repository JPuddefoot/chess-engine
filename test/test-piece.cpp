#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <King.h>
#include <Pawns.h>
#include <Knight.h>

#include <utils.h>
#include <Move.h>

TEST_CASE("Check makeMove") {

    SECTION("Moving Kings") {
        King whiteKing = King(Color::White);
        whiteKing.makeMove(Square::E1, Square::F3);

        bitboard_t whiteKingTestPos = generateBitboard(std::vector<Square>{
            Square::F3});

        CHECK(whiteKing.currentPos == whiteKingTestPos);
    }
}

TEST_CASE("Check capturePiece") {
    Pawns blackPawns = Pawns(Color::Black);
    blackPawns.capturePiece(Square::G7);

    bitboard_t bPawnsTestPos1 = generateBitboard(std::vector<Square>{
        Square::A7, Square::B7, Square::C7, Square::D7, Square::E7, Square::F7,
        Square::H7});

    CHECK(blackPawns.currentPos == bPawnsTestPos1);

    blackPawns.capturePiece(Square::A7);

    bitboard_t bPawnsTestPos2 = generateBitboard(std::vector<Square>{
        Square::B7, Square::C7, Square::D7, Square::E7, Square::F7, Square::H7});

    CHECK(blackPawns.currentPos == bPawnsTestPos2);
}

TEST_CASE("Check addPiece") {
    Knights whiteKnights = Knights(Color::White);
    whiteKnights.addPiece(Square::B3);

    bitboard_t whiteKnightsTestPos1 = generateBitboard(std::vector<Square>{
        Square::B1, Square::G1, Square::B3});

    CHECK(whiteKnights.currentPos == whiteKnightsTestPos1);

    whiteKnights.addPiece(Square::A8);

    bitboard_t whiteKnightsTestPos2 = generateBitboard(std::vector<Square>{
        Square::B1, Square::B3, Square::G1, Square::A8});

    CHECK(whiteKnights.currentPos == whiteKnightsTestPos2);
}