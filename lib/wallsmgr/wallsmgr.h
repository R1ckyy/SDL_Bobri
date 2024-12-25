#include <SDL2/SDL.h>
#include <stdbool.h>

#pragma once

void initWallsManager();

void renderWalls();

bool WallRectCollision(SDL_Rect rect); 

void killWallsManager();