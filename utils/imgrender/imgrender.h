#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void renderImage(SDL_Texture *img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip);