//
//  4enratlla.h
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 13/10/22.
//

#ifndef _enratlla_h
#define _enratlla_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minimax.h"

void mainScreen(void);
void initBoard(char [N][N]); //Initialize the board as blank spaces
int choosePlay(char); //The player chooses which column does he want to play
void twoPlayer(char[20], char[20]);
void playComputer(int, char *, char[20]);
char *computerName(void);

#endif /* _enratlla_h */
