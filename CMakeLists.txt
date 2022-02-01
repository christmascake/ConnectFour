cmake_minimum_required(VERSION 3.22.1)

project(
    ConnectFour
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#enable clang-tidy
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

#try to find an sfml package
find_package(
    SFML
    2.5.1 REQUIRED
    COMPONENTS system graphics window
)

#create executable target
add_executable(${PROJECT_NAME})

#add source files
target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ai.cpp
)

#include headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIRECTORIES}
)

#link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-system
    sfml-graphics
    sfml-window
)