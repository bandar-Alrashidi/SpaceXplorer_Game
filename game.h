#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>
#include "utility.h"

#define GRID_ROWS 18
#define GRID_COLS 18
#define MAX_JUNK 30
#define MAX_ASTEROIDS 10
#define BULLET_COUNT 10000



typedef struct
{
    int x;
    int y;
    bool active;
    int health;
} Asteroid;

typedef struct
{
    int x;
    int y;
    bool active;
    time_t spawnTime;
} Junk;

typedef struct
{
    int x;
    int y;
    bool active;
} Bullet;


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

extern Asteroid asteroids[MAX_ASTEROIDS];
extern Junk junks[MAX_JUNK];
extern Bullet bullets[BULLET_COUNT];


void drawGrid();
void printPlayer();
void erasePlayer();
void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void generateBullet();
void moveBullets();
void spawnAsteroid();
void spawnJunk();
void moveAsteroids();

#endif