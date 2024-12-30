#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/gamemgr/gamemgr.h"

#include "fileleaderboard.h"

void writeIntoFile(char *name, int points) {
    FILE *file = fopen(FILENAME, "a");
    if(file == NULL && isDebug()) {
        fprintf(stderr, "File %s failed to open", FILENAME);
        exit(1);
    }

    fprintf(file, "%s,%d;\n", name, points);

    fclose(file);
};

void swap(LeaderboardData *a, LeaderboardData *b) {
    LeaderboardData temp = *a;
    *a = *b;
    *b = temp;
    return;
};

ReadData readFromFile() {
    ReadData output;
    LeaderboardData *data = NULL;
    int entries = 0;

    FILE *file = fopen(FILENAME, "r");
    if(file == NULL) {
        output.entries = 0;
        output.data = NULL;
        return output;
    }

    char buf[50];
    while (fgets(buf, 50, file) != NULL) {
        if(entries == 0) {
            data = malloc(sizeof(LeaderboardData) * (entries+1));
            if(data == NULL && isDebug()) {
                fprintf(stderr, "Memory for Leaderboard data couldnt be allocated.\n");
                exit(1);
            }
            entries++;
        }else{
            data = realloc(data, sizeof(LeaderboardData) * (entries+1));
            if(data == NULL && isDebug()) {
                fprintf(stderr, "Memory for Leaderboard data couldnt be allocated.\n");
                exit(1);
            }
            entries++; 
        }

        LeaderboardData entry;
        char *token = strtok(buf, DELIM);
        int counter = 0;

        while (token != NULL) {
            switch (counter) {
            case 0:
                strcpy(entry.name, token);
                break;
            case 1:
                entry.points = atoi(token);
                break;
            default:
                break;
            }
            counter++;
            token = strtok(NULL, DELIM);
        }

        data[entries-1] = entry;
    }

    output.data = data;
    output.entries = entries;

    for (int i = 0; i < entries - 1; i++) {
        for (int j = 0; j < entries - i - 1; j++) {
            if (output.data[j].points < output.data[j + 1].points) swap(&output.data[j], &output.data[j + 1]);
        }
    }

    fclose(file);

    return output;
};