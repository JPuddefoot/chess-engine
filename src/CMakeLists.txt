# Create header list
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/*.h")
#set(HEADER_LIST "${ChessEngine_SOURCE_DIR}/include/*.h")

# make automatic library

add_library(chess_library Pawns.cpp Knight.cpp King.cpp utils.cpp
    Move.cpp Board.cpp Piece.cpp RookLookup.cpp ${HEADER_LIST})

# Need directory and users need too
target_include_directories(chess_library PUBLIC ../include)

target_compile_features(chess_library PUBLIC cxx_std_11)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)

