#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once

typedef struct {
    TTF_Font *font;
    char *text;
    int x;
    int y;
    int w;
    int h;
} Button;

Button createButton(TTF_Font *font, const char *text, int x, int y, int w, int h);

void renderButton(Button btn, SDL_Renderer *renderer);