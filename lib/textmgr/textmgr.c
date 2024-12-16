#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "textmgr.h"

void createText(TTF_Font *font, SDL_Renderer *renderer, SDL_Color color, const char *text, int x, int y, int w, int h) {
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

    SDL_Rect text_rect;
    text_rect.x = x;
    text_rect.y = y;
    text_rect.w = w;
    text_rect.h = h;

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderDrawRect(renderer, &text_rect);
    
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(surface);
};