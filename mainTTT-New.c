/*
 *
 * TESTED IN LINUX - 2020
 * 
 * This is my version of Tic Tac Toe, with an expandable board.
 *
 * TO DO: MAKE THE CODE LOOK NICE!!!
 *
*/


// Including needed stuff
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// Creating the board struct
struct TTT_BoardGame {
    unsigned short playerTurn;
    int boardSqrt;
    double boardLen;
    bool canFinish;
    char ***board;
};

// Ask the player for the size of the board they want
int askForBoardSize(void) {
	system("clear");
	int size;
	printf("Tic tac toe game.\n\nWhat size do you want the board to be? Enter a number to create a new board with the desired size: ");
	scanf("%d", &size);
	return size;
}

// Initializing the board struct
struct TTT_BoardGame ttt_init(void) {
    struct TTT_BoardGame game = {};
    game.playerTurn = 0;
    game.canFinish = false;

	int bSize = askForBoardSize();

	// Initialize the board at the correct size
	game.boardSqrt = bSize;
	game.boardLen = game.boardSqrt * game.boardSqrt;

	game.board = (char***)malloc(bSize * sizeof(char**));

	for (int i = 0; i < bSize; i++) {
		game.board[i] = (char**) malloc(bSize * sizeof(char*));

		for (int j = 0; j < bSize; j++) {
			game.board[i][j] = (char*) malloc(3 * sizeof(char));
		}
	}
    
    // Set the starting value in each board cell
    char pos[3] = {'0', '0', '1'};
    for (unsigned short v = 0; v < game.boardSqrt; v++) {
        for (unsigned short h = 0; h < game.boardSqrt; h++) {

			for (short p = 2; p >= 0; p--) {
				game.board[v][h][p] = pos[p];
			}
			if (pos[2] < '9')

	    for (short p = 2; p >= 0; p--) {
	        game.board[v][h][p] = pos[p];
	    }
	    if (pos[2] < '9')

            	pos[2]++;
            else {
            	pos[2] = '0';
            	pos[1]++;
            }

            if (pos[1] > '9') {
            	pos[1] = '0';
            	pos[0]++;
            }
        }
    }
    return game;
}

// The menu that displays when starting the game
void ttt_startMenu(void) {
	char key;
	system("clear");
	printf("Tic tac toe game.\n\nTip: When prompted, each player needs to choose a spot to place their symbol.\nPress the 'Enter' key to continue... ");
	scanf("%c", &key);
}

// Returns the symbol of the current player
char ttt_currentPlayerTurn(struct TTT_BoardGame *game) {
    return game->playerTurn % 2 ? 'O' : 'X';
}

// Returns the symbol of the player before the one now
char ttt_lastPlayerTurn(struct TTT_BoardGame *game) {
    return game->playerTurn % 2 ? 'X' : 'O';
}

// Asks the current player for a position
char *ttt_askForPosition(struct TTT_BoardGame *game) {
    static char pos[3];

    printf("Choose a position for '%c': ", ttt_currentPlayerTurn(game));
    scanf("%s", pos);
	
    return pos;
}

// Checks if the spot chosen by the player is empty
bool ttt_isLegalMove(struct TTT_BoardGame *game, unsigned short col, unsigned short row) {
    if ((row + 1) <= game->boardSqrt && (col +1) <= game->boardSqrt) {
        if (game->board[col][row][1] != 'X' && game->board[col][row][1] != 'O')
            return true;
    }
    return false;
}

// Edit the board cell to display the symbol of the current player
void ttt_markAnswer(struct TTT_BoardGame *game) {
    char *ans = ttt_askForPosition(game);

    for (unsigned short col = 0; col < game->boardSqrt; col++){
        for (unsigned short row = 0; row < game->boardSqrt; row++) {
	    if (strncmp(ans, game->board[col][row], 3) == 0) {
    	   	if (ttt_isLegalMove(game, col, row)) {
            	    game->board[col][row][0] = ' ';
            	    game->board[col][row][2] = ' ';
                    game->board[col][row][1] = ttt_currentPlayerTurn(game);
                    game->playerTurn++;
		    break;
             	}	
               	else {
     	            ttt_markAnswer(game);
               	}
            }
        }
    }
}

