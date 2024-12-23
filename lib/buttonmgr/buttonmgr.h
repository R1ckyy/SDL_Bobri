#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#pragma once

typedef void (*ButtonFnc)();

typedef struct {
    TTF_Font *font;
    const char *text;
    int x;
    int y;
    int w;
    int h;
    ButtonFnc action;
} Button;

Button createButton(TTF_Font *font, const char *text, int x, int y, int w, int h, ButtonFnc fnc);

void renderButton(Button btn, SDL_Color color, SDL_Color color_highl);

void buttonCheck();

void runButtonFnc(Button btn);

void kill_Button(Button btn);