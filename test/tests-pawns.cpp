#include <catch2/catch.hpp>

#include <iostream>
#include <vector>
#include <string>

#include <utils.h>
#include <Pawns.h>

TEST_CASE("Check Pawns can advance 1 square for white and black") {
    Pawns whitePawns = Pawns(Color::White);
    Pawns blackPawns = Pawns(Color::Black);

    std::vector<Move> moveListWhite = {};
    std::vector<Move> moveListBlack = {};

    bitboard_t white_pieces = (whitePawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::A3, Square::E6}));

    bitboard_t black_pieces = (blackPawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::G3, Square::H6}));

    whitePawns.generateMoves(white_pieces, black_pieces, moveListWhite);
    blackPawns.generateMoves(white_pieces, black_pieces, moveListBlack);

    bool moveIsIn = false;

    SECTION("Check white pawn can advance one square") {
        Move testMoveWhite = Move{Square::B2, Square::B3};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check white pawn with white blocker cannot advance one square") {
        Move testMoveWhite = Move{Square::A2, Square::A3};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check white pawn with black blocker cannot advance one square") {
        Move testMoveWhite = Move{Square::G2, Square::G3};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check that black pawn can advance one square") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::B7, Square::B6};
        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check black pawn with white blocker cannot advance one square") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::E7, Square::E6};
        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check black pawn with black blocker cannot advance one square") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::H7, Square::H6};
        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }
}

TEST_CASE("Check unmoved pawns can advance two unless blocked") {
    Pawns whitePawns = Pawns(Color::White);
    Pawns blackPawns = Pawns(Color::Black);

    std::vector<Move> moveListWhite = {};
    std::vector<Move> moveListBlack = {};

    bitboard_t white_pieces = (whitePawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::A3, Square::E6}));

    bitboard_t black_pieces = (blackPawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::G4, Square::H6}));

    whitePawns.generateMoves(white_pieces, black_pieces, moveListWhite);
    blackPawns.generateMoves(white_pieces, black_pieces, moveListBlack);
    bool moveIsIn = false;

    SECTION("Check white pawn advanced two squares") {
        Move testMoveWhite = Move{Square::B2, Square::B4};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check white pawn with white blocker has not moved two squares") {
        moveIsIn = false;
        Move testMoveWhite = Move{Square::A2, Square::A4};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check white pawn with black blocker has not moved two squares") {
        moveIsIn = false;
        Move testMoveWhite = Move{Square::G2, Square::G4};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check that black pawn advanced two square") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::B7, Square::B5};

        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check that black pawn with white blocker not moved two squares") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::E7, Square::E5};

        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check that black pawn with black blocker not moved two squares") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::H7, Square::H5};

        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }
}

TEST_CASE("Check pawns can take to the left") {
    Pawns whitePawns = Pawns(Color::White);
    Pawns blackPawns = Pawns(Color::Black);

    std::vector<Move> moveListWhite = {};
    std::vector<Move> moveListBlack = {};

    bitboard_t white_pieces = (whitePawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::A3, Square::E6}));

    bitboard_t black_pieces = (blackPawns.currentPos |= generateBitboard(
        std::vector<Square>{Square::G3, Square::C6}));

    whitePawns.generateMoves(white_pieces, black_pieces, moveListWhite);
    blackPawns.generateMoves(white_pieces, black_pieces, moveListBlack);
    bool moveIsIn = false;

    std::cout << bitboard_to_string(white_pieces);
    std::cout << bitboard_to_string(black_pieces);

    SECTION("Check white pawn can take black piece to left") {
        Move testMoveWhite = Move{Square::H2, Square::G3};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check white pawn can't take white piece to left") {
        moveIsIn = false;
        Move testMoveWhite = Move{Square::B2, Square::A3};
        for (Move move:moveListWhite) {
            if (move == testMoveWhite)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }

    SECTION("Check black pawn can take white piece to left") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::F7, Square::E6};
        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == true);
    }

    SECTION("Check black pawn can't take black piece to left") {
        moveIsIn = false;
        Move testMoveBlack = Move{Square::D7, Square::C6};
        for (Move move:moveListBlack) {
            if (move == testMoveBlack)
                moveIsIn = true;
        }
        CHECK(moveIsIn == false);
    }
}