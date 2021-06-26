#include <RookLookup.h>
#include <iostream>

// Generate the rook moveset for a given square, indexed using a magic number
// Starting with a random 64-bit number, go through each blockerboard, generate
// a hash and the associated move board. Try and place the move board in the map
// with the hash as a key. If already something there, compare move boards. If
// the move boards are the same this is fine, else have to start again with a
// different random number.
// Returns the magic number and changes a map of movesets for that particular
// square (which is given as an argument)




uint64_t RookLookup::generateRookMoveSetforSquare(Square const & origin) {

    // map of movesets, indexed by hash
    std::unordered_map<int, uint64_t>moveSet;
    //std::unordered_map<long long int, long long int>::iterator it;

    // Create a random number to be turned into bitset
    std::random_device rd; // used to obtain seed for rng
    std::mt19937_64 gen(rd()); // mersenne_tweister engine seeded with rd()
    std::uniform_int_distribution<uint64_t> distrib(0,std::llround(
        std::pow(2,64)));

    uint64_t magicNum = 0;


    // generate full list of blocking boards
    bitboard_t blockerMask = generateRookBlockerMask(origin);
    std::vector<bitboard_t> blockerBoards = generateBlockerBoards(
        blockerMask);

    int num_bits = blockerMask.count();

    // Try a certain amount of magic numbers before quitting
    for (int i=0; i<100000; i++) {

        moveSet.clear(); // clear map before each attempt

        bool validNum = true;

        // Generate the random magic number candidate
        magicNum = distrib(gen);
        std::cout << magicNum << "\n";


        //std::cout << "magicNum: " << magicNum << "\n";

        // Go through blockerBoards
        for (bitboard_t blockerBoard : blockerBoards) {
            // Create the moveBoard
            bitboard_t moveBoard = generateRookMoveBoard(blockerBoard, origin);
            // Generate the hash
            uint64_t blockerBoardInt = blockerBoard.to_ullong();
          //  std::cout << "Blockers" << bitboard_to_string(blockerBoard);
            uint64_t moveBoardInt = moveBoard.to_ullong();
          //  std::cout << "PreHash" << bitboard_to_string(blockerBoardInt*magicNum);
            int hash = (blockerBoardInt * magicNum) >> (64-num_bits);
          //  std::cout << "HASH: " << hash << bitboard_to_string(hash) << "\n";
          //  std::bitset<12> x(hash);
          //  std::cout << x << "\n";

            // Try placing moveboard at hash in map - if collision check if
            // current entry is same or not

            if (moveSet.count(hash) == 0) {
                moveSet[hash] = moveBoardInt;
                continue;
            }
            // if the move boards are the same can allow the collision
            else if (moveSet[hash] == moveBoardInt) {
            //    std::cout << "FINE COLLISION: " << "\n";
            //    std::cout << "Hash: " << hash << "\n";
            //    std::cout << "Current Moveboard: " << moveBoardInt << "\n";
            //    std::cout << "Moveboard at hash: " << moveSet[hash] << "\n";
                continue;
            }
            else {
                // Need to try a new magic number

                validNum = false;
              //  std::cout << "Bad NUM" << "\n";
              //  std::cout << "Hash: " << hash << "\n";
              //  std::cout << "Current Moveboard: " << moveBoardInt << "\n";
              //  std::cout << "Moveboard at hash: " << moveSet[hash] << "\n";
                break;
            }
        }
        // If code gets to here and valid num is true, can return moveSet
        // Else try a new magic number
        if (validNum) {
            //std::cout << "Found Number:: " << magicNum;
            // Add map to vector of maps
            return magicNum;
        }
    }


    throw std::invalid_argument("Couldn't find legitimate magic number!");
    return -1;

}
// For a given square, add a 1 to bitboard vertically/horizontally until
// reach the edge
bitboard_t RookLookup::generateRookBlockerMask(Square const & origin) {

    bitboard_t blockerMask = generateBitboard(std::vector<Square>{});


    std::size_t int_origin = static_cast<size_t>(origin);


    // get row start and end
    int row_start = int_origin/8 * 8; // int division to get multiple of 8
    int row_end = row_start + 7;

    // get column
    int col = int_origin - row_start;

    // fill whole row
    for (row_start; row_start<row_end-1; row_start++) {
        blockerMask.set(row_start+1);
    }

    // fill whole column
    for (int i=1; i<7; i++) {
        blockerMask.set(col+i*8);
    }

    // finally, set the origin square bit to 0
    blockerMask.reset(int_origin);

    return blockerMask;
}

