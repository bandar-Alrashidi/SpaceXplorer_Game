#include <stdio.h>
#include "game.h"
#include <conio.h>
#include "utility.h"

void playGame()
{
    clearScreen();
    hideCursor();
    drawGrid();
    printPlayer();
    printInstructions(25, 18);
    while (1)
    {
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
