#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../gamemgr/gamemgr.h"
#include "../../utils/imgrender/imgrender.h"

#include "wallsmgr.h"

#define WALLCOUNT 3

static SDL_Texture *wall_texture;

static int wallPos[WALLCOUNT][4] = {
    {1000,300,50,300},
    {400,300,200,50},
    {550,57+0,50,100}
};
static SDL_Rect *walls;

void initWallsManager() {
    wall_texture = IMG_LoadTexture(getRenderer(), "images/wall.png");

    walls = malloc(sizeof(SDL_Rect) * WALLCOUNT);
    if(!walls & isDebug()) {
        fprintf(stderr, "Memory allocation of Walls failed.\n");
        exit(1);
    }
    for (int i = 0; i < WALLCOUNT; i++) {
        SDL_Rect wallrect;
        for (int j = 0; j < 4; j++) {
            wallrect.x = wallPos[i][0];
            wallrect.y = wallPos[i][1];
            wallrect.w = wallPos[i][2];
            wallrect.h = wallPos[i][3];
        }
        walls[i] = wallrect;
    }
};

void renderWalls() {
    for (int i = 0; i < WALLCOUNT; i++) {
        renderImageOnRect(wall_texture, walls[i], 0, SDL_FLIP_NONE);
        SDL_RenderDrawRect(getRenderer(), &walls[i]);
    }
};

bool WallRectCollision(SDL_Rect rect) {
    SDL_Rect result;
    for (int i = 0; i < WALLCOUNT; i++) {
        if(SDL_IntersectRect(&walls[i], &rect, &result) == SDL_TRUE) return true;
    }
    return false;
}; 

void killWallsManager() {
    SDL_DestroyTexture(wall_texture);

    free(walls);
};