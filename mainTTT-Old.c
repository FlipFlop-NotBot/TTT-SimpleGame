/*
 * TESTED IN LINUX - 2020
*/

#include <stdio.h>
#include <stdlib.h>

int player = 1, choice;
int places[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void switchPlayers();
void displayBoard();
int markBoard(char mark);
int checkForWin();

int main() {


    while (!checkForWin()){
        system("clear");
        displayBoard();
        switchPlayers();
    }
    system("clear");
    displayBoard();
    checkForWin();

    return 0;
}


void switchPlayers(){
    if (player == 1) {
        printf("     Player 1 choose: ");
        scanf("%d", &choice);
        if (markBoard('X'))
            player = 1;
        else
            player = 2;

    }
    else if (player == 2){
        printf("     Player 2 choose: ");
        scanf("%d", &choice);
        if (markBoard('O'))
            player = 2;
        else
            player = 1;

    }
}

void displayBoard(){
    printf("\n             X & O           \n Player 1 (X) - Player 2 (O)\n\n");

    printf("\t    |   |   \n"
           "\t  %c | %c | %c \n"
           "\t ___|___|___\n"
           "\t    |   |   \n"
           "\t  %c | %c | %c \n"
           "\t ___|___|___\n"
           "\t    |   |   \n"
           "\t  %c | %c | %c \n"
           "\t    |   |   \n\n"
           ,  places[1], places[2],
           places[3], places[4], places[5],
           places[6], places[7], places[8], places[9]);
}

int markBoard(char mark){
    for (int i = 1; i < 10; ++i) {
        if (choice == i && places[i]-48 == i) {
            places[i] = mark;
            return 0;
        }
    }
    return 1;
}

int checkForWin() {
    short draw = 0;

    //Horizontal check
    for (int i = 1; i < 10; i += 3) {
        if (places[i] == places[i + 1] && places[i + 1] == places[i + 2]) {
            printf("\tYou won!\n");
            return 1;
        }
    }
    //Vertical check
    for (int i = 1; i < 4; i += 1) {
        if (places[i] == places[i + 3] && places[i + 3] == places[i + 6]) {
            printf("\tYou won!\n");
            return 1;
        }
    }
    //Diagonal check
    if (places[1] == places[5] && places[5] == places[9]) {
        printf("\tYou won!\n");
        return 1;
    } else if (places[3] == places[5] && places[5] == places[7]) {
        printf("\tYou won!\n");
        return 1;
    }
    //Check for draw
    for (int j = 1; j < 10; ++j) {
        if (places[j] - 48 != j)
            draw++;
    }
    if (draw == 9){
        printf("\t  Draw!\n");
        return 1;
    }

    return 0;
}
