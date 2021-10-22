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
    boardArray[static_cast<int>(Square::D1)] = &whiteQueens;
    boardArray[static_cast<int>(Square::C1)] = &whiteBishops;
    boardArray[static_cast<int>(Square::F1)] = &whiteBishops;
    boardArray[static_cast<int>(Square::B1)] = &whiteKnights;
    boardArray[static_cast<int>(Square::G1)] = &whiteKnights;
    boardArray[static_cast<int>(Square::A1)] = &whiteRooks;
    boardArray[static_cast<int>(Square::H1)] = &whiteRooks;
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
      Square::A2, Square::B2, Square::C2, Square::A1, Square::H1,
      Square::D2, Square::E2, Square::F2, Square::G2, Square::H2,
      Square::D1});

    // Black Pieces
    boardArray[static_cast<int>(Square::E8)] = &blackKing;
    boardArray[static_cast<int>(Square::D8)] = &blackQueens;
    boardArray[static_cast<int>(Square::C8)] = &blackBishops;
    boardArray[static_cast<int>(Square::F8)] = &blackBishops;
    boardArray[static_cast<int>(Square::B8)] = &blackKnights;
    boardArray[static_cast<int>(Square::G8)] = &blackKnights;
    boardArray[static_cast<int>(Square::A8)] = &blackRooks;
    boardArray[static_cast<int>(Square::H8)] = &blackRooks;
    boardArray[static_cast<int>(Square::A7)] = &blackPawns;
    boardArray[static_cast<int>(Square::B7)] = &blackPawns;
    boardArray[static_cast<int>(Square::C7)] = &blackPawns;
    boardArray[static_cast<int>(Square::D7)] = &blackPawns;
    boardArray[static_cast<int>(Square::E7)] = &blackPawns;
    boardArray[static_cast<int>(Square::F7)] = &blackPawns;
    boardArray[static_cast<int>(Square::G7)] = &blackPawns;
    boardArray[static_cast<int>(Square::H7)] = &blackPawns;
    blackPieces = generateBitboard(std::vector<Square>{
      Square::E8, Square::C8, Square::F8, Square::B8, Square::G8,
      Square::A7, Square::B7, Square::C7, Square::D7, Square::E7,
      Square::F7, Square::G7, Square::H7, Square::A8, Square::H8, Square::D1});


}

void Board::generateMoves() {

    // Reset moveList
    nextMoveList.clear();

    // Only generate moves for whose turn it is
    switch (whiteToMove) {
        case true:
            whiteKing.generateMoves(whitePieces, blackPieces, nextMoveList);
            whiteQueens.generateMoves(whitePieces, blackPieces, nextMoveList);
            whitePawns.generateMoves(whitePieces, blackPieces, nextMoveList);
            whiteKnights.generateMoves(whitePieces, blackPieces, nextMoveList);
            whiteBishops.generateMoves(whitePieces, blackPieces, nextMoveList);
            break;

        case false:
            blackKing.generateMoves(whitePieces, blackPieces, nextMoveList);
            blackQueens.generateMoves(whitePieces, blackPieces, nextMoveList);
            blackPawns.generateMoves(whitePieces, blackPieces, nextMoveList);
            blackKnights.generateMoves(whitePieces, blackPieces, nextMoveList);
            blackBishops.generateMoves(whitePieces, blackPieces, nextMoveList);
            break;
    }
}

Move Board::makeMove(Square origin, Square destination) {

    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    uint16_t info = 0;

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


    //////////////
    // Captures //
    //////////////

    // Have temp pointer to current piece if any on destination
    Piece * piece_at_dest = boardArray[static_cast<int>(destination)];

    if (piece_at_dest) {
        // Need to add piece to correct capturedPieces list
        if (whiteToMove) {
            capturedBlackPieces.push_back(piece_at_dest);
        }
        else {
            capturedWhitePieces.push_back(piece_at_dest);
        }
        // Remove piece from piece bitboard
        piece_at_dest->capturePiece(destination);
        // Update the Move info to show a piece has been taken
        info |= 1UL << 2;

    }

    // If piece of other type was captured, update other board
    bitboard_t * captured_board = (!whiteToMove) ? &whitePieces : &blackPieces;
    if (captured_board->test(bit_destination)) {
        captured_board->flip(bit_destination);
    }

    // Update the boardArray with the new position - overwrites old piece
    boardArray[static_cast<int>(destination)] = piece_to_move;
    boardArray[static_cast<int>(origin)] = nullptr;

    //////////////////
    //////////////////

    // Change who's move it is
    whiteToMove = !whiteToMove;

    // update the Move with all needed values and add to move_history
    Move move = Move{origin, destination, info};

    moveHistory.push_back(move);
    return move;
}

Move Board::undoMove() {

    // Reset color to move to be the previous color that moved
    whiteToMove = !whiteToMove;

    // Get the last move in the move history, then remove it from vector
    Move lastMove = moveHistory.back();
    moveHistory.pop_back();

    // For undo Move, swap origin and destination
    Square origin = lastMove.destination;
    Square destination = lastMove.origin;

    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);

    // Find the piece to be moved on boardArray and relevant bitboard
    Piece * piece_to_move = boardArray[static_cast<int>(origin)];
    bitboard_t * board_to_move = (whiteToMove) ? &whitePieces : &blackPieces;

    bool validMove = (piece_to_move && board_to_move->test(bit_origin));
    if (!validMove) {
        throw std::runtime_error("No piece of color at origin square: " +
            Square_array[bit_origin] + "\n");
    }

    // Move the piece back to its previous position
    piece_to_move->makeMove(origin, destination);
    // Update the current bitboard for origin/destination
    board_to_move->flip(bit_origin);
    board_to_move->flip(bit_destination);

    // Update boardArray with new position
    boardArray[bit_destination] = piece_to_move;
    boardArray[bit_origin] = nullptr;

    // If there was a piece captured with the move, replace the captured piece
    // The 3rd bit in the info details if a piece was captured on that move
    if ((lastMove.info >> 2) & 1UL) {
        auto * capturedPieces = (whiteToMove) ? &capturedBlackPieces :
            &capturedWhitePieces;
        Piece* capturedPiece = capturedPieces->back();
        capturedPieces->pop_back();

        // Add a piece onto the piece bitboard and general bitboard
        capturedPiece->addPiece(origin);

        bitboard_t * board_to_add = (whiteToMove) ? &blackPieces : &whitePieces;
        board_to_move->flip(bit_origin); // Only flip square where piece added

        // Add piece pointer onto boardArray
        boardArray[bit_origin] = capturedPiece;
    }

    return lastMove;
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