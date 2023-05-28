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

    //std::cout << "gm1: " << printBoard() << "\n";

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

    //std::cout << "gm2: " << printBoard() << "\n";

    for (const Move& move : pseudoLegalMoves) {
        if (checkLegalMove(move)) {
            nextMoveList.push_back(move);
        }
    }

   // std::cout << "gm3: " << printBoard() << "\n";
}

Move Board::makeMove(Move move) { //todo - move can be &move?

    Square origin = move.origin;
    Square destination = move.destination;
    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    std::bitset<4> info{"0000"};

    // Find the piece to be moved on boardArray and the bitboard
    Piece* piece_to_move = boardArray[static_cast<int>(origin)];
    bitboard_t * board_to_move = (whiteToMove) ? &whitePieces : &blackPieces;

    bool validMove = (piece_to_move && board_to_move->test(bit_origin));
    if (!validMove) {
        std::string colorToMove = (whiteToMove) ? "White" : "Black";
        throw std::runtime_error("makeMove: No piece of color: " + colorToMove + " at origin square: " +
            Square_array[bit_origin] + "\n");
    }

    // If move is encoded as en passant (done by pawn class)
    if (move.info == 5) { // i.e 0101
        makeEnpassant(move);
    }
    else {
        // If move is encoded as a pawn promotion - TODO
        // if (move.info.at(0)) {
        //    makePromotion()
        //}

        // Check if capture move
        Piece* piece_at_dest = boardArray[bit_destination];
        if (piece_at_dest) {
            // update the opposing piece boards
            makeCapture(move, piece_at_dest);
            move.info = 4; // records that a capture occurs
        }
    }

    // Finalise move - move piece,bitboard and boardArray, add move to
    // history and change whose turn it is

    piece_to_move->makeMove(origin, destination);
    board_to_move->flip(bit_origin);
    board_to_move->flip(bit_destination);
    boardArray[bit_destination] = piece_to_move;
    boardArray[bit_origin] = nullptr;

    moveHistory.push_back(move);

    whiteToMove = !whiteToMove;
    //std::cout << "MoveBoard\n";
    //std::cout << printBoard() << "\n";


    return move;

}

