#pragma once

#include <SDL2/SDL.h>

#define INPUTLENGTH 16

typedef struct {
    int boberid;
    int score;
} Score;

void init_EndGame();

void render_EndGame();

void endGame_keyPressed(SDL_KeyCode key);

void logic_EndGame();

void kill_EndGame();