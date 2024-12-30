#include <string.h>
#include "../gamemgr/gamemgr.h"
#include "../screens/mainmenu/mainmenu.h"
#include "../screens/settings/settings.h"

#include "buttonmgr.h"

static Button *activeButtons;
static int activeButtonsc;

void initButtonMgr() {
    activeButtonsc = 0;
    activeButtons = NULL;
};

void createButton(const char *id, TTF_Font *font, const char *text, int x, int y, int w, int h, SDL_Color color, SDL_Color color_highl, ButtonFnc fnc) {
    Button btn;
    btn.id = id;
    btn.font = font;
    btn.text = text;
    btn.x = x;
    btn.y = y;
    btn.w = w;
    btn.h = h;
    btn.color = color;
    btn.color_highl = color_highl;
    btn.action = fnc;

    if(activeButtonsc == 0) {
        activeButtons = malloc(sizeof(Button) * (activeButtonsc+1));
        if(!activeButtons && isDebug()) {
            fprintf(stderr, "Memory allocation of Buttons failed.\n");
            exit(1);
        }
        activeButtons[activeButtonsc] = btn;
        activeButtonsc++;
    }else{
        activeButtons = realloc(activeButtons, sizeof(Button) * (activeButtonsc+1));
        if(!activeButtons && isDebug()) {
            fprintf(stderr, "Memory allocation of Buttons failed.\n");
            exit(1);
        }
        activeButtons[activeButtonsc] = btn;
        activeButtonsc++;
    }
};

void renderButtons() {
    for (int i = 0; i < activeButtonsc; i++) {
        Button btn = activeButtons[i];

        SDL_Surface *surface;

        if((getMousePos(X) >= btn.x && getMousePos(X) <= btn.x+btn.w) && 
        (getMousePos(Y) >= btn.y && getMousePos(Y) <= btn.y+btn.h)) {
            surface = TTF_RenderText_Blended(btn.font, btn.text, btn.color_highl);
        }else{
            surface = TTF_RenderText_Blended(btn.font, btn.text, btn.color);
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

    }
};

void buttonCheck() {
    for (int i = 0; i < activeButtonsc; i++) {
        Button btn = activeButtons[i];

        if((getMousePos(X) >= btn.x && getMousePos(X) <= btn.x+btn.w) && (getMousePos(Y) >= btn.y && getMousePos(Y) <= btn.y+btn.h)) {
        btn.action();
        break;
        }
    }
    
};

void cleanButtons() {
    if(activeButtons != NULL) {
        free(activeButtons);
        activeButtons = NULL;
    }
    activeButtonsc = 0;
}

void killButtonMgr() {
    if(activeButtons != NULL) {
        free(activeButtons);
    }
};
