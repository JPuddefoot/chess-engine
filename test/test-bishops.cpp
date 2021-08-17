#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <BishopLookup.h>

#include <utils.h>
#include <Move.h>


TEST_CASE("Test bishopMask generation") {
    SECTION("For Bishop on A1") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::B2, Square::C3, Square::D4, Square::E5, Square::F6,
            Square::G7
        });
        bitboard_t blockerMask = BishopLookup::bishopMask(Square::A1);

        CHECK(correctBlocker == blockerMask);
    }

    SECTION("For Bishop on E4") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::D5, Square::C6, Square::B7, Square::F3, Square::G2,
            Square::F5, Square::G6, Square::D3, Square::C2
        });
        bitboard_t blockerMask = BishopLookup::bishopMask(Square::E4);

        CHECK(correctBlocker == blockerMask);
    }
}