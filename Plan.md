## Goal

Engine connected to graphical board that gives position evaluation and moves pieces for a side.

## Todo list

- [] Board Representation
- [] Search
- [] Evaluate
- [] Connect to GUI


## Board Representation

### Bitboards

finite set up to 64 elements - one bit per board square

typically have one bitboard for each color and type - 1 = piece, 0=nothing


Magic bitboard - used for sliding pieces (bishop rook queens)
    - blocker mask is all squares that can be occupied and block piece from moving further (dont need edges)
    - blocker boards - permutations of combinations that block (subset of blocker mask)
    - move board = resulting avaiale moves (including captures)

    - Need to generate blocker mask on all squares for rook and bishop, and all blocker and move boards
      For each square, piece combo try random 64 bit numbers - will be magic if (blockerboard*magic) >> (64-bits)
      for certain piece if two blocker boards generate same magical index but have different move boards - try again

    - Will have 64 rook magic numbers and 64 bishop numbers
    - initialize all blocker masks, blocker boards and move boards - can efficiently look up move baords with:
      uint64_t magic_move_rook (int8_t square, uint64t occupancy) {
          Remove occupants that arent in blocker mask for this square (occupancy &= Rook.blockmask[square])
          Calculate magic move index (int index = occupancy*Rook.magic[square]) >> (64-Rook.bits[square)
          return pre-calculaed move board (Return Rook.moveboard[square][index])
      }

Normal bitboards - generate move patterns

pawns/kings etc can shift bits left/right = moving a square

Need to have a full board with every piece on - two boards with white/black


#### Pawns

Push all pawns by shifting one rank (double if needed) - intersect with empty squares
Create disjoint sets for east-west attacks intersect with files for a and h files - reverse shift to get full attack set
Capture is intersect with opponent pieces
Additional rules for en passant