#include "game.h"
#include "utility.h"

int Fuel = 100;

char player = 'S';
int Px = 23;
int Py = 18;
int PlayerHealth = 100;
int PlayerScore = 0;

int fuelDepletion = 1;
int healthDepletion = 10;
int difficultyLevel = 1;
int junkCollected = 0;
int junkTarget = 10;

char Grid[GRID_ROWS][GRID_COLS] = {
    "+---------------------------------------+",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "|. . . . . . . . . . . . . . . . . . . .|",
    "+---------------------------------------+",
};

Asteroid asteroids[MAX_ASTEROIDS];
Junk junks[MAX_JUNK];

void setDifficulty(int level)
{
    difficultyLevel = level;
    if (level == 1)
    {
        fuelDepletion = 1;
        healthDepletion = 10;
        junkTarget = 10;
    }
    else if (level == 2)
    {
        fuelDepletion = 2;
        healthDepletion = 20;
        junkTarget = 15;
    }
    else if (level == 3)
    {
        fuelDepletion = 3;
        healthDepletion = 30;
        junkTarget = 20;
    }
}
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
    putchar(player);
}

void erasePlayer()
{
    gotoxy(Px, Py);
    putchar(' ');
}

void movePlayerUp()
{
    char next = getCharAtxy(Px, Py - 1);

    if (next == '.' || next == '#')
    {
        gotoxy(Px, Py);
        printf(".");

        Py = Py - 1;
        printPlayer();
    }
}

void movePlayerDown()
{
    char next = getCharAtxy(Px, Py + 1);

    if (next == '.' || next == '#')
    {
        gotoxy(Px, Py);
        printf(".");

        Py = Py + 1;
        printPlayer();
    }
}

void movePlayerLeft()
{
    char next = getCharAtxy(Px - 2, Py);

    if (next == '.' || next == '#')
    {
        gotoxy(Px, Py);
        printf(".");

        Px = Px - 2;
        printPlayer();
    }
}

void movePlayerRight()
{
    char next = getCharAtxy(Px + 2, Py);

    if (next == '.' || next == '#')
    {
        gotoxy(Px, Py);
        printf(".");

        Px = Px + 2;
        printPlayer();
    }
}

void spawnAsteroid()
{
    if (!asteroids[0].active)
    {
        asteroids[0].x = 1 + (rand() % ((GRID_COLS - 2) / 2)) * 2;
        asteroids[0].y = 1;
        asteroids[0].active = true;
        asteroids[0].health = 1;

        gotoxy(asteroids[0].x, asteroids[0].y);
        putchar('a');
    }
}

void spawnJunk()
{
    int count = 0;

    while (count < MAX_JUNK)
    {
        int row = 1 + rand() % 20;
        int col = 1 + (rand() % 21) * 2;

        char spot = getCharAtxy(col, row);

        if (spot == '.')
        {
            int occupied = 0;
            for (int j = 0; j < count; j++)
            {
                if (junks[j].x == col && junks[j].y == row)
                {
                    occupied = 1;
                    break;
                }
            }
            if (occupied)
                continue;

            junks[count].x = col;
            junks[count].y = row;
            junks[count].active = true;
            junks[count].spawnTime = time(NULL);

            gotoxy(col, row);
            putchar('#');
            count++;
        }
    }
}

void reduceFuel()
{
    Fuel = Fuel - fuelDepletion;
}
void reduceHealth()
{
    PlayerHealth = PlayerHealth - healthDepletion;
}

void moveAsteroidTowardsPlayer(int playerX, int playerY)
{
    if (!asteroids[0].active)
        return;

    gotoxy(asteroids[0].x, asteroids[0].y);
    putchar('.');

    if (asteroids[0].x < playerX)
        asteroids[0].x += 2;
    else if (asteroids[0].x > playerX)
        asteroids[0].x -= 2;

    if (asteroids[0].y < playerY)
        asteroids[0].y += 1;

    gotoxy(asteroids[0].x, asteroids[0].y);
    putchar('a');
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

void printFuel(int x, int y)
{
    gotoxy(x, y);
    printf("Remaining Fuel : %d      ", Fuel);
}

void printJunkCollection(int x, int y)
{
    gotoxy(x, y);
    printf("Junk Collected : %d/%d      ", junkCollected, junkTarget);
}

void showDifficulty(int x, int y)
{
    gotoxy(x, y);
    printf("Difficulty Level is : %d      ", difficultyLevel);
}

void checkPlayerCollisions()
{
    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (junks[i].active &&
            (junks[i].x == Px && junks[i].y == Py))
        {
            junks[i].active = false;
            gotoxy(junks[i].x, junks[i].y);
            putchar('S');
            PlayerScore += 5;
            junkCollected++;
        }
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active &&
            ((asteroids[i].x == Px && asteroids[i].y == Py)))
        {
            asteroids[i].active = false;
            gotoxy(asteroids[i].x, asteroids[i].y);
            putchar('.');
            reduceHealth();
        }
    }
}

void saveGameState(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file for saving game state");
        return;
    }

    fprintf(file, "%d %d %d %d %d\n", Px, Py, PlayerHealth, PlayerScore, Fuel, junkCollected);

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        fprintf(file, "%d %d %d %d\n", asteroids[i].x, asteroids[i].y, asteroids[i].active, asteroids[i].health);
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        fprintf(file, "%d %d %d %ld\n", junks[i].x, junks[i].y, junks[i].active, junks[i].spawnTime);
    }

    fclose(file);
}

void loadGameState(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file for loading game state");
        return;
    }

    if (fscanf(file, "%d %d %d %d %d\n", &Px, &Py, &PlayerHealth, &PlayerScore, &Fuel, &junkCollected) != 5)
    {
        fprintf(stderr, "Error reading player data from file\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (fscanf(file, "%d %d %d %d\n", &asteroids[i].x, &asteroids[i].y, &asteroids[i].active, &asteroids[i].health) != 4)
        {
            fprintf(stderr, "Error reading asteroid data from file\n");
            fclose(file);
            return;
        }
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (fscanf(file, "%d %d %d %ld\n", &junks[i].x, &junks[i].y, &junks[i].active, &junks[i].spawnTime) != 4)
        {
            fprintf(stderr, "Error reading junk data from file\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
}

void resetGameState(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file to reset game state");
        return;
    }

    Px = 23;
    Py = 18;
    PlayerHealth = 100;
    PlayerScore = 0;
    Fuel = 100;
    junkCollected = 0;

    if (fprintf(file, "%d %d %d %d %d\n", Px, Py, PlayerHealth, PlayerScore, Fuel, junkCollected) < 0)
    {
        perror("Error writing player data to file");
        fclose(file);
        return;
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        asteroids[i].x = 0;
        asteroids[i].y = 0;
        asteroids[i].active = 0;
        asteroids[i].health = 0;
        if (fprintf(file, "%d %d %d %d\n", 0, 0, 0, 0) < 0)
        {
            perror("Error writing asteroid data to file");
            fclose(file);
            return;
        }
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        junks[i].x = 0;
        junks[i].y = 0;
        junks[i].active = 0;
        junks[i].spawnTime = 0;
        if (fprintf(file, "%d %d %d %ld\n", 0, 0, 0, 0L) < 0)
        {
            perror("Error writing junk data to file");
            fclose(file);
            return;
        }
    }

    fclose(file);
}
