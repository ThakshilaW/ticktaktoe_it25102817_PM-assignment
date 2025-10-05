#ifndef TTTGAMELOGICNINPUTFUNC_H
#define TTTGAMELOGICNINPUTFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//function declarations
bool validMove(char** board, int size, int row, int col);
bool checkWin(char** board, int size, char playerSymbol);
bool checkDraw(char** board, int size);
void userInput(char** board, int size, int *row, int *col, int playerNum);
int gameMode();
void computerMove(char** board, int size, int *row, int *col);
char playerSymbol(int playerNumber);//added for part 3 of the game
int playerType(int playerNum, int gameMode); //to check if playwr is human or the computer

#endif
