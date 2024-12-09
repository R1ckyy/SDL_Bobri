gcc main.c $(find lib -name "*.c") -o main.out -fsanitize=address -g -lSDL2 -lSDL2_ttf -lSDL2_image
rm -rf build/
mkdir build
cd build
cmake ..
make
./sdlgame