std::vector<bitboard_t> RookLookup::generateBlockerBoards(
    bitboard_t const & blockerMask) {
    // To generate all possible blockerboards, need to get all possible
    // combinations of 1s and 0s from relevant squares. To do this,
    // can create bitsets for each number from 0 to 2^no.bits, and
    // use these to generate the bitboards by placing each bit on the relevant
    // square

    std::vector<bitboard_t> blockerBoards = {};

    // Create a vector of squares used in blocker, in order of index
    std::vector<Square> relevantSquares = {};
    for (size_t bit=0; bit<blockerMask.size(); bit++) {
        if (blockerMask.test(bit)) {
            relevantSquares.push_back(static_cast<Square>(bit));
        }
    }


    // loop through numbers from 0 to 2^bits, convert to binary and assign
    // each true bit to the relevant blocking square, then create the bitboard
    const int num_bits = blockerMask.count();
    for (size_t i=0; i<std::pow(2,num_bits); i++) {
        std::bitset<13> blockingBitset{i};  // 12 should be the maximum number of blocking pieces
        // go through bitset, for each turned on bit, add relevant square to vector

        std::vector<Square> blockingSquares = {};
        for (size_t j=0; j<num_bits; j++) {
            if (blockingBitset.test(j)) {
                blockingSquares.push_back(relevantSquares.at(j));
            }
        }
        blockerBoards.push_back(generateBitboard(blockingSquares));

    }

    return blockerBoards;
}

// Generate the attack set for a rook given a blocker mask
// Note this will allow attacks on same color pieces - need to remove later
bitboard_t RookLookup::generateRookMoveBoard(bitboard_t const & blockerBoard,
    Square const & origin) {

    bitboard_t moveSet = generateBitboard(std::vector<Square>{});

    int currentPos_int = static_cast<int>(origin);

    // Add ones in upwards direction until reach a blocker piece or end of board
    while(currentPos_int > static_cast<int>(Square::A8)) {
        // move up to next square
        currentPos_int -= 8;
        // if blocker piece, break out of upwards direction
        if (blockerBoard.test(currentPos_int)) {
            break;
        }
        // else, add square as a valid move
        moveSet.set(currentPos_int);
    }

    // Add in downwards direction until reach a blocker or end of board
    currentPos_int = static_cast<int>(origin); // reset current pos to origin
    while (currentPos_int < static_cast<int>(Square::H1)) {
        // move down to next square
        currentPos_int += 8;
        // if blocker piece, break out of current direction
        if (blockerBoard.test(currentPos_int)) {
            break;
        }
        // add square as valid move
        moveSet.set(currentPos_int);
    }

    currentPos_int = static_cast<int>(origin); // reset current pos to origin

    // get row start and end for left/right movement
    int row_start = currentPos_int/8 * 8; // int division to get multiple of 8
    int row_end = row_start + 7;

    // Add in left direction until reach a blocker or end of board

    while (currentPos_int < row_end) {
        // move down to next square
        currentPos_int += 1;
        // if blocker piece, break out of current direction
        if (blockerBoard.test(currentPos_int)) {
            break;
        }
        // add square as valid move
        moveSet.set(currentPos_int);
    }

    currentPos_int = static_cast<int>(origin); // reset current pos to origin

    // Add in right direction until reach blocker or end of board
    while (currentPos_int > row_start) {
        // move down to next square
        currentPos_int -= 1;
        // if blocker piece, break out of current direction
        if (blockerBoard.test(currentPos_int)) {
            break;
        }
        // add square as valid move
        moveSet.set(currentPos_int);
    }

    return moveSet;
}

