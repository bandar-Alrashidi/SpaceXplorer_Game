#include "game.h"
#include "utility.h"

int GameTime = 300;

char player[2] = {'/', '\\'};
int Px = 9;
int Py = 16;
int PlayerHealth = 100;
int PlayerScore = 0;


char Grid[GRID_ROWS][GRID_COLS] = {
    "+-+-+-+-+-+-+-+--+",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "|                |",
    "+-+-+-+-+-+-+-+--+"};


Asteroid asteroids[MAX_ASTEROIDS];
Junk junks[MAX_JUNK];
Bullet bullets[BULLET_COUNT];



void drawGrid()
{
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            putchar(Grid[i][j]);
        }
        putchar('\n');
    }
}

void printPlayer()
{
    gotoxy(Px, Py);
    for (int i = 0; i < 2; i++)
    {
        putchar(player[i]);
    }
}

void erasePlayer()
{
    gotoxy(Px, Py);
    for (int i = 0; i < 2; i++)
    {
        putchar(' ');
    }
}

void movePlayerUp()
{
    char next1 = getCharAtxy(Px, Py - 1);
    char next2 = getCharAtxy(Px + 1, Py - 1);
    if ((next1 == ' ' || next1 == '#') && (next2 == ' ' || next2 == '#'))
    {
        erasePlayer();
        Py--;
        printPlayer();
    }
}

void movePlayerDown()
{
    char next1 = getCharAtxy(Px, Py + 1);
    char next2 = getCharAtxy(Px + 1, Py + 1);
    if ((next1 == ' ' || next1 == '#') && (next2 == ' ' || next2 == '#'))
    {
        erasePlayer();
        Py++;
        printPlayer();
    }
}

void movePlayerLeft()
{
    char next = getCharAtxy(Px - 1, Py);
    if (next == ' ' || next == '#')
    {
        erasePlayer();
        Px = Px - 1;
        printPlayer();
    }
}

void movePlayerRight()
{
    char next = getCharAtxy(Px + 2, Py);
    if (next == ' ' || next == '#')
    {
        erasePlayer();
        Px = Px + 1;
        printPlayer();
    }
}

void printBullet(int x, int y)
{
    gotoxy(x, y);
    putchar('.');
}

void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    putchar(' ');
}

void generateBullet()
{
    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = Px + 1;
            bullets[i].y = Py - 1;
            bullets[i].active = true;
            printBullet(bullets[i].x, bullets[i].y);
            break;
        }
    }
}

void moveBullets()
{
    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (bullets[i].active)
        {
            char next = getCharAtxy(bullets[i].x, bullets[i].y - 1);
            if (next == ' ')
            {
                eraseBullet(bullets[i].x, bullets[i].y);
                bullets[i].y = bullets[i].y - 1;
                printBullet(bullets[i].x, bullets[i].y);
            }
            else
            {
                eraseBullet(bullets[i].x, bullets[i].y);
                bullets[i].active = false;
            }
        }
    }
}

void spawnAsteroid()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].active)
        {
            asteroids[i].x = rand() % (GRID_COLS - 2) + 1;
            asteroids[i].y = 1;
            asteroids[i].active = true;
            asteroids[i].health = 1;
            gotoxy(asteroids[i].x, asteroids[i].y);
            putchar('*');
            break;
        }
    }
}

void spawnJunk()
{
    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (!junks[i].active)
        {
            junks[i].x = rand() % (GRID_COLS - 2) + 1;
            junks[i].y = rand() % (GRID_ROWS - 2) + 1;
            char spot = getCharAtxy(junks[i].x, junks[i].y);
            if (spot == ' ')
            {
                junks[i].active = true;
                junks[i].spawnTime = time(NULL);
                gotoxy(junks[i].x, junks[i].y);
                putchar('#');
                gotoxy(25, 15);
            }
            break;
        }
    }
}

void moveAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active)
        {
            char next = getCharAtxy(asteroids[i].x, asteroids[i].y + 1);
            if (next == ' ' || next == '#')
            {
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar(' ');
                asteroids[i].y++;
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar('*');
            }

            else if (next == '+' || next == '-')
            {
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar(' ');
                asteroids[i].y = 0;
                asteroids[i].active = false;
            }
        }
    }
}

void printScore(int x, int y)
{
    gotoxy(x, y);
    printf("Score : %d      ", PlayerScore);
}

void printHealth(int x, int y)
{
    gotoxy(x, y);
    printf("Player Health : %d      ", PlayerHealth);
}

void printBossHealth(int x, int y)
{
    gotoxy(x, y);
    printf("Boss Health : %d        ", bossHealth);
}

void printTime(int x, int y)
{
    int minutes = GameTime / 60;
    int seconds = GameTime % 60;
    gotoxy(x, y);
    printf("Time Left : %01d:%02d       ", minutes, seconds);
}