// Prints one row of board cells
void ttt_displayBoardSegment(struct TTT_BoardGame *game, unsigned short vPos) {
    for (unsigned short v = 0; v < 3; v++) {
        if (v % 2 == 0) {
            for (unsigned short h = 0; h < game->boardSqrt; h++)
                printf("|=====|");
        } else {
            for (unsigned short h = 0; h < game->boardSqrt; h++)
                printf("| %c%c%c |", game->board[vPos][h][0], game->board[vPos][h][1], game->board[vPos][h][2]);
        }
        printf("\n");
    }
}

// Prints as many board cell rows as needed
void ttt_displayBoardTotal(struct TTT_BoardGame *game) {
    system("clear");
    printf("Tic Tac Toe %dx%d\n\n", game->boardSqrt, game->boardSqrt);
    for (unsigned short i = 0; i < game->boardSqrt; i++)
        ttt_displayBoardSegment(game, i);
}

// Checks if the game ended in a draw
bool ttt_testForDraw(struct TTT_BoardGame *game) {
    return game->playerTurn >= game->boardLen;
}

// Checks for rows with each cell full of one symbol
bool ttt_isHorizontalWin(struct TTT_BoardGame *game) {
    for (unsigned short v = 0; v < game->boardSqrt; v++) {
        char elem = game->board[v][0][1];
        for (unsigned short h = 0; h < game->boardSqrt; h++) {
            if (elem != game->board[v][h][1])
                break;
            if (h == game->boardSqrt - 1) {
                if (elem == 'X' || elem == 'O')
        	    return true;
            }
        }
    }
    return false;
}

// Checks for columns with each cell full of one symbol
bool ttt_isVerticalWin(struct TTT_BoardGame *game) {
    for (unsigned short h = 0; h < game->boardSqrt; h++) {
        char elem = game->board[0][h][1];
        for (unsigned short v = 0; v < game->boardSqrt; v++) {
            if (elem != game->board[v][h][1])
                break;
            if (v == game->boardSqrt - 1) {
            	if (elem == 'X' || elem == 'O')
        	    return true;
            }
        }
    }
    return false;
}

// Checks one diagonal (top left -> bottom right) with each cell full of one symbol 
bool ttt_isDiagonalWinLeftToRight(struct TTT_BoardGame *game) {
    char elem = game->board[0][0][1];

    for (unsigned short v = 0, h = 0; v < game->boardSqrt; v++, h++) {
        if (elem != game->board[v][h][1])
            break;
        if (h == game->boardSqrt - 1) {
            if (elem == 'X' || elem == 'O')
                return true;
        }
    }
    return false;
}

// Checks other diagonal (top right -> bottom left) with each cell full of one symbol
bool ttt_isDiagonalWinRightToLeft(struct TTT_BoardGame *game) {
    unsigned short lastPosRow = game->boardSqrt - 1;
    char elem = game->board[0][lastPosRow][1];

    for (unsigned short v = 0, h = game->boardSqrt - 1; v < game->boardSqrt; v++, h--) {

        if (elem != game->board[v][h][1])
            break;
        if (h == 0) {
            if (elem == 'X' || elem == 'O')
                return true;
        } 
    }
    return false;
}

// All of the 'win' possibilities combined
bool ttt_testForWin(struct TTT_BoardGame *game) {
    if (ttt_isVerticalWin(game) || ttt_isHorizontalWin(game) || ttt_isDiagonalWinLeftToRight(game) || ttt_isDiagonalWinRightToLeft(game))
        return true;
}

// Checks if somebody won or the game ended in a draw
bool ttt_finishGame(struct TTT_BoardGame *game) {
	if (ttt_testForWin(game) && game->canFinish) {
	    printf("\n'%c' won!\n", ttt_lastPlayerTurn(game));
	    return true;
	}
	else if (ttt_testForDraw(game) && game->canFinish) {
	    printf("\nDraw!\n");
            return true;
	}
	else if (ttt_testForWin(game) || ttt_testForDraw(game)) {
	    game->canFinish = true;
	}
	return false;
}


// 'main' function
int main() {
    ttt_startMenu();
	
    for (struct TTT_BoardGame game = ttt_init();;) {
        ttt_displayBoardTotal(&game);

        if (!game.canFinish)
            ttt_markAnswer(&game);

		if (ttt_finishGame(&game)) {
			// Free up memory space
			for (int v = 0; v < game.boardSqrt; v++) {
				for (int h = 0; h < game.boardSqrt; h++)
					free(game.board[v][h]);
			}
			free(game.board);
			
			break;
		}
	    	
    }

    return 0;
}
