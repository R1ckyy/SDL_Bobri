#include "../../lib/screens/endgame/endgame.h"

#pragma once

#define FILENAME "leaderboard.skibidiuwu"
#define DELIM ",;\n"

typedef struct {
    char name[INPUTLENGTH];
    int points;
} LeaderboardData;

typedef struct {
    int entries;
    LeaderboardData *data;
} ReadData;

void writeIntoFile(char *name, int points);

void swap(LeaderboardData *a, LeaderboardData *b);

ReadData readFromFile();