#include <stdio.h>
#include "game.h"
#include <conio.h>
#include "utility.h"

unsigned long lastAsteroidTime = 0;
unsigned long lastTimeUpdate = 0;
unsigned long lastBossBombTime = 0;

void startNewLevel()
{
    clearScreen();
    drawGrid();
    printPlayer();

    removeAsteroids();
    removeJunk();
    removeBullets();

    drawFinalBoss();
    bossActive = true;
}

void playGame()
{
    clearScreen();
    hideCursor();
    drawGrid();
    if (!bossActive)
    {
        spawnJunk();
    }
    printPlayer();
    printInstructions(50, 18);
    while (1)
    {
        printScore(50, 5);
        printHealth(50, 7);
        printTime(50, 9);
        unsigned long currentTime = GetTickCount();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
            moveAsteroidTowardsPlayer(Px, Py);
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
            moveAsteroidTowardsPlayer(Px, Py);
        }

        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
            moveAsteroidTowardsPlayer(Px, Py);
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
            moveAsteroidTowardsPlayer(Px, Py);
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
        }

        if (currentTime - lastTimeUpdate >= 1000 && GameTime > 0)
        {
            GameTime--;
            lastTimeUpdate = currentTime;
        }

        checkPlayerCollisions();
        moveBullets();
        checkBulletCollisions();

        if (!bossActive && PlayerScore >= 50)
        {
            startNewLevel();
        }

        if (bossActive)
        {
            printBossHealth(50, 11);
            moveFinalBoss();
            if (currentTime - lastBossBombTime >= 500)
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
