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


bool validMove(char** board, int size, int row, int col)
{
    // Check if coordinates are within the board boundaries
    if (row < 0 || row >= size || col < 0 || col >= size)
    {
        return false;
    }

    // Check if the target cell is empty
    if (board[row][col] != ' ')
    {
        return false;
    }

    return true;
}


bool checkWin(char** board, int size, char playerSymbol)
{
    bool foundWin;

    // Check all rows (horizontal lines)
    for (int row = 0; row < size; row++)
    {
        foundWin = true;

        // Check every cell in current row
        for (int col = 0; col < size; col++)
	{
            if (board[row][col] != playerSymbol)
	    {
                foundWin = false;
                break;
            }
	}
        
        if (foundWin) 
	{
            return true;
        }
    }

    // Check all columns (vertical lines)
    for (int col = 0; col < size; col++) 
    {
        foundWin = true;
        
        // Check every cell in current column
        for (int row = 0; row < size; row++)
       	{
            if (board[row][col] != playerSymbol) 
	    {
		foundWin = false;
                break;
            }
        }

        if (foundWin)
	{
            return true;
        }
    }

    // Check main diagonal (top-left to bottom-right)
    foundWin = true;
    for (int i = 0; i < size; i++)
    {
        if (board[i][i] != playerSymbol)
	{
            foundWin = false;
            break;
	}
    }
    if (foundWin)
    {
        return true;
    }

    // Check anti-diagonal (top-right to bottom-left)
    foundWin = true;
    for (int i = 0; i < size; i++)
    {
        if (board[i][size - 1 - i] != playerSymbol)
	{
            foundWin = false;
            break;
        }
    }
    if (foundWin)
    {
	    return true;
    }

    // No winning condition found
    return false;
}



bool checkDraw(char** board, int size)
{
    // Scan through every cell looking for empty spaces
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
	{
            if (board[row][col] == ' ')
	    {
                return false; // Found an empty cell - game can continue
            }
        }
    }

    // No empty cells found - game is a draw
    return true;
}



bool userInput(char** board, int size, int *row, int *col)
{
    while (true)
    {
        // Try to read two integers from input
        if (scanf("%d %d", row, col) != 2)
	{
            printf("Invalid input, enter TWO numbers (row column):\n");
            printf("> ");

            // Clear the input buffer to prevent infinite loop on bad input
            while (getchar() != '\n');
            continue;
        }

	// Check if the move is valid (within bounds and empty cell)
        if (validMove(board, size, *row, *col))
	{
            break; // Valid move received, exit loop
        } else
	{
            // Provide specific error message based on failure type
            if (*row < 0 || *row >= size || *col < 0 || *col >= size)
	    {
                printf("Position out of bounds, Use numbers 0 to %d:\n", size - 1);
            }
	    else if (board[*row][*col] != ' ')
	    {
                printf("That spot is already taken! Choose an empty cell:\n");
            }
            printf("> ");
        }
    }
}



int gameMode()
{
    int mode;
    printf("Select Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("Enter choice (1-2): ");

    while (true)
    {
        if (scanf("%d", &mode) != 1)
        {
            printf("Invalid input! Please enter 1 or 2: ");
            while (getchar() != '\n');
            continue;
        }

        if (mode == 1 || mode == 2)
        {
            break;
        }
        else
	{
            printf("Invalid choice! Please enter 1 or 2: ");
        }
    }
    return mode;
}



void computerMove(char** board, int size, int *row, int *col)
{
    // Generate random moves until a valid one is found
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!validMove(board, size, *row, *col));
    
    printf("Computer chooses position (%d, %d)\n", *row, *col);
}
