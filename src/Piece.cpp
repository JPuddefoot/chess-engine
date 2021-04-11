#include <Piece.h>
#include <iostream>

// Todo - error management -> should function fail if no bit in place?


// Check piece exists on origin, if it does then remove from square and
// add to destination
void Piece::makeMove(const Square & origin, const Square & destination) {
    std::size_t bit_origin = static_cast<std::size_t>(origin);
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    if (currentPos.test(bit_origin) && !currentPos.test(bit_destination)) {
        currentPos.flip(bit_origin);
        currentPos.flip(bit_destination);
    }
}

// Check piece exists on capture square, if it does then remove it from square
void Piece::capturePiece(const Square & capture_square) {
    std::size_t bit_capture_square = static_cast<std::size_t>(capture_square);
    if (currentPos.test(bit_capture_square))
        currentPos.flip(bit_capture_square);
}

// Check piece doesn't exists on square, if not then add to square
void Piece::addPiece(const Square & destination) {
    std::size_t bit_destination = static_cast<std::size_t>(destination);
    if (!currentPos.test(bit_destination))
        currentPos.flip(bit_destination);
}