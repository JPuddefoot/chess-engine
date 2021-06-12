#include <catch2/catch.hpp>

#include <vector>
#include <iostream>
#include <string>

#include <RookLookup.h>

#include <utils.h>
#include <Move.h>

TEST_CASE("Test generateRookBlockerMask") {
    SECTION("For Rook on D4") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::D3, Square::D2, Square::D5, Square::D6, Square::D7,
            Square::B4, Square::C4, Square::E4, Square::F4, Square::G4
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::D4);

        CHECK(correctBlocker == blockerMask);
    }
    SECTION("For Rook on A1 - Different behaviour at corners") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::A2, Square::A3, Square::A4, Square::A5, Square::A6,
            Square::A7, Square::B1, Square::C1, Square::D1, Square::E1,
            Square::F1, Square::G1
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::A1);
        CHECK(correctBlocker == blockerMask);
    }
    SECTION("For Rook on A8") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::A2, Square::A3, Square::A4, Square::A5, Square::A6,
            Square::A7, Square::B8, Square::C8, Square::D8, Square::E8,
            Square::F8, Square::G8
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::A8);
        CHECK(correctBlocker == blockerMask);
    }
    SECTION("For Rook on H1") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::H2, Square::H3, Square::H4, Square::H5, Square::H6,
            Square::H7, Square::B1, Square::C1, Square::D1, Square::E1,
            Square::F1, Square::G1
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::H1);
        CHECK(correctBlocker == blockerMask);
    }
    SECTION("For Rook on H8") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::H2, Square::H3, Square::H4, Square::H5, Square::H6,
            Square::H7, Square::B8, Square::C8, Square::D8, Square::E8,
            Square::F8, Square::G8
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::H8);
        CHECK(correctBlocker == blockerMask);
    }
    SECTION("For Rook on A7") {
        bitboard_t correctBlocker = generateBitboard(std::vector<Square>{
            Square::A2, Square::A3, Square::A4, Square::A5, Square::A6,
            Square::B7, Square::C7, Square::D7, Square::E7,
            Square::F7, Square::G7
        });
        bitboard_t blockerMask = generateRookBlockerMask(Square::A7);
        CHECK(correctBlocker == blockerMask);
    }
}


TEST_CASE("Test generation of BlockerBoards") {
    // Should be 2^no.bits different boards for each square, so
    // should be 4096 for corner cases, 2048 for edge cases and
    // 1024 for everything else
    SECTION("Checks for normal squares") {
        // E5
        size_t numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::E5)).size();
        CHECK(numBoards == 1024);
        // B2
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::E5)).size();
        CHECK(numBoards == 1024);
    }
    SECTION("Checks for edge cases") {
        // A2
        size_t numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::A2)).size();
        CHECK(numBoards == 2048);
        // H7
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::H7)).size();
        CHECK(numBoards == 2048);
        // B8
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::B8)).size();
        CHECK(numBoards == 2048);
        // F1
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::F1)).size();
        CHECK(numBoards == 2048);
    }
    SECTION("Checks for corner cases") {
        // A1
        size_t numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::A1)).size();
        CHECK(numBoards == 4096);
        // H1
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::H1)).size();
        CHECK(numBoards == 4096);
        // A8
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::A8)).size();
        CHECK(numBoards == 4096);
        // H8
        numBoards = generateBlockerBoards(generateRookBlockerMask(
        Square::H8)).size();
        CHECK(numBoards == 4096);
    }

}

TEST_CASE("Test generation of move board for given blockerBoard") {
    SECTION("Rook on A1") {
        // first blockerBoard
        bitboard_t BlockerBoard = generateBitboard(std::vector<Square>{
            Square::A5, Square::A7});
        bitboard_t correctMoveBoard = generateBitboard(std::vector<Square>{
            Square::A2, Square::A3, Square::A4, Square::B1, Square::C1,
            Square::D1, Square::E1, Square::F1, Square::G1, Square::H1
        });
        CHECK(correctMoveBoard == generateRookMoveBoard(BlockerBoard,
            Square::A1));

        // Second blockerboard
        BlockerBoard = generateBitboard(std::vector<Square>{
            Square::A8, Square::B1});
        correctMoveBoard = generateBitboard(std::vector<Square>{
            Square::A2, Square::A3, Square::A4, Square::A5, Square::A6,
            Square::A7
        });
        CHECK(correctMoveBoard == generateRookMoveBoard(BlockerBoard,
            Square::A1));
    }
}