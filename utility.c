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

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void displayIntro(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Failed to open intro file.\n");
        return;
    }

    clearScreen();
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
        Sleep(50);
    }
    fclose(file);

    printf("\n\nPress any key to start...");
    getch();
}

void printInstructions(int x, int y)
{
    gotoxy(x, y);
    printf("Arrow Keys - Move   Space - Right Fire  Back - Left Fire   Esc - Save and Quit");
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

char *askPlayerName()
{
    clearScreen();
    static char name[100];
    printf("+_____________________________________________________________+\n");
    printf("|                       PLAYER INFO                           |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("Enter the player name: ");
    scanf("%99s", name);
    return name;
}

void showPlayerName(int x, int y, char* name)
{
    gotoxy(x, y);
    printf("Player : %s    ", name);
}