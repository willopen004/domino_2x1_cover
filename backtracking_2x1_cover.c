#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// makes the board for the first time////////////////////////////////////////////////
char board_maker (int N, char board [N][N])
{
    for (int row = 0; row<N; row++)
    {
        for (int column = 0; column<N; column++)
        {
            board [row][column] = '_';
        }
    }
    return **board;
}

// prints the current board//////////////////////////////////////////////////////
void board_printer (int N, char board [N][N])
{
    for (int row = 0; row<N; row++)
    {
        for (int column = 0; column<N; column++)
        {
            printf ("%c", board [row][column]);
        }
        printf ("\n");
    }
    printf ("\n\n");
}

// builds the board////////////////////////////////////////////////////////////
char board_builder (int N, char board [N][N])
{
    int row = 0;
    int column = 0;
    printf ("now its time to set your board!\nplease type a row and column to mark them with #\n");
    printf ("when your done just type in 0\n");

    do
    {
        printf ("row: \n");
        scanf ("%d", &row);

        if (row == 0)
        {
            printf ("your final board is: \n");
            board_printer (N, board);
            return **board;
        }

        printf ("column: \n");
        scanf ("%d", &column);

        if (column == 0)
        {
            printf ("your final board is: \n");
            board_printer (N, board);
            return **board;
        }

        if (board [row-1][column-1] != '_')
        {
            printf ("you already marked that spot! pick another!\n");
            continue;
        }

        board [row-1][column-1] = '#';

        board_printer (N, board);
    }
    while (row != 0 || column != 0);

    return **board;
}
//checking if the solution is legal //////////////////////////////////////////////////////////////////////////
bool is_board_solved (int N, char board [N][N])
{
    int counter = 0;
    
    for (int row = 0; row<N; row++)
    {
        for (int column = 0; column<N; column++)
        {
            if (board [row][column] != '_')
            {
                counter++;
            }
        }
    }
    
    if (counter == N*N)
    {
        return true;
    }

    return false;
}
//solving the board //////////////////////////////////////////////////////////////////
bool board_solver (int N, char board [N][N], int row, int column, char letter)
{
    if (row*column == N*N)
    {
        if (is_board_solved (N, board))
        {
            board_printer (N, board);

            return true;
        }
        else
        {
            return false;
        }
    }

    if (column == N)
    {
        row++;
        column = 0;
    }

    if (board [row][column] == '_')
    {
        // side check:
        if (board [row][column+1] == '_' && column+1 < N)
        {
            #ifdef HELP
            printf("\nside: \nrow: %d column: %d\n", row ,column);
            #endif
            board [row][column] = letter;
            board [row][column+1] = letter;
            #ifdef HELP
            board_printer (N, board);
            printf ("\n\n");
            #endif
            if (board_solver (N, board, row, column+1, letter+1))
            {
                return true;
            }

            board [row][column] = '_';
            board [row][column+1] = '_';

        }

        // down check:

        if (board [row+1][column] == '_' && row+1 < N)
        {
            #ifdef HELP
            printf("\ndown: \nrow: %d column: %d\n", row ,column);
            #endif
            board [row][column] = letter;
            board [row+1][column] = letter;
            #ifdef HELP
            board_printer (N, board);
            printf ("\n\n");
            #endif
            if (board_solver (N, board, row, column+1, letter+1))
            {
                return true;
            }
            board [row][column] = '_';
            board [row+1][column] = '_';
        }
    }


    return board_solver (N, board, row, column+1, letter);;

}


int main()
{
int N = 0;
int row = 0;
int column = 0;
char letter = 'A';
printf ("backtracking\n");
printf ("--------------------------\n");

printf ("please enter a board size: ");
scanf ("%d", &N);

char board [N][N];

board_maker (N, board);
board_printer (N, board);
board_builder (N, board);
if (!board_solver (N, board, row, column, letter))
{
    printf ("broken board");
}

    return 0;
}
