/**
 * TIC-TAC-TOE GAME
 * With the use of header files in the revised version
 * Part 1: Two Players | Part 2: Player vs Computer | Part 3: Three Players
 */

#include "tttgamefunctions.h"        
#include "tttgamelogicninputfunc.h"  
#include "tttgamerecords.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main()
{
    // Game variables
    int boardSize;
    int selectedMode;
    int currentPlayer = 0; // 0=X, 1=O, 2=Z
    char playerSymbols[3] = {'X', 'O', 'Z'};
    int moveRow, moveCol;
    FILE *gameLogFile;

    // Initialize random number generator for computer moves
    srand(time(NULL));

    // Welcome message and game setup
    printf("TIC-TAC-TOE\n");
   
    // Get game mode
    selectedMode = gameMode();
    printf("\n");

    // Get board size from user with validation
    printf("Enter board size--> N (3 <= N <= 10): ");
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
    gameLogFile = fopen("tictactoe_record.txt", "w");

    // Check if log file opened successfully
    if (gameLogFile == NULL) 
    {
        printf(" Error: Could not create game record!\n");
        freeBoard(gameBoard, boardSize);
        return 1;
    }

    // Log game start information
    fprintf(gameLogFile, "=== TIC-TAC-TOE GAME RECORD ===\n");
    fprintf(gameLogFile, "Board Size: %dx%d\n", boardSize, boardSize);
    if (selectedMode == 1) 
    { 
        fprintf(gameLogFile, "Mode: Three Human Players (X, O, Z)\n");
    }
    else if (selectedMode == 2)
    {
        fprintf(gameLogFile, "Mode: Two Humans + One Computer\n");
    }
    else 
    {
        fprintf(gameLogFile, "Mode: One Human + Two Computers\n");
    }
    fprintf(gameLogFile, "=============================\n\n");

    // Display initial empty board
    printf("Initial game board:\n");
    displayBoard(gameBoard, boardSize);

    printf("Player X goes first\n\n");
    
    while (true)
    {
        char currentSymbol = playerSymbols[currentPlayer];
        
        // Display current player's turn
        if (playerType(currentPlayer, selectedMode) == 1) 
        {
            // Human player
            printf("Player %c's turn:\n", currentSymbol);
            printf("Enter row and column numbers (0-%d) separated by a space:\n", boardSize - 1);
            printf("> ");
            userInput(gameBoard, boardSize, &moveRow, &moveCol, currentPlayer); // FIXED: added currentPlayer
        } 
        else 
        {
            // Computer player
            printf("Computer's turn (Player %c):\n", currentSymbol);
            computerMove(gameBoard, boardSize, &moveRow, &moveCol); // FIXED: removed extra parameter
        }
        
        // Update game board with player's symbol
        gameBoard[moveRow][moveCol] = currentSymbol;

        // Display updated board
        printf("\nPlayer %c placed at position (%d, %d)\n", currentSymbol, moveRow, moveCol);
        displayBoard(gameBoard, boardSize);

        // Log the move to file using logMove function
        logMove(gameLogFile, gameBoard, boardSize, currentSymbol, moveRow, moveCol);

        // Check Game status
        // Check if current player has won
        if (checkWin(gameBoard, boardSize, currentSymbol)) 
        {
            if (playerType(currentPlayer, selectedMode) == 0) 
            {
                printf("COMPUTER WINS! (Player %c)\n", currentSymbol);
            } 
            else 
            {
                printf(" Player %c WINS! \n", currentSymbol);
            }
            fprintf(gameLogFile, " WINNER: Player %c\n", currentSymbol);
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

        // Switch to next player (0→1→2→0)
        currentPlayer = (currentPlayer + 1) % 3;
        printf("Switching turns... Next player: %c\n\n", playerSymbols[currentPlayer]);
    }

    // cleanup    
    printf("\n Game log saved to 'tictactoe_record.txt'\n");
    printf(" Thanks for playing!\n");

    // Close log file and free memory
    fclose(gameLogFile);
    freeBoard(gameBoard, boardSize);

    return 0;
}
