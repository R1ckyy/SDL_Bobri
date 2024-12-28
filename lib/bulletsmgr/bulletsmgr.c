#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../gamemgr/gamemgr.h"
#include "../playermgr/playermgr.h"
#include "../wallsmgr/wallsmgr.h"
#include "../../utils/imgrender/imgrender.h"

#include "bulletsmgr.h"

#define BULLETSPEED 700
#define BULLETSIZE 15

SDL_Texture *bullet_texture;

static Bullet *bullets;
static int bulletc;

void initBulletManager() {
    bullet_texture = IMG_LoadTexture(getRenderer(),"images/bullet.png");
    bulletc = 0;
};

Bullet createBullet(Bober firing_bober) {
    Bullet bullet;
    bullet.rect.x = firing_bober.angle == 0 ? firing_bober.rect.x+BOBERSIZE/2-WEAPONSIZE/2 : 
                    firing_bober.angle == 90 ? firing_bober.rect.x+BOBERSIZE+WEAPONSIZE :
                    firing_bober.angle == 180 ? firing_bober.rect.x+BOBERSIZE/2+WEAPONSIZE/2 :
                    firing_bober.angle == 270 ? firing_bober.rect.x-WEAPONSIZE : 0;
    bullet.rect.y = firing_bober.angle == 0 ? firing_bober.rect.y-WEAPONSIZE :
                    firing_bober.angle == 90 ? firing_bober.rect.y+BOBERSIZE/2-WEAPONSIZE/2 :
                    firing_bober.angle == 180 ? firing_bober.rect.y+BOBERSIZE+WEAPONSIZE :
                    firing_bober.angle == 270 ? firing_bober.rect.y+BOBERSIZE/2-WEAPONSIZE/2 : 0;
    bullet.rect.w = BULLETSIZE;
    bullet.rect.h = BULLETSIZE;
    bullet.remove = false;

    return bullet;
};

void bulletFired(Bober firing_bober) {
    printf("Bullet fired\n");

    if(firing_bober.active_weapon == VETEV) {
        if(bulletc == 0) {
            bulletc++;
            bullets = malloc(sizeof(Bullet) * bulletc);
        }else{
            bulletc++;
            bullets = realloc(bullets, sizeof(Bullet) * bulletc);
        }           
        Bullet bullet = createBullet(firing_bober);
        bullet.x_vel = firing_bober.angle == 90 ? 1 : firing_bober.angle == 270 ? -1 : 0;
        bullet.y_vel = firing_bober.angle == 0 ? -1 : firing_bober.angle == 180 ? 1 : 0;

        bullets[bulletc-1] = bullet;
    }else if(firing_bober.active_weapon == PAREZ) {
        firing_bober.ammo--;
        if(bulletc == 0) {
            bulletc++;
            bullets = malloc(sizeof(Bullet) * bulletc);
        }else{
            bulletc++;
            bullets = realloc(bullets, sizeof(Bullet) * bulletc);
        }           
        Bullet bullet = createBullet(firing_bober);
        bullet.x_vel = firing_bober.angle == 90 ? 2 : firing_bober.angle == 270 ? -2 : 0;
        bullet.y_vel = firing_bober.angle == 0 ? -2 : firing_bober.angle == 180 ? 2 : 0;

        bullets[bulletc-1] = bullet;
    } else {
        if(bulletc == 0) {
            bulletc++;
            bullets = malloc(sizeof(Bullet) * bulletc);
        }else{
            bulletc++;
            bullets = realloc(bullets, sizeof(Bullet) * bulletc);
        }           
        Bullet bullet = createBullet(firing_bober);
        bullet.x_vel = firing_bober.angle == 90 ? 1 : firing_bober.angle == 270 ? -1 : 0;
        bullet.y_vel = firing_bober.angle == 0 ? -1 : firing_bober.angle == 180 ? 1 : 0;

        bullets[bulletc-1] = bullet;
    }    
};

void bulletLogic() {
    for (int i = 0; i < bulletc; i++) {
        bullets[i].rect.x = bullets[i].rect.x + bullets[i].x_vel * BULLETSPEED * getDeltaTime();
        bullets[i].rect.y = bullets[i].rect.y + bullets[i].y_vel * BULLETSPEED * getDeltaTime();
    }

    for (int i = 0; i < bulletc; i++) {
        if(bullets[i].rect.x >= 1400 || bullets[i].rect.x+BULLETSIZE <= 0) bullets[i].remove = true; 
        if(bullets[i].rect.y >= 800 || bullets[i].rect.y+BULLETSIZE <= 0) bullets[i].remove = true;
        if(WallRectCollision(bullets[i].rect)) bullets[i].remove = true;
    }

    int new_bulletc = 0;
    for (int i = 0; i < bulletc; i++) {
        if (!bullets[i].remove) {
            new_bulletc++;
        }
    }

    Bullet *new_bullets = malloc(sizeof(Bullet) * new_bulletc);
    int index = 0;
    for (int i = 0; i < bulletc; i++) {
        if (!bullets[i].remove) {
            new_bullets[index] = bullets[i];
            index++;
        }
    }

    free(bullets);
    bullets = new_bullets;
    bulletc = new_bulletc;    
};

void renderBullets() {
    for (int i = 0; i < bulletc; i++) {
        renderImageOnRect(bullet_texture, bullets[i].rect, 0, 0);
    }
};

void killBulletManager() {
    SDL_DestroyTexture(bullet_texture);
    if(bulletc > 0 || bullets != NULL) {
        free(bullets);
        bulletc = 0;
    }
};