#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../lib/gamemgr/gamemgr.h"

#include "imgrender.h"

void renderImage(const char *path, int x, int y, int w, int h, double angle) {
    SDL_Texture * img = IMG_LoadTexture(getRenderer(), path);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(getRenderer(), img, NULL, &rect, angle, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(img);
};