#pragma once

#include <stdbool.h>
#include "../playermgr/playermgr.h"

typedef struct {
    SDL_Rect rect;
    double x_vel;
    double y_vel;
    bool remove;
    int id_bober_owner;
} Bullet;

void initBulletManager();

Bullet createBullet(Bober firing_bober);

void bulletFired(Bober firing_bober, int id_bober);

void bulletLogic();

void renderBullets();

void killBulletManager();