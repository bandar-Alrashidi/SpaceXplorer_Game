#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>
#include "utility.h"

#define GRID_ROWS 18
#define GRID_COLS 18

extern int GameTime;

extern char player[2];
extern int Px;
extern int Py;
extern int PlayerHealth;
extern int PlayerScore;

extern char finalBoss[2][4];
extern int Bx;
extern int By;
extern char direction;
extern bool bossActive;
extern int bossHealth;

extern char Grid[GRID_ROWS][GRID_COLS];

void drawGrid();
void printPlayer();
void erasePlayer();
void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();

#endif
