#include <stdio.h>
#include "game.h"
#include <conio.h>
#include "utility.h"

unsigned long lastAsteroidTime = 0;
unsigned long lastJunkTime = 0;
unsigned long lastTimeUpdate = 0;
unsigned long lastBossBombTime = 0;
void startNewLevel()
{
    clearScreen();
    drawGrid();
    Px = 9;
    Py = 16;
    printPlayer();

    drawFinalBoss();
    bossActive = true;
}


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

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            saveGameState("gameState.txt");
            break;
        }
        if (!bossActive)
        {

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
        }

        if (currentTime - lastTimeUpdate >= 1000 && GameTime > 0)
        {
            GameTime--;
            lastTimeUpdate = currentTime;
        }

        checkPlayerCollisions();
        moveBullets();
        checkBulletCollisions();
        removeExpiredJunk();

        if (!bossActive && PlayerScore >= 50)
        {
            startNewLevel();
        }

        if (bossActive)
        {
            moveFinalBoss();
            if (currentTime - lastBossBombTime >= 1500)
            {
                spawnBossBomb(Bx + 1, By + 1);
                lastBossBombTime = currentTime;
            }
            moveBossBombs();
        }

        if (bossHealth <= 0)
        {
            clearScreen();
            youWon();
            printf("\n\nPress any key to play again...");
            getch();
            resetGameState("gameState.txt");
            break;
        }

        if (PlayerHealth <= 0 || GameTime <= 0)
        {
            clearScreen();
            youLose();
            while (kbhit())
                getch();
            printf("\n\nPress any key to play again...");
            getch();
            resetGameState("gameState.txt");
            break;
        }

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
            loadGameState("gameState.txt");
            playGame();
        }
        else if (choice == 2)
        {
            resetGameState("gameState.txt");
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