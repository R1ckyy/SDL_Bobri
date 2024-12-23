cmake_minimum_required(VERSION 3.12)
project(sdlapp C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE CFILES
    main.c
    lib/**/*.c
    utils/**/*.c
    utils/*.c
)

file(GLOB_RECURSE HFILES
    lib/**/*.h
    utils/**/*.h
)

add_executable(sdlgame ${CFILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(sdlgame PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdlgame SDL2 SDL2_image SDL2_ttf)

target_include_directories(sdlgame PRIVATE HFILES)