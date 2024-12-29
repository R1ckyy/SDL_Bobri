#pragma once

#include <stdbool.h>
#include "../playermgr/playermgr.h"

#define UPGRADE_XSIZE 90
#define UPGRADE_YSIZE 35
#define UPGRADE_RECT2OFFSET 10

#define UPGRADE_RESPAWNCOOLDOWN 20000

typedef struct {
   enum Weapon weapon_upgrade;
   SDL_Rect rect;
   SDL_Rect rect2;
   bool active;
} Upgrade;

void initUpgradesManager();

void respawnUpgrades();

void renderUpgrades();

void upgradesLogic();

void killUpgradesManager();