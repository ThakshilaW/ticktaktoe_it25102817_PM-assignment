/**
 * TIC-TAC-TOE GAME FUNCTIONS - PART 1 (Two Players)
 * 
 * Modular functions for implementing Tic-Tac-Toe game logic
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * Creates and initializes the game board with empty spaces
 * 
 * param--> "size" The dimension of the board (size x size)
 * return--> Pointer to the dynamically allocated 2D character array
 * note: Memory must be freed using freeBoard() to prevent leaks
 */


//function declarations with parameters 
char** createBoard(int size);
void freeBoard(char** board, int size);
void displayBoard(char** board, int size);
bool isValidMove(char** board, int size, int row, int col);
void getUserInput(char** board, int size, int *row, int *col);
bool checkWin(char** board, int size, char playerSymbol);
bool checkDraw(char** board, int size);
void logMove(FILE *logFile, char** board, int size, char player, int row, int col);



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

/**
 * freeBoard function frees all dynamically allocated memory used by the game board
 * note: Critical function to prevent memory leaks - must be called before program exit
 */
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

/**
 * Displays the current state of the game board in a user-friendly format 
 * Shows column headers, row numbers, and uses a grid-like format
 */
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
        printf("---+");// adding a + sign here gives clear image of cells in the board
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


/**
 * isValidMove function validates whether a proposed move is legal.
 * return true if move is valid (within bounds and empty cell), false otherwise
 */
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

/**
 * Gets and validates player input for their next move
 * row is a Pointer to store the validated row input
 * col is a Pointer to store the validated column input
 * 
 * Uses infinite loop that only breaks when valid input is received
 * Handles various error cases with specific error messages
 */
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

/**
 * checkWin function checks if the specified player has achieved a winning condition.
 * param--> playerSymbol, The player's symbol ('X' or 'O') to check for
 * return--> true, if player has N identical symbols in a row, column, or diagonal
 * 
 * Checks all possible winning conditions:
 * - Horizontal rows
 * - Vertical columns  
 * - Main diagonal (top-left to bottom-right)
 * - secondary diagonal (top-right to bottom-left)
 */
bool checkWin(char** board, int size, char playerSymbol) 
{
    bool foundWin;//this is a function created within a function so ig no need to declare initially

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

/**
 * checkDraw function checks if the game has ended in a draw (tie)
 * return--> true, if board is full with no winner, false otherwise
 * 
 * A draw happens when all cells are filled but no player has achieved N in a row
 */
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

// this function creates a log for later access or analysis of games.
// fogfile is a pointer to the open log file.

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

int main()
{
    // Game configuration variables
    int boardSize;              // N x N board size (3-10)
    char currentPlayer = 'X';   // Start with player X
    int moveRow, moveCol;       // Store player's move coordinates
    FILE *gameLogFile;          // File pointer for game logging

    // Welcome message and game setup

    printf("TIC-TAC-TOE\n");
   

    // Get board size from user with validation
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &boardSize);

    // Validate board size input
    if (boardSize < 3 || boardSize > 10) 
    {
        printf(" Invalid board size! Please choose between 3 and 10.\n");
        printf("Restart the program to try again.\n");
        return 1; // Exit program with error code
    }

    printf(" Creating a %dx%d game board...\n\n", boardSize, boardSize);

    // Initialize game components
    char** gameBoard = createBoard(boardSize);  // Create empty board
    gameLogFile = fopen("tictactoe_log.txt", "w");  // Open log file for writing

    // Check if log file opened successfully
    if (gameLogFile == NULL) 
    {
        printf(" Error: Could not create game log file!\n");
        freeBoard(gameBoard, boardSize);  // Clean up memory before exiting
        return 1;
    }

    // Log game start information
    fprintf(gameLogFile, "=== TIC-TAC-TOE GAME LOG ===\n");
    fprintf(gameLogFile, "Board Size: %dx%d\n", boardSize, boardSize);
    fprintf(gameLogFile, "Players: X vs O\n");
    fprintf(gameLogFile, "=============================\n\n");

    // Display initial empty board
    printf("Initial game board:\n");
    displayBoard(gameBoard, boardSize);



    printf("Player X goes first\n\n");
    
    while (true)
    {
        // Display current player's turn
        printf("Player %c's turn:\n", currentPlayer);
        printf("Enter row and column numbers (0-%d) separated by a space:\n", boardSize - 1);
        printf("> ");

        // Get and process player's move
        getUserInput(gameBoard, boardSize, &moveRow, &moveCol);
        
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
            printf(" Player %c WINS! \n", currentPlayer);
            fprintf(gameLogFile, " WINNER: Player %c\n", currentPlayer);
            fprintf(gameLogFile, "=== GAME OVER ===\n");
            break;  // Exit game loop
        }

        // Check if game is a draw (board full, no winner)
        if (checkDraw(gameBoard, boardSize)) 
	{
            printf(" DRAW: The board is full with no winner.\n");
            fprintf(gameLogFile, " RESULT: Draw game\n");
            fprintf(gameLogFile, "=== GAME OVER ===\n");
            break;  // Exit game loop
        }

        // Switch to other player for next turn
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        printf("Switching turns... Next player: %c\n\n", currentPlayer);
    }

    // cleanup    
    printf("\n Game log saved to 'tictactoe_log.txt'\n");
    printf(" Thanks for playing!\n");

    // Close log file and free memory
    fclose(gameLogFile);
    freeBoard(gameBoard, boardSize);

    return 0; // Successful program execution
}

