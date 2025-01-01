#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../../utils/imgrender/imgrender.h"
#include "../../../utils/textrender/textrender.h"
#include "../../../utils/colors/colors.h"
#include "../../../utils/fileleaderboard/fileleaderboard.h"
#include "../../gamemgr/gamemgr.h"
#include "../../buttonmgr/buttonmgr.h"

#include "leaderboard.h"

static TTF_Font *titlefont;
static TTF_Font *mainfont;

static SDL_Texture *background_texture;

static ReadData leaderboard;

void btnAction_LReturnToMenu() {
    setActiveScreen(MENU);
};

void init_Leaderboard() {
    titlefont = TTF_OpenFont("fonts/Galindo.ttf", 72);
    mainfont = TTF_OpenFont("fonts/Roboto.ttf", 72);

    background_texture = IMG_LoadTexture(getRenderer(),"images/background_menu.png");

    leaderboard = readFromFile();

    createButton("led_returntomain", mainfont, "Return to menu", 50, 700, 300, 50, grey, white, btnAction_LReturnToMenu);
};

void render_Leaderboard() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0);

    renderImage(background_texture, 0, 0, 1400, 800, 0, 0);

    createText(titlefont, white, "Leaderboard", 50, 50, 375, 100);
    createText(mainfont, grey, "Copyright Erik Graf 2024/2025, All rights reserved", 0, 785, 300, 15);
    //createText(titlefont, white, "Coming soon Skbiid", 700, 200, 300, 300);

    if(leaderboard.entries == 0) {
        createText(mainfont, red, "No data", 500, 300, 400, 200);
    } else {
        for (int i = 0; i < 10; i++) {
            char buf[10];
            sprintf(buf, "%2d", (i+1));
            if(i >= leaderboard.entries) createText(mainfont, darkgrey, buf, 350, 160+(i*50), 50, 45);
            else {
                if(i == 0) createText(mainfont, gold, buf, 350, 160+(i*50), 50, 45);
                else createText(mainfont, white, buf, 350, 160+(i*50), 50, 45);
            }
        }
        
        for (int i = 0; i < 10 && i < leaderboard.entries; i++) {
            char buf[30];
            sprintf(buf, "%2d Points", leaderboard.data[i].points);
            if(i == 0) {
                createText(mainfont, gold, leaderboard.data[i].name, 450, 160+(i*50), 400, 45);
                createText(mainfont, gold, buf, 900, 160+(i*50), 200, 45);
            } else {
                createText(mainfont, white, leaderboard.data[i].name, 450, 160+(i*50), 400, 45);
                createText(mainfont, white, buf, 900, 160+(i*50), 200, 45);
            } 
        }
    }

    renderButtons();
};

void kill_Leaderboard() {
    TTF_CloseFont(titlefont);
    TTF_CloseFont(mainfont);

    if(leaderboard.entries != 0) free(leaderboard.data);

    SDL_DestroyTexture(background_texture);
};