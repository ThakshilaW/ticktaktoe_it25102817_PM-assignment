/**
 * TIC-TAC-TOE GAME
 * With the use of header files in the revised version
 * Part 1: Two Players | Part 2: Player vs Computer
 */

#include <tttgamefunctions.h>
#include <tttgamelogicninputfunc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


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
    gameMode = gameMode();
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
    char** gameBoard = Board(boardSize);
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
            userInput(gameBoard, boardSize, &moveRow, &moveCol);
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
                userInput(gameBoard, boardSize, &moveRow, &moveCol);
            } 
            else 
            {
                // Computer mode - computer player O
                printf("Computer's turn (Player O):\n");
                computerMove(gameBoard, boardSize, &moveRow, &moveCol);
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
