#include "game.h"
#include "utility.h"

int GameTime = 300;

char player[2] = {'/', '\\'};
int Px = 9;
int Py = 16;
int PlayerHealth = 100;
int PlayerScore = 0;

char finalBoss[2][4] = {
    "^@^",
    "/_\\"};
int Bx = 3;
int By = 2;
char direction = 'R';
bool bossActive = false;
int bossHealth = 100;

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

void spawnAsteroid()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (!asteroids[i].active)
        {
            asteroids[i].x = rand() % (GRID_COLS - 2) + 1;
            asteroids[i].y = 1;
            asteroids[i].active = true;
            asteroids[i].health = 1;
            gotoxy(asteroids[i].x, asteroids[i].y);
            putchar('*');
            break;
        }
    }
}

void spawnJunk()
{
    for (int i = 0; i < MAX_JUNK; i++)
    {
        if (!junks[i].active)
        {
            junks[i].x = rand() % (GRID_COLS - 2) + 1;
            junks[i].y = rand() % (GRID_ROWS - 2) + 1;
            char spot = getCharAtxy(junks[i].x, junks[i].y);
            if (spot == ' ')
            {
                junks[i].active = true;
                junks[i].spawnTime = time(NULL);
                gotoxy(junks[i].x, junks[i].y);
                putchar('#');
                gotoxy(25, 15);
            }
            break;
        }
    }
}

void moveAsteroids()
{
    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        if (asteroids[i].active)
        {
            char next = getCharAtxy(asteroids[i].x, asteroids[i].y + 1);
            if (next == ' ' || next == '#')
            {
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar(' ');
                asteroids[i].y++;
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar('*');
            }

            else if (next == '+' || next == '-')
            {
                gotoxy(asteroids[i].x, asteroids[i].y);
                putchar(' ');
                asteroids[i].y = 0;
                asteroids[i].active = false;
            }
        }
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
            ((junks[i].x == Px && junks[i].y == Py) || (junks[i].x == Px + 1 && junks[i].y == Py)))
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
            putchar(' ');
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
            putchar(' ');
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
                        putchar(' ');
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
                    eraseBullet(bullets[i].x, bullets[i].y);

                    bossBombs[j].health--;

                    if (bossBombs[j].health <= 0)
                    {
                        bossBombs[j].active = false;
                        gotoxy(bossBombs[j].x, bossBombs[j].y);
                        putchar(' ');
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
                putchar(' ');

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
        return;

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
        return;

    fscanf(file, "%d %d %d %d %d\n", &Px, &Py, &PlayerHealth, &PlayerScore, &GameTime);

    int bossActiveInt;
    fscanf(file, "%d %d %c %d %d\n", &Bx, &By, &direction, &bossActiveInt, &bossHealth);
    bossActive = (bool)bossActiveInt;

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        fscanf(file, "%d %d %d %d\n", &asteroids[i].x, &asteroids[i].y, &asteroids[i].active, &asteroids[i].health);
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        fscanf(file, "%d %d %d %ld\n", &junks[i].x, &junks[i].y, &junks[i].active, &junks[i].spawnTime);
    }

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        fscanf(file, "%d %d %d\n", &bullets[i].x, &bullets[i].y, &bullets[i].active);
    }

    fclose(file);
}

void resetGameState(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return;

    Px = 9;
    Py = 16;
    PlayerHealth = 100;
    PlayerScore = 0;
    GameTime = 300;

    Bx = 3;
    By = 2;
    direction = 'R';
    bossActive = false;
    bossHealth = 100;

    fprintf(file, "%d %d %d %d %d\n", Px, Py, PlayerHealth, PlayerScore, GameTime);
    fprintf(file, "%d %d %c %d %d\n", Bx, By, direction, bossActive, bossHealth);

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        asteroids[i].x = 0;
        asteroids[i].y = 0;
        asteroids[i].active = 0;
        asteroids[i].health = 0;
        fprintf(file, "%d %d %d %d\n", 0, 0, 0, 0);
    }

    for (int i = 0; i < MAX_JUNK; i++)
    {
        junks[i].x = 0;
        junks[i].y = 0;
        junks[i].active = 0;
        junks[i].spawnTime = 0;
        fprintf(file, "%d %d %d %ld\n", 0, 0, 0, 0L);
    }

    for (int i = 0; i < BULLET_COUNT; i++)
    {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].active = 0;
        fprintf(file, "%d %d %d\n", 0, 0, 0);
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

            else if (next == '+' || next == '-')
            {
                gotoxy(bossBombs[i].x, bossBombs[i].y);
                putchar(' ');
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