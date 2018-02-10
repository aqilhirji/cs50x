/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // function 1/4 - create the board contents 
    int s = d * d; // assign s as sum of number of pieces on board
    int t = d * d; // assign t as the same as s, but not decrementing
    for (int i = 0; i < d ; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = --s; // auto sets bottom right to 0 (convert to blank in draw)
        }
    }
    // check for odd tiles and switch 1 and 2 if needed  (use modulo to check)
    if (t % 2 == 0)
    {
        board[d - 1][d - 2] = 2; // swap to static value 2
        board[d - 1][d - 3] = 1; // swap to static value 1
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
// print the board variables in the correct order 
    for (int i = 0; i < d; i++) // increment rows
    {
        for (int j = 0; j < d; j++) // increment columns 
        {
            if (board[i][j] == 0)
            {
                printf("  _"); // sub blank space for the 0 value (note 3 chars equal to number of spaces below)
            }
            else {
                printf("%3i", board[i][j]); // print spaces and then value 
                }
        }
        printf("\n"); // print new line after row
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{ // moves any tile that borders an empty spcae
    for (int i = 0; i < d; i++)
        { // looks for tile value iteratively (rows)
            for (int j = 0; j < d; j++)
                { // looks for tile value iteratively (columns)
                    if (board[i][j] == tile) // find spot equal to tile 
                    {
                        if (i + 1 <= (d - 1) && board[i + 1][j] == 0) // if spot to right is not end and spot to right = 0
                        {
                            board[i + 1][j] = tile; // move value to right 
                            board[i][j] = 0; //change current spot to 0
                            return true; 

                        }
                        else if (i - 1 >= 0 && board[i - 1][j] == 0) // if spot to left is not end and spot to left = 0
                        {
                            board[i - 1][j] = tile; // move value left
                            board[i][j] = 0; //change current spot to 0
                            return true; 
                        }
                        else if (j + 1 <= d - 1 && board[i][j + 1] == 0) // if spot below is not end and spot below = 0
                        {
                            board[i][j + 1] = tile; // move value down
                            board[i][j] = 0; //change current spot to 0
                            return true; 
                        }
                        else if (j - 1 >= 0 && board[i][j - 1] == 0) // if spot above is not end and spot above = 0 
                        {
                            board[i][j - 1] = tile; // move value up
                            board[i][j] = 0; // change current spot to 0 
                            return true; 
                        }

                    }
                }
        }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{ // checks if the current board config is a winner
    // go spot by spot and check if they're in order 
    int a = 0; // counter for each tile 
    int s = d * d; // total number of spots
    for (int i = 0; i < d; i++) // increment rows
        { 
            for (int j = 0; j < d; j++) // increment columns 
                { 
                    if (++a != s && board[i][j] != a) // check if order is correct
                    {
                        return false; 
                    }
                }
        }
    return true; // if made it through entire loop without break to false, then return true 
}
