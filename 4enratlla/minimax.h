//
//  minimax.h
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 13/10/22.
//

#ifndef minimax_h
#define minimax_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "doubleuse.h"

#define WIN 100000
#define THREE 100
#define STANDARD 10

typedef struct node{
    char board[N][N];
    int index;
    int level;
    int n_sons;
    int *plays;
    struct node* *sons; //Un array de tamany desconegut, on guarda apuntadora a nodes.
    int value;
}Node;


int calcSons(char [N][N]);
Node *makeNode(Node *, int, int);
void make1level(Node *, int);
void makeLevelpair(Node *, int);
void makeTree(Node *, int, int);
void copyBoard(char [N][N], char [N][N]);
void eraseTree(Node *); //esborra tots els nodes de l’arbre, passant-li l’arrel.
int heuristic (Node *);
void valueLeafs (Node *);
void doMinimax(Node *); //retorna la columna escollida per a la millor jugada
int applyMinimax(char [N][N], int);
void printTreeVal(Node *);

#endif /* Header_h */