/*
// Initialise RookLookup moveSets and magic numbers - static members have to
// be declared like this
std::vector<std::unordered_map<uint64_t, uint64_t>> RookLookup::moveSets = {};

const std::vector<uint64_t> RookLookup::rookMagicNumbers = {
    // H8
    generateRookMoveSetforSquare(Square::H8, moveSets),
    // G8
    generateRookMoveSetforSquare(Square::G8, moveSets),
    // F8
    generateRookMoveSetforSquare(Square::F8, moveSets),
    // E8
    generateRookMoveSetforSquare(Square::E8, moveSets),
    // D8
    generateRookMoveSetforSquare(Square::D8, moveSets),
    // C8
    generateRookMoveSetforSquare(Square::C8, moveSets),
    // B8
    generateRookMoveSetforSquare(Square::B8, moveSets),
    // A8
    generateRookMoveSetforSquare(Square::A8, moveSets),

    // H7
    generateRookMoveSetforSquare(Square::H7, moveSets),
    // G7
    generateRookMoveSetforSquare(Square::G7, moveSets),
    // F7
    generateRookMoveSetforSquare(Square::F7, moveSets),
    // E7
    generateRookMoveSetforSquare(Square::E7, moveSets),
    // D7
    generateRookMoveSetforSquare(Square::D7, moveSets),
    // C7
    generateRookMoveSetforSquare(Square::C7, moveSets),
    // B7
    generateRookMoveSetforSquare(Square::B7, moveSets),
    // A7
    generateRookMoveSetforSquare(Square::A7, moveSets),

    // H6
    generateRookMoveSetforSquare(Square::H6, moveSets),
    // G6
    generateRookMoveSetforSquare(Square::G6, moveSets),
    // F6
    generateRookMoveSetforSquare(Square::F6, moveSets),
    // E6
    generateRookMoveSetforSquare(Square::E6, moveSets),
    // D6
    generateRookMoveSetforSquare(Square::D6, moveSets),
    // C6
    generateRookMoveSetforSquare(Square::C6, moveSets),
    // B6
    generateRookMoveSetforSquare(Square::B6, moveSets),
    // A6
    generateRookMoveSetforSquare(Square::A6, moveSets),

    // H5
    generateRookMoveSetforSquare(Square::H5, moveSets),
    // G5
    generateRookMoveSetforSquare(Square::G5, moveSets),
    // F5
    generateRookMoveSetforSquare(Square::F5, moveSets),
    // E5
    generateRookMoveSetforSquare(Square::E5, moveSets),
    // D5
    generateRookMoveSetforSquare(Square::D5, moveSets),
    // C5
    generateRookMoveSetforSquare(Square::C5, moveSets),
    // B5
    generateRookMoveSetforSquare(Square::B5, moveSets),
    // A5
    generateRookMoveSetforSquare(Square::A5, moveSets),

    // H4
    generateRookMoveSetforSquare(Square::H4, moveSets),
    // G4
    generateRookMoveSetforSquare(Square::G4, moveSets),
    // F4
    generateRookMoveSetforSquare(Square::F4, moveSets),
    // E4
    generateRookMoveSetforSquare(Square::E4, moveSets),
    // D4
    generateRookMoveSetforSquare(Square::D4, moveSets),
    // C4
    generateRookMoveSetforSquare(Square::C4, moveSets),
    // B4
    generateRookMoveSetforSquare(Square::B4, moveSets),
    // A4
    generateRookMoveSetforSquare(Square::A4, moveSets),

    // H3
    generateRookMoveSetforSquare(Square::H3, moveSets),
    // G3
    generateRookMoveSetforSquare(Square::G3, moveSets),
    // F3
    generateRookMoveSetforSquare(Square::F3, moveSets),
    // E3
    generateRookMoveSetforSquare(Square::E3, moveSets),
    // D3
    generateRookMoveSetforSquare(Square::D3, moveSets),
    // C3
    generateRookMoveSetforSquare(Square::C3, moveSets),
    // B3
    generateRookMoveSetforSquare(Square::B3, moveSets),
    // A3
    generateRookMoveSetforSquare(Square::A3, moveSets),

    // H2
    generateRookMoveSetforSquare(Square::H2, moveSets),
    // G2
    generateRookMoveSetforSquare(Square::G2, moveSets),
    // F2
    generateRookMoveSetforSquare(Square::F2, moveSets),
    // E2
    generateRookMoveSetforSquare(Square::E2, moveSets),
    // D2
    generateRookMoveSetforSquare(Square::D2, moveSets),
    // C2
    generateRookMoveSetforSquare(Square::C2, moveSets),
    // B2
    generateRookMoveSetforSquare(Square::B2, moveSets),
    // A2
    generateRookMoveSetforSquare(Square::A2, moveSets),

    // H1
    generateRookMoveSetforSquare(Square::H1, moveSets),
    // G1
    generateRookMoveSetforSquare(Square::G1, moveSets),
    // F1
    generateRookMoveSetforSquare(Square::F1, moveSets),
    // E1
    generateRookMoveSetforSquare(Square::E1, moveSets),
    // D1
    generateRookMoveSetforSquare(Square::D1, moveSets),
    // C1
    generateRookMoveSetforSquare(Square::C1, moveSets),
    // B1
    generateRookMoveSetforSquare(Square::B1, moveSets),
    // A1
    generateRookMoveSetforSquare(Square::A1, moveSets),
};
*/

