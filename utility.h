#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

extern char wonMessage[5][61];
extern char loseMessage[6][71];


void youWon();
void youLose();
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void clearScreen();
void hideCursor();
int displayIntro(const char *filename);
void printInstructions(int x, int y);
int gameMenu();

#endif