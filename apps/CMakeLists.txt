add_executable(chessApp main.cpp)
target_compile_features(chessApp PRIVATE cxx_std_17)

target_link_libraries(chessApp PRIVATE chess_library)