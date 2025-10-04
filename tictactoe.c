/**
 * TIC-TAC-TOE GAME
 * Part 1: Two Players | Part 2: Player vs Computer
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function declarations
char** createBoard(int size);
void freeBoard(char** board, int size);
void displayBoard(char** board, int size);
bool isValidMove(char** board, int size, int row, int col);
void getUserInput(char** board, int size, int *row, int *col);
bool checkWin(char** board, int size, char playerSymbol);
bool checkDraw(char** board, int size);
void logMove(FILE *logFile, char** board, int size, char player, int row, int col);
int getGameMode();
void makeComputerMove(char** board, int size, int *row, int *col);

char** createBoard(int size) 
{
    // Allocate memory for array of row pointers
    char** newBoard = (char**)malloc(size * sizeof(char*));
    
    if (newBoard == NULL) 
    {
        printf("Memory allocation failed (row)\n");
        exit(1);
    }

    // Allocate memory for each row and initialize with empty spaces
    for (int row = 0; row < size; row++) 
    {
        newBoard[row] = (char*)malloc(size * sizeof(char));
        
        if (newBoard[row] == NULL) 
	{
            printf(" Memory allocation failed (columns)\n");
            exit(1);
        }

        // Initialize all cells to empty (space character)
        for (int col = 0; col < size; col++) 
	{
            newBoard[row][col] = ' ';
        }
    }

    return newBoard;
}

void freeBoard(char** board, int size) 
{
    // Free each row's memory
    for (int i = 0; i < size; i++) 
    {
        free(board[i]);
    }
    // Free the array of row pointers
    free(board);
}

void displayBoard(char** board, int size) 
{
    printf("\n");
    
    // Print column headers (0, 1, 2, ...)
    printf("    ");
    for (int col = 0; col < size; col++) 
    {
        printf(" %d  ", col);
    }
    printf("\n");

    // Print top border
    printf("    +");
    for (int col = 0; col < size; col++)
    {
        printf("---+");
    }
    printf("\n");

    // Print each row with row numbers and cell contents
    for (int row = 0; row < size; row++) 
    {
        printf(" %d  |", row);
        
        // Print cells in current row
        for (int col = 0; col < size; col++) 
	{
            printf(" %c |", board[row][col]);
        }
        printf("\n");

        // Print row separator
        printf("    +");
        for (int col = 0; col < size; col++) 
	{
            printf("---+");
        }
        printf("\n");
    }
    printf("\n");
}

bool isValidMove(char** board, int size, int row, int col) 
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

void getUserInput(char** board, int size, int *row, int *col) 
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
        if (isValidMove(board, size, *row, *col)) 
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

int getGameMode()
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

void makeComputerMove(char** board, int size, int *row, int *col)
{
    // Generate random moves until a valid one is found
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!isValidMove(board, size, *row, *col));
    
    printf("Computer chooses position (%d, %d)\n", *row, *col);
}

int main()
{
    // Game configuration variables
    int boardSize;
    int gameMode;
    char currentPlayer = 'X';
    int moveRow, moveCol;
    FILE *gameLogFile;

    // Initialize random number generator for computer moves
    srand(time(NULL));

    // Welcome message and game setup
    printf("TIC-TAC-TOE\n");
   
    // Get game mode
    gameMode = getGameMode();
    printf("\n");

    // Get board size from user with validation
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &boardSize);

    // Validate board size input
    if (boardSize < 3 || boardSize > 10) 
    {
        printf(" Invalid board size! Please choose between 3 and 10.\n");
        printf("Restart the program to try again.\n");
        return 1;
    }

    printf(" Creating a %dx%d game board...\n\n", boardSize, boardSize);

    // Initialize game components
    char** gameBoard = createBoard(boardSize);
    gameLogFile = fopen("tictactoe_log.txt", "w");

    // Check if log file opened successfully
    if (gameLogFile == NULL) 
    {
        printf(" Error: Could not create game log file!\n");
        freeBoard(gameBoard, boardSize);
        return 1;
    }

    // Log game start information
    fprintf(gameLogFile, "=== TIC-TAC-TOE GAME LOG ===\n");
    fprintf(gameLogFile, "Board Size: %dx%d\n", boardSize, boardSize);
    if (gameMode == 1) {
        fprintf(gameLogFile, "Mode: Two Players (X vs O)\n");
    } else {
        fprintf(gameLogFile, "Mode: User vs Computer (X vs O)\n");
    }
    fprintf(gameLogFile, "=============================\n\n");

    // Display initial empty board
    printf("Initial game board:\n");
    displayBoard(gameBoard, boardSize);

    printf("Player X goes first\n\n");
    
    while (true)
    {
        // Display current player's turn
        if (currentPlayer == 'X') 
        {
            // Always human player for X
            printf("Player %c's turn:\n", currentPlayer);
            printf("Enter row and column numbers (0-%d) separated by a space:\n", boardSize - 1);
            printf("> ");
            getUserInput(gameBoard, boardSize, &moveRow, &moveCol);
        } 
        else 
        {
            // Player O - depends on game mode
            if (gameMode == 1) 
            {
                // Two players mode - human player O
                printf("Player %c's turn:\n", currentPlayer);
                printf("Enter row and column numbers (0-%d) separated by a space:\n", boardSize - 1);
                printf("> ");
                getUserInput(gameBoard, boardSize, &moveRow, &moveCol);
            } 
            else 
            {
                // Computer mode - computer player O
                printf("Computer's turn (Player O):\n");
                makeComputerMove(gameBoard, boardSize, &moveRow, &moveCol);
            }
        }
        
        // Update game board with player's symbol
        gameBoard[moveRow][moveCol] = currentPlayer;

        // Display updated board
        printf("\nPlayer %c placed at position (%d, %d)\n", currentPlayer, moveRow, moveCol);
        displayBoard(gameBoard, boardSize);

        // Log the move to file using logMove function
        logMove(gameLogFile, gameBoard, boardSize, currentPlayer, moveRow, moveCol);

        // Check Game status
        // Check if current player has won
        if (checkWin(gameBoard, boardSize, currentPlayer)) 
	{
            if (gameMode == 2 && currentPlayer == 'O') 
            {
                printf("COMPUTER WINS!\n");
            } 
            else 
            {
                printf(" Player %c WINS! \n", currentPlayer);
            }
            fprintf(gameLogFile, " WINNER: Player %c\n", currentPlayer);
            fprintf(gameLogFile, "=== GAME OVER ===\n");
            break;
        }

        // Check if game is a draw (board full, no winner)
        if (checkDraw(gameBoard, boardSize)) 
	{
            printf(" DRAW: The board is full with no winner.\n");
            fprintf(gameLogFile, " RESULT: Draw game\n");
            fprintf(gameLogFile, "=== GAME OVER ===\n");
            break;
        }

        // Switch to other player for next turn
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        
        // Only show message when switching to human player
        if (currentPlayer == 'X' || (currentPlayer == 'O' && gameMode == 1)) 
        {
            printf("Switching turns... Next player: %c\n\n", currentPlayer);
        } 
        else 
        {
            printf("\n");
        }
    }

    // cleanup    
    printf("\n Game log saved to 'tictactoe_log.txt'\n");
    printf(" Thanks for playing!\n");

    // Close log file and free memory
    fclose(gameLogFile);
    freeBoard(gameBoard, boardSize);

    return 0;
}
