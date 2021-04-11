#include <Board.h>
#include <iostream>

// Initialise board:
//
//    - fill board_array with normal starting positions
Board::Board() {

    // White Pieces
    boardArray[static_cast<int>(Square::E1)] = PieceType::wKing;
    boardArray[static_cast<int>(Square::B1)] = PieceType::wKnight;
    boardArray[static_cast<int>(Square::G1)] = PieceType::wKnight;
    boardArray[static_cast<int>(Square::A2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::B2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::C2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::D2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::E2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::F2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::G2)] = PieceType::wPawn;
    boardArray[static_cast<int>(Square::H2)] = PieceType::wPawn;

    // Black Pieces
    boardArray[static_cast<int>(Square::E8)] = PieceType::bKing;
    boardArray[static_cast<int>(Square::B8)] = PieceType::bKnight;
    boardArray[static_cast<int>(Square::G8)] = PieceType::bKnight;
    boardArray[static_cast<int>(Square::A7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::B7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::C7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::D7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::E7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::F7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::G7)] = PieceType::bPawn;
    boardArray[static_cast<int>(Square::H7)] = PieceType::bPawn;

}


std::string Board::printBoard() {
    std::stringstream ss;
    ss << "\n";
    for (int row=0; row<=7; row++) {
        for (int col=7; col>=0; col--) {
            std::string marker;
            switch (boardArray[row*8 + col]) {
                case PieceType::wKing:
                    marker = whiteKing.name;
                    break;
                case PieceType::bKing:
                    marker = blackKing.name;
                    break;
                default:
                    marker = ".";
            }
            ss << marker << " ";
        }
        ss << "\n";
    }
    ss << "\n";
    return ss.str();
}