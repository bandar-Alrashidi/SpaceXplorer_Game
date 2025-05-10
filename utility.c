#include "utility.h"

char wonMessage[5][61] = {
    " \\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | |",
    "  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| |",
    "   \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` |",
    "    | | | |__| | |__| |    \\  /\\  / | |__| | |\\  |",
    "    |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_|"};

char loseMessage[6][71] = {
    " __     ______  _    _   _      ____   _____ ______ ",
    " \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|  ____|",
    "  \\ \\_/ / |  | | |  | | | |   | |  | | (___ | |__   ",
    "   \\   /| |  | | |  | | | |   | |  | |\\___ \\|  __|  ",
    "    | | | |__| | |__| | | |___| |__| |____) | |____ ",
    "    |_|  \\____/ \\____/  |______\\____/|_____/|______|"};

void youWon()
{
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", wonMessage[i]);
    }
}

void youLose()
{
    for (int i = 0; i < 6; i++)
    {
        printf("%s\n", loseMessage[i]);
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}


void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void clearScreen()
{
    system("cls");
}

int displayIntro(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to open intro file.\n");
        return 1;
    }

    clearScreen();
    char line[256];
    char lastLine[256] = "";

    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
        Sleep(50);

        if (strlen(line) > 1)
        {
            strcpy(lastLine, line);
        }
    }

    fclose(file);

    printf("\n\nPress any key to start...");
    getch();

    int difficulty = 1;
    if (sscanf(lastLine, "The Difficulty Level is : %d", &difficulty) == 1)
    {
        return difficulty;
    }
    else
    {
        return 1;
    }
}

void printInstructions(int x, int y)
{
    gotoxy(x, y);
    printf("W,S,A and S - Move  Esc - Save and Quit");
}

int gameMenu()
{
    clearScreen();
    int choice;
    printf("+_____________________________________________________________+\n");
    printf("|                       MAIN MENU                             |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("| 1. Resume Game                                              |\n");
    printf("| 2. Start New Game                                           |\n");
    printf("| 3. Exit                                                     |\n");
    printf("+_____________________________________________________________+\n");
    printf("Please Enter your choice: ");

    scanf("%d", &choice);
    return choice;
}