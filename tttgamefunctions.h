#ifndef TTTGAMEFUNCTIONS_H
#define TTTGAMEFUNCTIONS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//function declarations
char** Board(int size); //changed function name than earlier commits because why not
void freeBoard(char** board, int size);
void displayBoard(char** board, int size);

#endif
