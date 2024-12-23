#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "../../lib/gamemgr/gamemgr.h"

#include "textrender.h"

void createText(TTF_Font *font, SDL_Color color, const char *text, int x, int y, int w, int h) {
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

    SDL_Rect text_rect;
    text_rect.x = x;
    text_rect.y = y;
    text_rect.w = w;
    text_rect.h = h;

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_RenderDrawRect(getRenderer(), &text_rect);
    
    SDL_RenderCopy(getRenderer(), text_texture, NULL, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(surface);
};