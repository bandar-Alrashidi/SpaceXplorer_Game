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