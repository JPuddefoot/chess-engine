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
long long int generateRookMoveSetforSquare(Square const & origin) {

    // map of movesets, indexed by hash
    std::unordered_map<long long int, uint64_t>moveSet;
    //std::unordered_map<long long int, long long int>::iterator it;

    // Create a random number to be turned into bitset
    std::random_device rd; // used to obtain seed for rng
    std::mt19937_64 gen(rd()); // mersenne_tweister engine seeded with rd()
    std::uniform_int_distribution<long long int> distrib(0,std::llround(
        std::pow(2,64)));

    long long int magicNum = 0;


    // generate full list of blocking boards
    bitboard_t blockerMask = generateRookBlockerMask(origin);
    std::vector<bitboard_t> blockerBoards = generateBlockerBoards(
        blockerMask);

    int num_bits = blockerMask.count()+1;

    // Try a certain amount of magic numbers before quitting
    for (int i=0; i<1000000; i++) {

        moveSet.clear(); // clear map before each attempt

        bool validNum = true;

        // Generate the random magic number candidate
        magicNum = distrib(gen);


       // std::cout << "magicNum: " << magicNum << "\n";

        // Go through blockerBoards
        for (bitboard_t blockerBoard : blockerBoards) {
            // Create the moveBoard
            bitboard_t moveBoard = generateRookMoveBoard(blockerBoard, origin);
            // Generate the hash
            uint64_t blockerBoardInt = blockerBoard.to_ullong();
            uint64_t moveBoardInt = moveBoard.to_ullong();
            uint64_t hash = blockerBoardInt * magicNum >> (64-num_bits);
            //std::cout << "HASH: " << hash << "\n";

            // Try placing moveboard at hash in map - if collision check if
            // current entry is same or not

            if (moveSet.count(hash) == 0) {
                moveSet[hash] = moveBoardInt;
                continue;
            }
            else {
                // Need to try a new magic number
               // std::cout << "Muggle Number, trying new magic number \n";
                validNum = false;
               // std::cout << "MoveBoard: " << bitboard_to_string(moveBoardInt) << "\n";
               // std::cout << "Collided : " << bitboard_to_string(moveSet.at(hash)) << "\n";
               // std::cout << "Blocker board: " << blockerBoardInt << "\n";
                break;
            }
        }
        // If code gets to here and valid num is true, can return moveSet
        // Else try a new magic number
        if (validNum) {
            std::cout << "Found Number:: " << magicNum;
            return magicNum;
        }
    }



    return -1;

}
// For a given square, add a 1 to bitboard vertically/horizontally until
// reach the edge
bitboard_t generateRookBlockerMask(Square const & origin) {

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

std::vector<bitboard_t> generateBlockerBoards(bitboard_t const & blockerMask) {
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
bitboard_t generateRookMoveBoard(bitboard_t const & blockerBoard,
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


