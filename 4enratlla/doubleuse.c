//
//  doubleuse.c
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 29/11/22.
//

#include "doubleuse.h"

char header[] = "  A   B   C   D   E   F   G   H ";
char horbar[] = "|---|---|---|---|---|---|---|---|";

bool checkFull(char board[N][N], int play){
    
    int count = 0;
    
    for (int i = N-1; i >= 0; i--){
        //We check if the item is empty in ascending order, if so, put the token there
        if (board[i][play] != ' '){
            count++;
        }
    }
    if (count == 8){//Full col
        return true;
    }
    return false;
}

bool checkWin(char player, char board[N][N]){
    
    //We'll have to check for both diagonals, column and line 4 in a rows
    //We check in groups of 4, if there is a space with an 'X' we add 1, if not, 0, if the sum is 4, player wins.
    
    //Columns:
    for (int j = 0; j <= N-1; j++){ //Fixed columns
        int count = 0;
        for (int i = N-1; i >= 3; i--){//Fix each starting point to go up 4 places to check
            count = 0;
            for (int k = 0; k < 4; k++){
                if (board[i-k][j] == player){
                    count++;
                }
            }
            if (count == 4){
                return true;
            }
        }
    }
    
    //Rows:
    
    for (int i = 0; i <= N-1; i++){ //Fixed rows
        int count = 0;
        for (int j = 0; j <= N-4; j++){//Fix each starting point to go up 4 places to check
            count = 0;
            for (int k = 0; k < 4; k++){
                if (board[i][j+k] == player){
                    count++;
                }
            }
            if (count == 4){
                return true;
            }
        }
    }
    
    //Right diagonals
    
    for (int m = 0; m <= N-4 ; m++){
        int count = 0;
        for (int i = 3; i <= N-1; i++){
            count = 0;
            for (int j = 0; i-j >=3; j++){
                count = 0;
                for (int k = 0; k < 4; k++){
                    if (k + j + m <= N-1 && board[i-j-k][k + j + m] == player){
                        count++;
                    }
                }
                if (count == 4){
                    return true;
                }
            }
        }
    }
    
    //Left diagonals
    
    for (int j = 3; j <= N-1; j++){
        int count = 0;
        for (int i = 0; j-i >=3; i++){
            count = 0;
            for (int k = 0; k < 4; k++){
                if (board[N-1-i-k][j-k] == player){
                    count++;
                }
            }
            if (count == 4){
                return true;
            }
        }
    }
    return false;
}

void printBoard(char board[N][N]){
    
    printf("%s\n", header);
    printf("%s\n", horbar);
    
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                if(board[i][j] == '0'){
                    printf("| %s%c%s ", AC_RED, board[i][j], AC_NORMAL);//IF COMPUTER, RED
                }
                else{
                    printf("| %s%c%s ", AC_GREEN, board[i][j], AC_NORMAL);//IF PLAYER, GREEN
                }
            }
            printf("|\n");
            printf("%s\n", horbar);
        }
    printf("\n");
}

void makePlay(char board[N][N], int play, char player){

    for (int i = N-1; i >= 0; i--){
        //We check if the item is empty in ascending order, if so, put the token there
        if (board[i][play] == ' '){
            board[i][play] = player;
            break;
        }
    }
}
