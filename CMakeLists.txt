cmake_minimum_required(VERSION 3.14...3.19)

# Project name
project(
    ChessEngine
    VERSION 0.1
    DESCRIPTION "A chess engine"
    LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # ensure -std=c++xx not g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    include(CTest)

endif()

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_fetchContent.cmake)
endif()


# compiled library code is here
add_subdirectory(src)

# executable code is here
add_subdirectory(apps)

# Testing code
add_subdirectory(test)
