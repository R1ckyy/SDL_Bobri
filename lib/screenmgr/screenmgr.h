#ifndef SCREENMGR_H
#define SCREENMGR_H

enum Screens {
    MENU,
    SETTINGS,
    LEADERBOARD,
    INGAME
};

void setActiveScreen(enum Screens);

enum Screens getActiveScreen();

void renderActiveScreen();

#endif