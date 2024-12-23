#include <string.h>
#include "../gamemgr/gamemgr.h"
#include "../screens/mainmenu/mainmenu.h"

#include "buttonmgr.h"

Button createButton(TTF_Font *font, const char *text, int x, int y, int w, int h, ButtonFnc fnc) {
    Button btn;
    btn.font = font;
    btn.text = text;
    btn.x = x;
    btn.y = y;
    btn.w = w;
    btn.h = h;
    btn.action = fnc;

    return btn;
};

void renderButton(Button btn, SDL_Color color, SDL_Color color_highl) {
    SDL_Surface *surface;

    if((getMousePos(X) >= btn.x && getMousePos(X) <= btn.x+btn.w) && (getMousePos(Y) >= btn.y && getMousePos(Y) <= btn.y+btn.h)) {
        surface = TTF_RenderText_Blended(btn.font, btn.text, color_highl);
    }else{
        surface = TTF_RenderText_Blended(btn.font, btn.text, color);
    }

    SDL_Rect text_rect;
    text_rect.x = btn.x;
    text_rect.y = btn.y;
    text_rect.w = btn.w;
    text_rect.h = btn.h;

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(getRenderer(), surface);

    SDL_RenderDrawRect(getRenderer(), &text_rect);
    
    SDL_RenderCopy(getRenderer(), text_texture, NULL, &text_rect);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(surface);
};

void buttonCheck(int mouse_x, int mouse_y) {
    switch (getActiveScreen()) {
    case MENU:
        btnclk_MainMenu(mouse_x, mouse_y);
        break;
    default:
        break;
    }
};

void runButtonFnc(Button btn) {
    if((getMousePos(X) >= btn.x && getMousePos(X) <= btn.x+btn.w) && (getMousePos(Y) >= btn.y && getMousePos(Y) <= btn.y+btn.h)) {
        btn.action();
    }
};

void kill_Button(Button btn) {
};