//
//  doubleuse.h
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 29/11/22.
//

#ifndef doubleuse_h
#define doubleuse_h
#define p1 'X' //The player 1 is 'X', and player 2 is '0'.
#define p2 '0'
//COLORS
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"
#define N 8 //The size of the board will be 8x8

#include <stdbool.h>
#include <stdio.h>

void makePlay(char [N][N], int, char);
bool checkWin(char player, char board[N][N]); //Check for possible 4 in a rows
void printBoard(char [N][N]); //Fucntion to print the board
bool checkFull(char [N][N], int); //

#endif /* doubleuse_h */
