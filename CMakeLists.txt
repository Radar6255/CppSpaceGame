cmake_minimum_required(VERSION 3.16)
project(SpaceGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_compile_options(-Wall -Wextra -pedantic -g)

add_executable(main main.cpp world.cpp asteroid.cpp display.cpp ship.cpp general.cpp)

target_link_libraries(main ${CURSES_LIBRARIES})
