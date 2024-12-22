#pragma once

#include <SDL2/SDL.h>

void btnAction_StartGame();
void btnAction_Settings();
void btnAction_LeaderBoard();
void btnAction_Quit();

void init_MainMenu();

void render_MainMenu(SDL_Renderer *renderer, int mouse_x, int mouse_y);

void btnclk_MainMenu(int mouse_x, int mouse_y);

void kill_MainMenu();
