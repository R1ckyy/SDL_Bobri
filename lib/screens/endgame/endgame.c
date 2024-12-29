#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../../gamemgr/gamemgr.h"
#include "../../playermgr/playermgr.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../../utils/imgrender/imgrender.h"
#include "../../buttonmgr/buttonmgr.h"

#include "endgame.h"

static Score bestScore;

static SDL_Texture *background_texture;

static TTF_Font *titlefont;
static TTF_Font *mainfont;

void btnAction_EReturnToMenu() {
    setActiveScreen(MENU);
};

void init_EndGame() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    background_texture = IMG_LoadTexture(getRenderer(), "images/background_menu.png");

    bestScore = getPlayerScores();

    createButton("end_returntomain", mainfont, "Return to menu", 50, 700, 300, 50, grey, white, btnAction_EReturnToMenu);
};

void render_EndGame() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);
    renderImage(background_texture, 0, 0, 1400, 800, 0, SDL_FLIP_NONE);

    createText(titlefont, white, "Game Over!", 500, 100, 400, 100);

    if(bestScore.bober_id == -2) {
        createText(mainfont, white, "Its a Tie! Too bad...", 400, 300, 600, 100);
    } else {
        char buf[35];
        sprintf(buf, "Player %d Won with %d points!", bestScore.bober_id, bestScore.score);
        createText(mainfont, white, buf, 300, 300, 800, 100);
    }

    renderButtons();
};

void EndGameLogic() {

};

void kill_EndGame() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);

    SDL_DestroyTexture(background_texture);
};