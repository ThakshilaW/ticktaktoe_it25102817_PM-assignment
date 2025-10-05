#include<stdio.h>

void logMove(FILE *logFile, char** board, int size, char player, int row, int col)
{
    // Log the move details
    fprintf(logFile, "Player %c moved to (%d, %d)\n", player, row, col);
    fprintf(logFile, "Current board state:\n");

    // Log the board in a simple grid format
    for (int i = 0; i < size; i++)
    {
        fprintf(logFile, "|");
        for (int j = 0; j < size; j++)
        {
            fprintf(logFile, " %c |", board[i][j]);
        }
        fprintf(logFile, "\n");
    }
    fprintf(logFile, "--- End of turn ---\n\n");
}

