/*
 * TESTED IN LINUX - 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct TTT_BoardGame {
    unsigned short playerTurn;
    double boardLen;
    char board[3][3];
};

struct TTT_BoardGame ttt_init(void) {
    struct TTT_BoardGame game = {};
    game.playerTurn = 0;
    game.boardLen = sizeof(game.board);
    char pos = '1';
    for (unsigned short v = 0; v < sqrt(game.boardLen); v++) {
        for (unsigned short h = 0; h < sqrt(game.boardLen); h++){
            game.board[v][h] = pos;
            pos++;
        }
    }
    return game;
}

char ttt_currentPlayerTurn(struct TTT_BoardGame *game) {
    return game->playerTurn % 2 ? 'O' : 'X';
}

char ttt_lastPlayerTurn(struct TTT_BoardGame *game) {
    return game->playerTurn % 2 ? 'X' : 'O';
}

int ttt_askForPosition(struct TTT_BoardGame *game) {
    int pos;

    printf("Choose a position for '%c': ", ttt_currentPlayerTurn(game));
    scanf("%d", &pos);

    return pos;
}

bool ttt_isLegalMove(struct TTT_BoardGame *game, unsigned short col, unsigned short row) {
    if ((row + 1) <= sqrt(game->boardLen) && (col +1) <= sqrt(game->boardLen)) {
        if (game->board[col][row] != 'X' && game->board[col][row] != 'O')
            return true;
    }
    return false;
}

void ttt_markAnswer(struct TTT_BoardGame *game) {
    int ans = ttt_askForPosition(game);

    for (unsigned short col = 0; col < sqrt(game->boardLen); col++){
        for (unsigned short row = 0; row < sqrt(game->boardLen); row++) {
            if (ans + '0' == game->board[col][row]) {
                if (ttt_isLegalMove(game, col, row)) {
                    game->board[col][row] = ttt_currentPlayerTurn(game);
                    game->playerTurn++;
                }
                else {
                    ttt_markAnswer(game);
                }
                break;
            }
        }
    }
}

void ttt_displayBoardSegment(struct TTT_BoardGame *game, unsigned short vPos) {
    for (unsigned short v = 0; v < 3; v++) {
        if (v % 2 == 0) {
            for (unsigned short h = 0; h < sqrt(game->boardLen); h++)
                printf("|===|");
        } else {
            for (unsigned short h = 0; h < sqrt(game->boardLen); h++)
                printf("| %c |", game->board[vPos][h]);
        }
        printf("\n");
    }
}

void ttt_displayBoardTotal(struct TTT_BoardGame *game) {
    system("clear");
    for (unsigned short i = 0; i < sqrt(game->boardLen); i++)
        ttt_displayBoardSegment(game, i);
}

bool ttt_testForDraw(struct TTT_BoardGame *game) {
    return game->playerTurn >= game->boardLen;
}

bool ttt_isHorizontalWin(struct TTT_BoardGame *game) {
    for (unsigned short v = 0; v < sqrt(game->boardLen); v++) {
        char elem = game->board[v][0];
        for (unsigned short h = 0; h < sqrt(game->boardLen); h++) {
            if (elem != game->board[v][h])
                break;
            if (h == sqrt(game->boardLen) - 1)
                return true;
        }
    }
    return false;
}

bool ttt_isVerticalWin(struct TTT_BoardGame *game) {
    for (unsigned short h = 0; h < sqrt(game->boardLen); h++) {
        char elem = game->board[0][h];
        for (unsigned short v = 0; v < sqrt(game->boardLen); v++) {
            if (elem != game->board[v][h])
                break;
            if (v == sqrt(game->boardLen) - 1)
                return true;
        }
    }
    return false;
}

bool ttt_isDiagonalWinLeftToRight(struct TTT_BoardGame *game) {
    char elem = game->board[0][0];

    for (unsigned short v = 0, h = 0; v < sqrt(game->boardLen); v++, h++) {
        if (elem != game->board[v][h])
            break;
        if (h == sqrt(game->boardLen) - 1)
            return true;
    }
    return false;
}

bool ttt_isDiagonalWinRightToLeft(struct TTT_BoardGame *game) {
    unsigned short lastPosRow = sqrt(game->boardLen) - 1;
    char elem = game->board[0][lastPosRow];

    for (unsigned short v = 0, h = sqrt(game->boardLen) - 1; v < sqrt(game->boardLen); v++, h--) {

        if (elem != game->board[v][h])
            break;
        if (h == 0)
            return true;
    }
    return false;
}

bool ttt_testForWin(struct TTT_BoardGame *game) {
    if (ttt_isVerticalWin(game) || ttt_isHorizontalWin(game) || ttt_isDiagonalWinLeftToRight(game) || ttt_isDiagonalWinRightToLeft(game))
        return true;
}


int main() {
    bool canFinish = false;
    for (struct TTT_BoardGame game = ttt_init();;) {
        ttt_displayBoardTotal(&game);

        if (!canFinish)
            ttt_markAnswer(&game);


        if (ttt_testForWin(&game) && canFinish) {
            printf("\n'%c' won!\n", ttt_lastPlayerTurn(&game));
            break;
        }
        else if (ttt_testForDraw(&game) && canFinish) {
            printf("\nDraw!\n");
            break;
        }
        else if (ttt_testForWin(&game) || ttt_testForDraw(&game)) {
            canFinish = true;
        }


    }

    return 0;
}
