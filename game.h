#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h>
#include "utility.h"

#define GRID_ROWS 22
#define GRID_COLS 41
#define MAX_JUNK 40
#define MAX_ASTEROIDS 10


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


extern int Fuel;

extern char player;
extern int Px;
extern int Py;
extern int PlayerHealth;
extern int PlayerScore;

extern int healthDepletion;
extern int fuelDepletion;
extern int difficultyLevel;
extern int junkCollected;
extern int junkTarget;

extern char Grid[GRID_ROWS][GRID_COLS];

extern Asteroid asteroids[MAX_ASTEROIDS];
extern Junk junks[MAX_JUNK];


void setDifficulty(int level);
void drawGrid();
void printPlayer();
void erasePlayer();
void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();
void spawnAsteroid();
void spawnJunk();
void reduceFuel();
void reduceHealth();
void moveAsteroidTowardsPlayer(int playerX, int playerY);
void printScore(int x, int y);
void printHealth(int x, int y);
void printFuel(int x, int y);
void printJunkCollection(int x, int y);
void showDifficulty(int x, int y);
void checkPlayerCollisions();
void saveGameState(const char *filename);
void loadGameState(const char *filename);
void resetGameState(const char *filename);



#endif
