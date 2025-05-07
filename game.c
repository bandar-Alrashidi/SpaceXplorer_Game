#include "game.h"
#include "utility.h"

int GameTime = 300;

char player = 'S';
int Px = 23;
int Py = 18;
int PlayerHealth = 100;
int PlayerScore = 0;

char finalBoss[2][4] = {
    "^@^",
    "/_\\"};
int Bx = 2;
int By = 0;
char direction = 'R';
bool bossActive = false;
int bossHealth = 100;

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
Bullet bullets[BULLET_COUNT];
Bomb bossBombs[MAX_BOSS_BOMBS];

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

void printBullet(int x, int y)
{
    gotoxy(x, y);
    putchar('^');
}

void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    putchar(' ');
}

void generateBullet()
{
    int targetX = Px;
    int targetY = Py - 1;

    char next = getCharAtxy(targetX, targetY);
    if (next != 'S' && next != '.')
        return;

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].x = targetX;
            bullets[i].y = targetY;
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

            if (next == '.' || next == 'S')
            {
                gotoxy(bullets[i].x, bullets[i].y);
                putchar('.');
                bullets[i].y -= 1;
                printBullet(bullets[i].x, bullets[i].y);
            }
            
            else if (next == '#' || next == '-' || next == '+')
            {
                bullets[i].active = false;
                gotoxy(bullets[i].x, bullets[i].y);
                if(!bossActive)
                {
                    putchar('.');
                }
                else
                {
                    putchar(' ');
                }
            }

            else if (next == ' ')
            {
                eraseBullet(bullets[i].x, bullets[i].y);
                bullets[i].y -= 1;
                printBullet(bullets[i].x, bullets[i].y);
            }
        }
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

    if (asteroids[0].x == playerX && asteroids[0].y == playerY)
    {
        asteroids[0].active = false;
        PlayerHealth = PlayerHealth - 100;
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

void checkPlayerCollisions()
{
    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (junks[i].active &&
            (junks[i].x == Px && junks[i].y == Py))
        {
            junks[i].active = false;
            gotoxy(junks[i].x, junks[i].y);
            putchar(' ');
            PlayerScore += 5;
            GameTime += 2;
        }
    }

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active &&
            ((asteroids[i].x == Px && asteroids[i].y == Py) ||
             (asteroids[i].x == Px + 1 && asteroids[i].y == Py) ||
             (asteroids[i].x == Px && asteroids[i].y == Py - 1) ||
             (asteroids[i].x == Px + 1 && asteroids[i].y == Py - 1) ||
             (asteroids[i].x == Px && asteroids[i].y == Py + 1) ||
             (asteroids[i].x == Px + 1 && asteroids[i].y == Py + 1)))
        {
            asteroids[i].active = false;
            gotoxy(asteroids[i].x, asteroids[i].y);
            putchar('.');
            PlayerHealth -= 100;
        }
    }

    for (int i = 0; i < MAX_BOSS_BOMBS; i++)
    {
        if (bossBombs[i].active &&
            ((bossBombs[i].x == Px && bossBombs[i].y == Py) ||
             (bossBombs[i].x == Px + 1 && bossBombs[i].y == Py) ||
             (bossBombs[i].x == Px && bossBombs[i].y == Py - 1) ||
             (bossBombs[i].x == Px + 1 && bossBombs[i].y == Py - 1)))
        {
            bossBombs[i].active = false;
            gotoxy(bossBombs[i].x, bossBombs[i].y);
            putchar('.');
            PlayerHealth -= 10;
        }
    }
}

