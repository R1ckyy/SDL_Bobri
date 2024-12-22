#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "imgrender.h"

void renderImage(SDL_Renderer *renderer, const char *path, int x, int y, int w, int h) {
    SDL_Texture * img = IMG_LoadTexture(renderer, path);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, img, NULL, &rect);

    SDL_DestroyTexture(img);
};