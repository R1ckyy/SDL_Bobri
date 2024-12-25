#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../lib/gamemgr/gamemgr.h"

#include "imgrender.h"

void renderImage(SDL_Texture *img, int x, int y, int w, int h, double angle, SDL_RendererFlip flip) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(getRenderer(), img, NULL, &rect, angle, NULL, flip);
};

void renderImageOnRect(SDL_Texture *img, SDL_Rect rect, double angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(getRenderer(), img, NULL, &rect, angle, NULL, flip);
};