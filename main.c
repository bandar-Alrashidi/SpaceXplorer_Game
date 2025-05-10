#include <stdio.h>
#include "game.h"
#include <conio.h>
#include "utility.h"

unsigned long lastAsteroidTime = 0;
unsigned long lastTimeUpdate = 0;

void playGame()
{
    clearScreen();
    hideCursor();
    drawGrid();

    spawnJunk();
    printPlayer();
    printInstructions(50, 18);
    while (1)
    {
        printScore(50, 5);
        printHealth(50, 7);
        printFuel(50, 9);
        printJunkCollection(50, 11);
        showDifficulty(50, 13);
        unsigned long currentTime = GetTickCount();
        if (GetAsyncKeyState('A') & 0x8000)
        {
            movePlayerLeft();
            moveAsteroidTowardsPlayer(Px, Py);
            reduceFuel();
        }

        if (GetAsyncKeyState('D') & 0x8000)
        {
            movePlayerRight();
            moveAsteroidTowardsPlayer(Px, Py);
            reduceFuel();
        }

        if (GetAsyncKeyState('W') & 0x8000)
        {
            movePlayerUp();
            moveAsteroidTowardsPlayer(Px, Py);
            reduceFuel();
        }

        if (GetAsyncKeyState('S') & 0x8000)
        {
            movePlayerDown();
            moveAsteroidTowardsPlayer(Px, Py);
            reduceFuel();
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            saveGameState("gameState.txt");
            break;
        }

        if (currentTime - lastAsteroidTime >= 5000)
        {
            spawnAsteroid();
            lastAsteroidTime = currentTime;
        }

        checkPlayerCollisions();

        if (PlayerHealth <= 0 || Fuel <= 0)
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

        if(junkCollected >= junkTarget)
        {
            clearScreen();
            youWon();
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
    int diff = displayIntro("intro.txt");
    setDifficulty(diff);
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