void checkBulletCollisions()
{
    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (bullets[i].active)
        {
            for (int j = 0; j < MAX_ASTEROIDS; j++)
            {
                if (asteroids[j].active &&
                    bullets[i].x == asteroids[j].x &&
                    bullets[i].y - 1 == asteroids[j].y)
                {
                    bullets[i].active = false;
                    eraseBullet(bullets[i].x, bullets[i].y);

                    asteroids[j].health--;
                    if (asteroids[j].health <= 0)
                    {
                        asteroids[j].active = false;
                        gotoxy(asteroids[j].x, asteroids[j].y);
                        putchar('.');
                        PlayerScore += 10;
                    }
                    break;
                }
            }
            for (int j = 0; j < MAX_BOSS_BOMBS; j++)
            {
                if (bossBombs[j].active &&
                    bullets[i].x == bossBombs[j].x &&
                    bullets[i].y - 1 == bossBombs[j].y)
                {
                    bullets[i].active = false;
                    gotoxy(bullets[i].x, bullets[i].y);
                    putchar('.');

                    bossBombs[j].health--;

                    if (bossBombs[j].health <= 0)
                    {
                        bossBombs[j].active = false;
                        gotoxy(bossBombs[j].x, bossBombs[j].y);
                        putchar('.');
                        PlayerScore += 5;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (bullets[i].active && bossActive)
        {
            if ((bullets[i].x >= Bx && bullets[i].x <= Bx + 2) &&
                (bullets[i].y >= By && bullets[i].y <= By + 2))
            {
                bullets[i].active = false;
                gotoxy(bullets[i].x, bullets[i].y);
                putchar('.');

                bossHealth -= 5;
                PlayerScore += 2;
            }
        }
    }
}

void removeExpiredJunk()
{
    time_t currentTime = time(NULL);
    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (junks[i].active && difftime(currentTime, junks[i].spawnTime) >= 5)
        {
            junks[i].active = false;
            gotoxy(junks[i].x, junks[i].y);
            putchar(' ');
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

    fprintf(file, "%d %d %d %d %d\n", Px, Py, PlayerHealth, PlayerScore, GameTime);

    fprintf(file, "%d %d %c %d %d\n", Bx, By, direction, bossActive, bossHealth);

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        fprintf(file, "%d %d %d %d\n", asteroids[i].x, asteroids[i].y, asteroids[i].active, asteroids[i].health);
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        fprintf(file, "%d %d %d %ld\n", junks[i].x, junks[i].y, junks[i].active, junks[i].spawnTime);
    }

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        fprintf(file, "%d %d %d\n", bullets[i].x, bullets[i].y, bullets[i].active);
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

    if (fscanf(file, "%d %d %d %d %d\n", &Px, &Py, &PlayerHealth, &PlayerScore, &GameTime) != 5)
    {
        fprintf(stderr, "Error reading player data from file\n");
        fclose(file);
        return;
    }

    int bossActiveInt;
    if (fscanf(file, "%d %d %c %d %d\n", &Bx, &By, &direction, &bossActiveInt, &bossHealth) != 5)
    {
        fprintf(stderr, "Error reading boss data from file\n");
        fclose(file);
        return;
    }
    bossActive = (bossActiveInt != 0);

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

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (fscanf(file, "%d %d %d\n", &bullets[i].x, &bullets[i].y, &bullets[i].active) != 3)
        {
            fprintf(stderr, "Error reading bullet data from file\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
}

void drawFinalBoss()
{
    gotoxy(Bx, By);
    printf("%s", finalBoss[0]);
    gotoxy(Bx, By + 1);
    printf("%s", finalBoss[1]);
}

void moveFinalBoss()
{
    gotoxy(Bx, By);
    printf("   ");
    gotoxy(Bx, By + 1);
    printf("   ");

    if (direction == 'R')
    {
        Bx++;
        if (Bx >= GRID_COLS - 4)
            direction = 'L';
    }
    else
    {
        Bx--;
        if (Bx <= 1)
            direction = 'R';
    }

    drawFinalBoss();
}

void spawnBossBomb(int x, int y)
{
    for (int i = 0; i < MAX_BOSS_BOMBS; i++)
    {
        if (!bossBombs[i].active)
        {
            bossBombs[i].x = x;
            bossBombs[i].y = y;
            bossBombs[i].active = true;
            bossBombs[i].health = 3;
            break;
        }
    }
}

void moveBossBombs()
{
    for (int i = 0; i < MAX_BOSS_BOMBS; i++)
    {
        if (bossBombs[i].active)
        {
            char next = getCharAtxy(bossBombs[i].x, bossBombs[i].y + 1);
            if (next == ' ')
            {
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                putchar(' ');
                bossBombs[i].y++;
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                putchar('o');
            }

            if (next == '.')
            {
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                putchar('.');
                bossBombs[i].y++;
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                putchar('o');
            }

            else if (next == '+' || next == '-')
            {
                char back = getCharAtxy(bossBombs[i].x, bossBombs[i].y-1);
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                if(back == '.')
                {
                    putchar('.');
                }
                else
                {
                    putchar(' ');
                }
                bossBombs[i].y = 0;
                bossBombs[i].active = false;
            }

            if ((bossBombs[i].x == Px || bossBombs[i].x == Px + 1) && bossBombs[i].y == Py)
            {
                PlayerHealth -= 10;
                bossBombs[i].active = false;
            }
        }
    }
}

void removeAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        asteroids[i].active = false;
    }
}

void removeJunk()
{
    for (int i = 0; i < MAX_JUNK; i++)
    {
        junks[i].active = false;
    }
}

void removeBullets()
{
    for (int i = 0; i < BULLET_COUNT; i++)
    {
        bullets[i].active = false;
    }
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
    GameTime = 300;

    Bx = 3;
    By = 1;
    direction = 'R';
    bossActive = false;
    bossHealth = 100;

    if (fprintf(file, "%d %d %d %d %d\n", Px, Py, PlayerHealth, PlayerScore, GameTime) < 0)
    {
        perror("Error writing player data to file");
        fclose(file);
        return;
    }

    if (fprintf(file, "%d %d %c %d %d\n", Bx, By, direction, bossActive, bossHealth) < 0)
    {
        perror("Error writing boss data to file");
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

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].active = 0;
        if (fprintf(file, "%d %d %d\n", 0, 0, 0) < 0)
        {
            perror("Error writing bullet data to file");
            fclose(file);
            return;
        }
    }

    fclose(file);
}
