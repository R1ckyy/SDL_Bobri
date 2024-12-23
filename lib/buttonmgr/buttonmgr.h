#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once

typedef void (*ButtonFnc)();

typedef struct {
    const char *id;
    TTF_Font *font;
    const char *text;
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
    SDL_Color color_highl;
    ButtonFnc action;
} Button;

void initButtonMgr();

void createButton(const char *id, TTF_Font *font, const char *text, int x, int y, int w, int h, SDL_Color color, SDL_Color color_highl, ButtonFnc fnc);

void renderButtons();

void buttonCheck();

void cleanButtons();

void killButtonMgr();