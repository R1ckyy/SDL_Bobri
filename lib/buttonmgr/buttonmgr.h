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

void renderButton(Button btn, SDL_Renderer *renderer, SDL_Color color, SDL_Color color_highl, int mouse_x, int mouse_y);

void buttonCheck(int mouse_x, int mouse_y);

void runButtonFnc(Button btn, int mouse_x, int mouse_y);

void kill_Button(Button btn);