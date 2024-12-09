cmake_minimum_required(VERSION 3.12)
project(sdlapp C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES
    main.c
    lib/**/*.c
)

file(GLOB_RECURSE HEADERS
    lib/**/*.h
)

add_executable(sdlgame ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(sdlgame PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdlgame SDL2 SDL2_image SDL2_ttf)

target_include_directories(sdlgame PRIVATE HEADERS)