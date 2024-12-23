#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void createText(TTF_Font *font, SDL_Color color, const char *text, int x, int y, int w, int h);
