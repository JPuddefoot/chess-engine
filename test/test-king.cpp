#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <King.h>

#include <utils.h>
#include <Move.h>


/*TEST_CASE("Check King starts in correct place") {
    King whiteKing = King(Color::White);
    King blackKing = King(Color::Black);

    bitboard_t white_start = generateBitboard(std::vector<Square>{Square::E1});
    bitboard_t black_start = generateBitboard(std::vector<Square>{Square::E8});

    CHECK(whiteKing.currentPos == white_start);
    CHECK(blackKing.currentPos == black_start);
}

TEST_CASE("Check Kings can take opposite color and not same color") {
    King whiteKing = King(Color::White);
    King blackKing = King(Color::Black);

    std::vector<Move> moveListWhite = {};
    std::vector<Move> moveListBlack = {};

    bitboard_t white_pieces = (whiteKing.currentPos |= generateBitboard(
        std::vector<Square>{Square::D1, Square::E7}));

    bitboard_t black_pieces = (blackKing.currentPos |= generateBitboard(
        std::vector<Square>{Square::D2, Square::F8}));

    whiteKing.generateMoves(white_pieces, black_pieces, moveListWhite);
    blackKing.generateMoves(white_pieces, black_pieces, moveListBlack);

    bool moveIsIn = false;

    SECTION("Check White King can take black piece") {
        Move testMoveWhite = Move{Square::E1, Square::D2};
        for (Move move : moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check white King can't take white piece") {
        Move testMoveWhite = Move{Square::E1, Square::D1};
        for (Move move : moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check black King can take white piece") {
        Move testMoveBlack = Move{Square::E8, Square::E7};
        for (Move move : moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check black King can't take black piece") {
        Move testMoveBlack = Move{Square::E8, Square::F8};
        for (Move move : moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }
}*/