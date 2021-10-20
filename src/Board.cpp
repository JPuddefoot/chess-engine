#include <Board.h>
#include <iostream>

// Initialise board:
//
//    - fill board_array with normal starting positions
//    - Create initial positions in white/black pieces bitboard
Board::Board() {

    whiteToMove = true;

    // White Pieces
    boardArray[static_cast<int>(Square::E1)] = &whiteKing;
    boardArray[static_cast<int>(Square::C1)] = &whiteBishops;
    boardArray[static_cast<int>(Square::F1)] = &whiteBishops;
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
    whitePieces = generateBitboard(std::vector<Square>{
      Square::E1, Square::F1, Square::C1, Square::B1, Square::G1,
      Square::A2, Square::B2, Square::C2,
      Square::D2, Square::E2, Square::F2, Square::G2, Square::H2});

    // Black Pieces
    boardArray[static_cast<int>(Square::E8)] = &blackKing;
    boardArray[static_cast<int>(Square::C8)] = &blackBishops;
    boardArray[static_cast<int>(Square::F8)] = &blackBishops;
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
    blackPieces = generateBitboard(std::vector<Square>{
      Square::E8, Square::C8, Square::F8, Square::B8, Square::G8, Square::A7, Square::B7, Square::C7,
      Square::D7, Square::E7, Square::F7, Square::G7, Square::H7});


}

void Board::generateMoves() {

    // Reset moveList
    moveList.clear();

    // Only generate moves for whose turn it is
    switch (whiteToMove) {
        case true:
            whiteKing.generateMoves(whitePieces, blackPieces, moveList);
            whitePawns.generateMoves(whitePieces, blackPieces, moveList);
            whiteKnights.generateMoves(whitePieces, blackPieces, moveList);
            whiteBishops.generateMoves(whitePieces, blackPieces, moveList);
            break;

        case false:
            blackKing.generateMoves(whitePieces, blackPieces, moveList);
            blackPawns.generateMoves(whitePieces, blackPieces, moveList);
            blackKnights.generateMoves(whitePieces, blackPieces, moveList);
            blackBishops.generateMoves(whitePieces, blackPieces, moveList);
            break;
    }
}

Move Board::makeMove(Square origin, Square destination) {

    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);

    // Find the piece to be moved on boardArray and relevant bitboard
    Piece* piece_to_move = boardArray[static_cast<int>(origin)];
    bitboard_t * board_to_move = (whiteToMove) ? &whitePieces : &blackPieces;

    // Check a piece exists for both - if not then throw error

    bool validMove = (piece_to_move && board_to_move->test(bit_origin));
    if (!validMove) {
        throw std::runtime_error("No piece of color at origin square: " +
            Square_array[bit_origin] + "\n");
    }


    // Make the piece move
    piece_to_move->makeMove(origin, destination);
    // Update the current bitboard for origin/destination
    board_to_move->flip(bit_origin);
    board_to_move->flip(bit_destination);

    // Have temp pointer to current piece if any on destination
    Piece * piece_at_dest = boardArray[static_cast<int>(destination)];

    // Update the boardArray with the new position - overwrites old piece
    boardArray[static_cast<int>(destination)] = piece_to_move;
    boardArray[static_cast<int>(origin)] = nullptr;

    // If piece was destination, tell it it has been captured

    if (piece_at_dest) {
        piece_at_dest->capturePiece(destination);
    }

    // If piece of other type was captured, update other board
    bitboard_t * captured_board = (!whiteToMove) ? &whitePieces : &blackPieces;
    if (captured_board->test(bit_destination)) {
        captured_board->flip(bit_destination);
    }


    // Change who's move it is
    whiteToMove = !whiteToMove;
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