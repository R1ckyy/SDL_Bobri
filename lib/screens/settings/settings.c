#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../gamemgr/gamemgr.h"
#include "../../buttonmgr/buttonmgr.h"
#include "../../playermgr/playermgr.h"

#include "settings.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

static SDL_Texture *background_texture;
SDL_Texture *bobers[3];

void btnAction_SReturnToMenu() {
    setActiveScreen(MENU);
};

void btnAction_SPlayer1() {
    enum PlayerSetting setting = getPlayerSetting(0);
    setPlayerSetting(0, setting == HUMAN ? BOT : setting == BOT ? INACTIVE : HUMAN);
};

void btnAction_SPlayer2() {
    enum PlayerSetting setting = getPlayerSetting(1);
    setPlayerSetting(1, setting == HUMAN ? BOT : setting == BOT ? INACTIVE : HUMAN);
};

void btnAction_SPlayer3() {
    enum PlayerSetting setting = getPlayerSetting(2);
    setPlayerSetting(2, setting == HUMAN ? BOT : setting == BOT ? INACTIVE : HUMAN);
};

void init_Settings() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    background_texture = IMG_LoadTexture(getRenderer(),"images/background_menu.png");

    createButton("set_returntomain", mainfont, "Return to menu", 50, 700, 300, 50, grey, white, btnAction_SReturnToMenu);

    createButton("set_playerone", mainfont, "Player 1", 500, 200, 300, 100, grey, high, btnAction_SPlayer1);
    createButton("set_playertwo", mainfont, "Player 2", 500, 350, 300, 100, grey, high, btnAction_SPlayer2);
    createButton("set_playerthree", mainfont, "Player 3", 500, 500, 300, 100, grey, high, btnAction_SPlayer3);

    bobers[0] = IMG_LoadTexture(getRenderer(), "images/Bober_kurwa_1.png");
    bobers[1] = IMG_LoadTexture(getRenderer(), "images/Bober_kurwa_2.png");
    bobers[2] = IMG_LoadTexture(getRenderer(), "images/Bober_kurwa_3.png");
};

void render_Settings() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    renderImage(background_texture, 0, 0, 1400, 800, 0, 0);

    createText(titlefont, white, "Settings", 50, 50, 300, 100);
    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);
    //createText(titlefont, white, "Coming soon Skbiid", 700, 200, 300, 300);

    for (int i = 0; i < 3; i++) {
        renderImage(bobers[i], 350, 200+i*150, 100, 100, 0, SDL_FLIP_NONE);  
        
        char buf[10];
        sprintf(buf, "%s", getPlayerSetting(i) == HUMAN ? "HUMAN" : getPlayerSetting(i) == BOT ? "BOT" : "NONE");
        createText(mainfont, white, buf, 900, 200+i*150, 200, 100);  
    }    
    createText(mainfont, white, "(W,A,S,D | SPACE)", 570, 310, 200, 25);
    createText(mainfont, white, "(I,J,K,L |  N  )", 570, 460, 200, 25);
    createText(mainfont, white, "(UP,LEFT,DOWN,RIGHT | RSHIFT)", 550, 610, 240, 25);
    
    renderButtons();
};

void kill_Settings() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);

    SDL_DestroyTexture(background_texture);
};