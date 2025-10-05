#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//function declarations
char** Board(int size); //changed function name than earlier commits because why not
void freeBoard(char** board, int size);
void displayBoard(char** board, int size);




char** Board(int size)
{
	// Allocate memory for array of row pointers
	char** newBoard = (char**)malloc(size * sizeof(char));
	if (newBoard == NULL)
	{
		printf("Memory allocation failed (row)\n");
		exit(1);
	}
//Allocate memory for each row and initialize with empty spaces
for (int row = 0; row < size; row++)
{
	newBoard[row] = (char*)malloc(size * sizeof(char));
	if (newBoard[row] == NULL)
	{
		printf("Memory allocation failed (columns)\n");
		exit(1);
	}
//initialize all cells as empty
	for (int col = 0; col < size; col++)
	{
		newBoard[row][col] = ' ';
	}
}
return newBoard;
}

void freeBoard(char** board, int size)
{
	//Free row memory
	for (int i=0; i<size; i++)
	{
		free(board[i]);
	}
	//free array of row pointers
	free(board);
}


void displayBoard(char** board, int size)
{
	printf("\n");

	//column headers
	printf("   ");
	for (int col = 0; col<size; col++)
	{
		printf(" %d ",col);
	}
	printf("\n");


	//top border
	printf("   +");
	for (int col = 0; col<size; col++)
	{
		printf("---+");
	}
	printf("\n");

	//rows with numbers and cell contents
	
	for (int row = 0; row<size; row++)
	{
		printf(" %d |",row);

		for (int col = 0; col<size; col++)
		{
		printf(" %c |", board[row][col]);
		}
	
		printf("\n");

		// row seperator
	
		printf("   +");
		for (int col = 0; col<size; col++)
		{
		printf("---+");
		}
		printf("\n");
		}
	printf("\n");
}
