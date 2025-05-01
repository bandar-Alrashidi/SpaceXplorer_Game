#include <stdio.h>
#include "game.h"
#include <conio.h>
#include "utility.h"

unsigned long lastAsteroidTime = 0;
unsigned long lastJunkTime = 0;

void playGame()
{
    clearScreen();
    hideCursor();
    drawGrid();
    printPlayer();
    printInstructions(25, 18);
    while (1)
    {
        printScore(25, 5);
        printHealth(25, 7);
        printTime(25, 9);
        printBossHealth(25, 11);
        unsigned long currentTime = GetTickCount();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }

        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }

        if (currentTime - lastAsteroidTime >= 5000)
        {
            spawnAsteroid();
            lastAsteroidTime = currentTime;
        }

        if (currentTime - lastJunkTime >= 10000)
        {
            spawnJunk();
            lastJunkTime = currentTime;
        }
        moveAsteroids();
        checkPlayerCollisions();
        moveBullets();
        checkBulletCollisions();
        removeExpiredJunk();
        
        Sleep(100);
    }
    gotoxy(1, 15);
}

int main()
{
    displayIntro("intro.txt");
    int choice = 0;
    while (choice != 3)
    {
        choice = gameMenu();
        if (choice == 1)
        {
            playGame();
        }
        else if (choice == 2)
        {
            playGame();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("Please Enter a valid choice");
            getch();
        }
    }

    return 0;
}