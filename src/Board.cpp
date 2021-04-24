#include <Board.h>
#include <iostream>

// Initialise board:
//
//    - fill board_array with normal starting positions
Board::Board() {

    // White Pieces
    boardArray[static_cast<int>(Square::E1)] = &whiteKing;
    boardArray[static_cast<int>(Square::B1)] = &whiteKnights;
    boardArray[static_cast<int>(Square::G1)] = &whiteKnights;
    boardArray[static_cast<int>(Square::A2)] = &whitePawns;
    boardArray[static_cast<int>(Square::B2)] = &whitePawns;
    boardArray[static_cast<int>(Square::C2)] = &whitePawns;
    boardArray[static_cast<int>(Square::D2)] = &whitePawns;
    boardArray[static_cast<int>(Square::E2)] = &whitePawns;
    boardArray[static_cast<int>(Square::F2)] = &whitePawns;
    boardArray[static_cast<int>(Square::G2)] = &whitePawns;
    boardArray[static_cast<int>(Square::H2)] = &whitePawns;

    // Black Pieces
    boardArray[static_cast<int>(Square::E8)] = &blackKing;
    boardArray[static_cast<int>(Square::B8)] = &blackKnights;
    boardArray[static_cast<int>(Square::G8)] = &blackKnights;
    boardArray[static_cast<int>(Square::A7)] = &blackPawns;
    boardArray[static_cast<int>(Square::B7)] = &blackPawns;
    boardArray[static_cast<int>(Square::C7)] = &blackPawns;
    boardArray[static_cast<int>(Square::D7)] = &blackPawns;
    boardArray[static_cast<int>(Square::E7)] = &blackPawns;
    boardArray[static_cast<int>(Square::F7)] = &blackPawns;
    boardArray[static_cast<int>(Square::G7)] = &blackPawns;
    boardArray[static_cast<int>(Square::H7)] = &blackPawns;


}

Move Board::makeMove(Square origin, Square destination) {
    Piece* piece_to_move = boardArray[static_cast<int>(origin)];
    piece_to_move->makeMove(origin, destination);
    boardArray[static_cast<int>(destination)] = piece_to_move;
    boardArray[static_cast<int>(origin)] = nullptr;
    return Move{origin, destination};
}


std::string Board::printBoard() {
    std::stringstream ss;
    ss << "\n";
    for (int row=0; row<=7; row++) {
        for (int col=7; col>=0; col--) {
            std::string marker = ".";
            Piece* piece = boardArray[row*8 + col];
            if (piece) {
                marker = piece->getName();
            }

            ss << marker << " ";
        }
        ss << "\n";
    }
    ss << "\n";
    return ss.str();
}