#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>
#include "utility.h"

#define GRID_ROWS 22
#define GRID_COLS 41
#define MAX_JUNK 30
#define MAX_ASTEROIDS 10
#define BULLET_COUNT 10000
#define MAX_BOSS_BOMBS 100


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

typedef struct
{
    int x, y;
    bool active;
    int health;
} Bomb;

extern int GameTime;

extern char player;
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
extern Bomb bossBombs[MAX_BOSS_BOMBS];


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
// void generateLeftBullet();
void moveBullets();
void spawnAsteroid();
void spawnJunk();
void moveAsteroids();
void moveAsteroidTowardsPlayer(int playerX, int playerY);
void printScore(int x, int y);
void printHealth(int x, int y);
void printBossHealth(int x, int y);
void printTime(int x, int y);
void checkPlayerCollisions();
void checkBulletCollisions();
void removeExpiredJunk();
void saveGameState(const char *filename);
void loadGameState(const char *filename);
void drawFinalBoss();
void moveFinalBoss();
void spawnBossBomb(int x, int y);
void moveBossBombs();
void removeAsteroids();
void removeJunk();
void removeBullets();
void resetGameState(const char *filename);



#endif
