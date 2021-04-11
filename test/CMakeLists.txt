# Add catch 2
FetchContent_Declare(
    catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.9.1)
FetchContent_MakeAvailable(catch)

# Add tests as executable
add_executable(TEST tests-main.cpp tests-pawns.cpp test-knights.cpp
    test-king.cpp test-piece.cpp)

target_compile_features(TEST PRIVATE cxx_std_17)

target_link_libraries(TEST PRIVATE chess_library Catch2::Catch2)

add_test(NAME testlibtest COMMAND TEST)
