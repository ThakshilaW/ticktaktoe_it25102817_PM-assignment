/**
 * TIC-TAC-TOE GAME
 * Final version with part 3 : fixdddd
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
    int currentPlayer = 0; // 0=X, 1=O
    char playerSymbols[2] = {'X', 'O'}; // Only 2 symbols for modes 1 & 2
    int moveRow, moveCol;
    FILE *gameLogFile;
    int totalPlayers = 2; // Default to 2 players for modes 1 & 2

    // Initialize random number generator for computer moves
    srand(time(NULL));

    // Welcome message and game setup
    printf("TIC-TAC-TOE\n");
   
    // Get game mode
    selectedMode = gameMode();
    printf("\n");

    // Handle three-player modes
    if (selectedMode >= 31 && selectedMode <= 33) 
    {
        totalPlayers = 3;
        // Expand symbols array for three players
        char threeSymbols[3] = {'X', 'O', 'Z'};
        // We'll use threeSymbols when needed
        playerSymbols[0] = 'X';
        playerSymbols[1] = 'O'; 
        playerSymbols[2] = 'Z';
    }

    // Get board size from user with validation
    printf("Enter board size-->(between 3 and 10 including them): ");
    scanf("%d", &boardSize);

    // Validate board size input
    if (boardSize < 3 || boardSize > 10) 
    {
        printf(" Invalid board size, choose between 3 and 10.\n");
        printf("Restart the program to try again.\n");
        return 1;
    }

    printf(" Creating a %dx%d game board...\n\n", boardSize, boardSize);

    // Initialize game
    char** gameBoard = Board(boardSize);
    gameLogFile = fopen("tictactoe_record.txt", "w");

    // Check if log file opened 
    if (gameLogFile == NULL) 
    {
        printf(" Error: Could not create game record!\n");
        freeBoard(gameBoard, boardSize);
        return 1;
    }

    // record start information
    fprintf(gameLogFile, "=== TIC-TAC-TOE GAME RECORD ===\n");
    fprintf(gameLogFile, "Board Size: %dx%d\n", boardSize, boardSize);
    
    // Handle all mode types correctly
    if (selectedMode == 1) 
    { 
        fprintf(gameLogFile, "Mode: Two Players (X vs O)\n");
        printf("Mode: Two Players (X vs O)\n");
    }
    else if (selectedMode == 2)
    {
        fprintf(gameLogFile, "Mode: Player vs Computer\n");
        printf("Mode: Player vs Computer\n");
    }
    else if (selectedMode == 31)
    {
        fprintf(gameLogFile, "Mode: Three Players\n");
        printf("Mode: Three Players\n");
    }
    else if (selectedMode == 32)
    {
        fprintf(gameLogFile, "Mode: Two players + One Computer\n");
        printf("Mode: Two players + One Computer\n");
    }
    else if (selectedMode == 33)
    {
        fprintf(gameLogFile, "Mode: One player + Two Computers\n");
        printf("Mode: One player + Two Computers\n");
    }
    
    fprintf(gameLogFile, "=============================\n\n");

    // Display empty board
    printf("Game starts:\n");
    displayBoard(gameBoard, boardSize);

    printf("Player X goes first\n\n");
    
    while (true)
    {
        char currentSymbol;
        
        // Get current symbol based on number of players
        if (totalPlayers == 3) 
        {
            currentSymbol = (currentPlayer == 0) ? 'X' : (currentPlayer == 1) ? 'O' : 'Z';
        }
        else 
        {
            currentSymbol = (currentPlayer == 0) ? 'X' : 'O';
        }
        
        // Display current player's turn
        if (playerType(currentPlayer, selectedMode) == 1) 
        {
            // player
            printf("Player %c's turn:\n", currentSymbol);
            printf("Enter row and column numbers (0-%d) separated by a space:\n", boardSize - 1);
            printf("> ");
            userInput(gameBoard, boardSize, &moveRow, &moveCol, currentPlayer);
        } 
        else 
        {
            // Computer
            printf("Computer's turn (Player %c):\n", currentSymbol);
            computerMove(gameBoard, boardSize, &moveRow, &moveCol);
        }
        
        // Update game board with player's symbol
        gameBoard[moveRow][moveCol] = currentSymbol;

        // Display updated board
        printf("\nPlayer %c placed at position (%d, %d)\n", currentSymbol, moveRow, moveCol);
        displayBoard(gameBoard, boardSize);

        // record the move to the file using logMove function
        logMove(gameLogFile, gameBoard, boardSize, currentSymbol, moveRow, moveCol);

        // Check Game status
        // Check if current player has won
        if (checkWin(gameBoard, boardSize, currentSymbol)) 
        {
            if (playerType(currentPlayer, selectedMode) == 0) 
            {
                printf("COMPUTER WINS (Player %c)\n", currentSymbol);
            } 
            else 
            {
                printf(" Player %c WINS \n", currentSymbol);
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

        // Switch to next player (handle 2 or 3 players)
        if (totalPlayers == 3) 
        {
            currentPlayer = (currentPlayer + 1) % 3;
        }
        else 
        {
            currentPlayer = (currentPlayer + 1) % 2;
        }
        
        printf("Switching turns... Next player: %c\n\n", 
               (totalPlayers == 3) ? 
               ((currentPlayer == 0) ? 'X' : (currentPlayer == 1) ? 'O' : 'Z') :
               ((currentPlayer == 0) ? 'X' : 'O'));
    }

    // cleanup    
    printf("\n Game log saved to 'tictactoe_record.txt'\n");
    printf(" Exiting..\n");

    // Close log file and free memory
    fclose(gameLogFile);
    freeBoard(gameBoard, boardSize);

    return 0;
}
