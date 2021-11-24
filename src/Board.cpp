#include <Board.h>
#include <iostream>

// Initialise board:
//
//    - fill board_array with normal starting positions
//    - Create initial positions in white/black pieces bitboard
Board::Board() {

    whiteToMove = true;

    // Have to fill Rook Attack table here
    RookLookup::fillAttackTable();

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
      Square::A1, Square::B1, Square::C1, Square::D1, Square::E1, Square::F1,
      Square::G1, Square::H1, Square::A2, Square::B2, Square::C2, Square::D2,
      Square::E2, Square::F2, Square::G2, Square::H2});

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
      Square::A8, Square::B8, Square::C8, Square::D8, Square::E8, Square::F8,
      Square::G8, Square::H8, Square::A7, Square::B7, Square::C7, Square::D7,
      Square::E7, Square::F7, Square::G7, Square::H7});


}

void Board::generateMoves() {

    // Reset moveList
    nextMoveList.clear();

    std::vector<Move> pseudoLegalMoves = {};

    // Only generate moves for whose turn it is
    switch (whiteToMove) {
        case true:
            whiteKing.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            whiteQueens.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            whitePawns.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            whiteKnights.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            whiteBishops.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            whiteRooks.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            break;

        case false:
            blackKing.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            blackQueens.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            blackPawns.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            blackKnights.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            blackBishops.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            blackRooks.generateMoves(whitePieces, blackPieces, pseudoLegalMoves);
            break;
    }
    for (const Move& move : pseudoLegalMoves) {
        if (checkLegalMove(move)) {
            nextMoveList.push_back(move);
        }
    }
}

Move Board::makeMove(Move move) {

    Square origin = move.origin;
    Square destination = move.destination;

    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    uint16_t info = 0;

    // Find the piece to be moved on boardArray and relevant bitboard
    Piece* piece_to_move = boardArray[static_cast<int>(origin)];
    bitboard_t * board_to_move = (whiteToMove) ? &whitePieces : &blackPieces;

    // Check a piece exists for both - if not then throw error

    bool validMove = (piece_to_move && board_to_move->test(bit_origin));
    if (!validMove) {
        std::string colorToMove = (whiteToMove) ? "White" : "Black";
        throw std::runtime_error("No piece of color: " + colorToMove + " at origin square: " +
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
    move.info = info;

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
        std::string colorToMove = (whiteToMove) ? "White" : "Black";
        throw std::runtime_error("No piece of color: " + colorToMove + " at origin square: " +
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
        board_to_add->flip(bit_origin); // Only flip square where piece added

        // Add piece pointer onto boardArray
        boardArray[bit_origin] = capturedPiece;
    }

    return lastMove;
}

// Check that a possible move is legal - i.e move doesn't leave/put king in check
bool Board::checkLegalMove(const Move& move) {
    // First make the proposed move, then check if the king is still in check.
    // This is done by checking if a piece is in the right place to take it -
    // e.g check all open diagonals and if a oppposite queen or bishop is there
    // then the king is still in check.
    // This should be quicker than making the move, generating all possible moves for the opponent
    // and checking if the king was taken

    makeMove(move);

    // Get the king bitboard for the color that just made the test move
    // Remember that making move switched the color to move - i.e if white
    // made the last move then whiteToMove is false
    bitboard_t king_board = (whiteToMove) ? blackKing.currentPos : whiteKing.currentPos;

    int king_square;
    // Get the kings position from the bitboard
    for (std::size_t bit=0; bit<king_board.size(); bit++) {
        if (king_board.test(bit)) {
            king_square = bit;
        }
    }

    // Rank and file of king position
    int rank = king_square/8;
    int file = king_square % 8;

    // Get bitboard of blocking pieces or attacking pieces depending on whose moving
    uint64_t blocking = (whiteToMove) ? blackPieces.to_ulong() : whitePieces.to_ulong();
    uint64_t attacking = (whiteToMove) ? whitePieces.to_ulong() : blackPieces.to_ulong();

    // check diagonals

    auto passesDiagonalChecks = [&] ()->bool {
        for (int r = rank+1, f = file+1, blocks=0; r<=7 && f<=7 && blocks<1; r++, f++) {
            if (blocking & (1ULL << (f + r*8)))
                // If there is a piece blocking then the king is not currently in check
                blocks++;
            else if (attacking & (1ULL << (f + r*8))) {
                // Need to check if diagonal enemy piece is queen or bishop
                // If it is then king is in check, else break and check next diagonal
                std::string pieceType = boardArray[f+r*8]->getName();
                if (pieceType == "B" || pieceType == "Q" )
                    return false;
                else
                    break;
            }

        }
        for (int r = rank+1, f = file-1, blocks=0; r<=7 && f>=0 && blocks<1; r++, f--) {
            if (blocking & (1ULL << (f + r*8)))
                blocks++;
            else if (attacking & (1ULL << (f + r*8))) {
                // Need to check if diagonal enemy piece is queen or bishop
                std::string pieceType = boardArray[f+r*8]->getName();
                if (pieceType == "B" || pieceType == "Q" )
                    return false;
                else
                    break;
            }
        }
        for (int r = rank-1, f = file+1, blocks=0; r>=0 && f<=7 && blocks<1; r--, f++) {
            if (blocking & (1ULL << (f + r*8)))
                blocks++;
            else if (attacking & (1ULL << (f + r*8))) {
                // Need to check if diagonal enemy piece is queen or bishop
                std::string pieceType = boardArray[f+r*8]->getName();
                if (pieceType == "B" || pieceType == "Q" )
                    return false;
                else
                    break;
            }

        }
        for (int r = rank-1, f = file-1, blocks=0; r>=0 && f>=0 && blocks<1; r--, f--) {
            if (blocking & (1ULL << (f+r*8)))
                blocks++;
            else if (attacking & (1ULL << (f + r*8))) {
                // Need to check if diagonal enemy piece is queen or bishop
                std::string pieceType = boardArray[f+r*8]->getName();
                if (pieceType == "B" || pieceType == "Q" )
                    return false;
                else
                    break;
            }
        }

        return true;
    };

    auto passesKnightChecks = [&] () -> bool {
        // Get the possible positions a knight could be to check the king
        bitboard_t knight_attacks = whiteKnights.KnightLookup->at(king_square);
        bitboard_t enemy_knight_positions = (whiteToMove) ?
            whiteKnights.currentPos : blackKnights.currentPos;

        if ((knight_attacks & enemy_knight_positions).any()) {
            // There is a enemy knight giving a check, so cannot do move
            return false;
        }
        return true;

    };
    // Check en passant moves?

    bool isLegalMove = (passesKnightChecks() && passesDiagonalChecks());

    // Always have to undo move
    undoMove();

    return isLegalMove;

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