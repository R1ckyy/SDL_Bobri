#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h> 
#include "../../gamemgr/gamemgr.h"
#include "../../playermgr/playermgr.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../../utils/imgrender/imgrender.h"
#include "../../buttonmgr/buttonmgr.h"

#include "endgame.h"

const char *bobers_paths[3] = {"images/Bober_kurwa_1.png","images/Bober_kurwa_2.png","images/Bober_kurwa_3.png"};
static SDL_Texture *bobers[3];
static double angle; 

static char name[INPUTLENGTH];
Score bestScore;
SDL_Rect input;
static bool input_active;
static int length;

static SDL_Texture *background_texture;

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void btnAction_EReturnToMenu() {
    setActiveScreen(MENU);
};

void btnAction_ESaveData() {
    setActiveScreen(MENU);
}

void init_EndGame() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    background_texture = IMG_LoadTexture(getRenderer(), "images/background_menu.png");
    for (int i = 0; i < 3; i++) {
        bobers[i] = IMG_LoadTexture(getRenderer(), bobers_paths[i]);
    }
    angle = 0;

    bestScore.boberid =-2;
    bestScore.score = 0;

    bestScore = getPlayerScores();
    input.x = 300;
    input.y = 450;
    input.w = 600;
    input.h = 75;
    input_active = false;
    length = 0;
    for (int i = 0; i < INPUTLENGTH-1; i++) {
        name[i] = ' ';
    }
    name[INPUTLENGTH] = '\0';

    createButton("end_returntomain", mainfont, "Return to menu", 50, 700, 300, 50, grey, white, btnAction_EReturnToMenu);
};

void render_EndGame() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
    renderImage(background_texture, 0, 0, 1400, 800, 0, SDL_FLIP_NONE);

    createText(titlefont, white, "Game Over!", 500, 100, 400, 100);

    if(bestScore.boberid == -2) {
        createText(mainfont, white, "Its a Tie! Too bad...", 400, 300, 600, 100);
    } else if (bestScore.boberid == -1) {
        createText(mainfont, white, "A Bot Won!", 400, 300, 600, 100);
    } else {
        createButton("end_savedata", mainfont, "Save", 915, 450, 175, 75, grey, high, btnAction_ESaveData);

        char buf[35];
        sprintf(buf, "Player %d Won with %d points!", bestScore.boberid+1, bestScore.score);
        renderImage(bobers[bestScore.boberid], 625, 190, 150, 150, angle, SDL_FLIP_NONE);
        createText(mainfont, white, buf, 300, 325, 800, 75);
        createText(mainfont, white, "Enter your name (15 chars max):", 300, 425, 250, 25);
        if(input_active) SDL_SetRenderDrawColor(getRenderer(), 150, 150, 150, 150);
        else SDL_SetRenderDrawColor(getRenderer(), 100, 100, 100, 100);
        SDL_RenderFillRect(getRenderer(), &input);
        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
        createText(mainfont, white, name, 310 ,460, 580, 55);
    }

    renderButtons();
};

void endGame_keyPressed(SDL_KeyCode key) {
    if(!input_active) return;
    if(key == SDLK_BACKSPACE && length > 0) {
        name[length-1] = ' ';
        length--;
    }
    if(key >= SDLK_a && key <= SDLK_z && length < INPUTLENGTH -1) {
        name[length] = (char)key;
        length++;
    }else if(key == SDLK_SPACE && length < INPUTLENGTH -1) {
        name[length] = '-';
        length++;
    }
};

void logic_EndGame() {
    if(getMousePos(X) >= input.x && getMousePos(X) <= input.x+input.w && getMousePos(Y) >= input.y && getMousePos(Y) <= input.y+input.h) input_active = true;
    else input_active = false;
    
    angle = angle + 100*getDeltaTime();
};

void kill_EndGame() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);

    SDL_DestroyTexture(background_texture);
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bobers[i]);
    }
};