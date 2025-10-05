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
bool userInput(char** board, int size, int *row, int *col);
int gameMode();
void computerMove(char** board, int size, int *row, int *col);


#endif
