#pragma once

#include <SDL2/SDL.h>

typedef struct {
    int bober_id;
    int score;
} Score;

void init_EndGame();

void render_EndGame();

void EndGameLogic();

void kill_EndGame();