/*Move Board::makeMove(Move move) {

    Square origin = move.origin;
    Square destination = move.destination;

    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    std::bitset<4> info{"0000"};

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
        info.set(1);

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
}*/

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
        for (Move move : moveHistory) {
            std::cout << "Move: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << "\n";
        }
        std::cout << "Move: " << Square_array[static_cast<int>(lastMove.origin)] << "to" << Square_array[static_cast<int>(lastMove.destination)] <<
            "Info: " << lastMove.info <<  "\n";
        std::cout << printBoard() << "\n";
        std::cout << bitboard_to_string(*board_to_move) << "\n";
        std::cout << "PtM: " << piece_to_move << "\n";
        std::cout << "bTM: " << board_to_move->test(bit_origin) << "\n";
        std::string colorToMove = (whiteToMove) ? "White" : "Black";
        throw std::runtime_error("undoMove: No piece of color: " + colorToMove + " at origin square: " +
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
    // A move with a capture (not en passant!) is has an info=4 (0100)
    if (lastMove.info == 4) {
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


    // If an enpassant move (info=5), replace captured pawn at the appropiate square
    // This is the square above/below the origin of the capturing pawn
    if (lastMove.info == 5) {
        // Get last captured piece and remove from captured pieces list
        auto * capturedPieces = (whiteToMove) ? &capturedBlackPieces :
            &capturedWhitePieces;
        Piece* capturedPiece = capturedPieces->back();
        capturedPieces->pop_back();

        // Add the captured pawn back on the board and piece bitboard in the
        // right place

        // If white to move, (i.e undoing white's move), replace black pawn
        if (whiteToMove) {
            capturedPiece->addPiece(static_cast<Square>(bit_origin+8));
            (&blackPieces)->flip(bit_origin+8);
            boardArray[bit_origin+8] = capturedPiece;

        }
        if (!whiteToMove) {
            capturedPiece->addPiece(static_cast<Square>(bit_origin-8));
            (&whitePieces)->flip(bit_origin-8);
            boardArray[bit_origin-8] = capturedPiece;
        }
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

    //std::cout << "clm1: " << printBoard() << "\n";

    makeMove(move);

    //std::cout << "MovecLM: " << Square_array[static_cast<int>(move.origin)] << "to" << Square_array[static_cast<int>(move.destination)] << " Info:" << move.info << "\n";

   /* if (move.info == 1) {
            std::cout << "ASDASDASD\n";
            std::cout << "Proposed Move: Origin: ";
            std::cout << Square_array[static_cast<int>(move.origin)] << " Dest: ";
            std::cout << Square_array[static_cast<int>(move.destination)] << " Info: ";
            std::cout << move.info << "\n";
        }*/

    //std::cout << "Proposed Move: Origin: ";
    //std::cout << Square_array[static_cast<int>(move.origin)] << " Dest: ";
    //std::cout << Square_array[static_cast<int>(move.destination)] << " Info: ";
    //std::cout << move.info << "\n";


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
    // If move is flagged as en passant, check previous move was double pawn push
    // from appropiate pawn
    auto passesEnPassantCheck = [move, this] () -> bool {

        // Check if move is encoded as en passant
        if (move.info != 5) {
            return true;
        }

        // Can't have en passant if move history empty Todo: raise error?
        if (moveHistory.empty()) {
            return false;
        }
        const Move& prevMove = *(moveHistory.rbegin()+1); // rbegin gives  reverse iterator

        // Check previous move was a double pawn push, if it was then
        // check move destination is same file as previous move origin
        if (prevMove.info == 1) {
            if (static_cast<int>(prevMove.origin) % 8 == static_cast<int>(move.destination) % 8) {
                return true;
            }
        }
        return false;
    };

    //std::cout << "clm2: " << printBoard() << "\n";

    // TODO: Do I need a passesHorizontalCheck?
    bool isLegalMove = (passesKnightChecks() && passesDiagonalChecks() && passesEnPassantCheck());

    //std::cout << "clm3: " << printBoard() << "\n";
    // Always have to undo move
    undoMove();

    //std::cout << "clm4: " << printBoard() << "\n";

    return isLegalMove;

}

// Deal with capture of other pawn
void Board::makeEnpassant(const Move & move) {

    // Find which square the opposing pawn to be taken is on
    // For white, will be row below destination, row above for black
    std::size_t bit_destination = static_cast<std::size_t>(move.destination);
    std::size_t oppPawnLoc = (whiteToMove) ?
        bit_destination + 8: bit_destination - 8;

    Piece * pawn_to_capture = boardArray[oppPawnLoc];
    if (!pawn_to_capture) {
        throw std::runtime_error("No pawn at expected destination for en passant");
    }

    // Add pawn to captured pieces
    (whiteToMove) ? capturedBlackPieces.push_back(pawn_to_capture):
        capturedWhitePieces.push_back(pawn_to_capture);

    // Remove pawn from pawn bitboard
    pawn_to_capture->capturePiece(static_cast<Square>(oppPawnLoc));

    // Update pieces bitboard
    bitboard_t * captured_board = (whiteToMove) ? &blackPieces : &whitePieces;
   // std::cout << bitboard_to_string(*captured_board);
   // std::cout << "Dest: " << bit_destination << "\n";
   // std::cout << "HI: " << oppPawnLoc << "\n";
    if (!captured_board->test(oppPawnLoc)){
        throw std::runtime_error("No pawn at expected position in piece bitboard");
    }
    captured_board->flip(oppPawnLoc);

    // Update boardArray - remove pawn at position
    boardArray[oppPawnLoc] = nullptr;
}

// Remove captured piece from board and relevant bitboards
// Also add captured piece to list of captured pieces for correct color
// Dont need to move capturing piece as done at end of makeMove()
void Board::makeCapture(const Move & move, Piece* piece_at_dest) {

    // Add captured piece to captured pieces list
    std::vector<Piece*>& capturedPieceList = (!whiteToMove) ?
        capturedWhitePieces : capturedBlackPieces;
    capturedPieceList.push_back(piece_at_dest);

    // Remove piece from pieces bitboard
    piece_at_dest->capturePiece(move.destination);

    // Remove piece from piece board
    bitboard_t* captured_board = (!whiteToMove) ? &whitePieces : &blackPieces;
    captured_board->flip(static_cast<std::size_t>(move.destination));
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