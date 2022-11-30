//
//  minimax.c
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 13/10/22.
//

#include "minimax.h"
#include "doubleuse.h"

int valueGlobal = 0;

Node *makeNode(Node *father, int col, int gamemode){ //int level ens diu el numero de level on estem, 1 o 2
    
    int j = 0;
    
    Node *p = malloc(sizeof(Node)); //Reservem l'espai
    copyBoard(p -> board, father -> board); //First copy board, standard value and add 1 level, then make a play, and check n_sons
    p -> value = valueGlobal;
    p -> level = father -> level + 1;
    
    if (p -> level%2 == 1){ //PC turn
        makePlay(p -> board, col, p2);
    }
    else{ //Then user turn
        makePlay(p -> board, col, p1);
    }
    
    p -> n_sons = calcSons(p -> board);

    if (p -> level == 2*gamemode || checkWin(p1, p -> board) || checkWin(p2, p-> board)){//If last play or alredy won, this node has no sons
        p -> n_sons = 0;
    }
    if (p -> n_sons != 0){
        p -> sons = malloc(p -> n_sons * sizeof(Node *)); //Create the sons array and the plays array
        p -> plays = (int *) malloc(p -> n_sons*sizeof(int));
        
        for (int i=0; i < N; i++){
            
            if (p -> board[0][i] == ' '){
                p -> plays[j] = i;
                j++;
            }
        }
    }
    
    else {  //Node leaf, no hi ha mes sons
        p -> plays = NULL;
        p -> sons = NULL;
    }
    
    return p;
    
}

void make1level(Node *father, int gamemode) { //Crea els levels a partir del father
    
  for (int i=0; i < father -> n_sons; i++) { //Per cada un dels possibles sons del father, crees un node i l'emmagatzemes
    father -> sons[i] = makeNode(father, father -> plays[i], gamemode); //Omple el array sons ple d'apuintadors a nodes with (node, index, level, mode)
  }
}


void makeTree(Node *root, int gamemode, int total){
    
  makeLevelpair(root, gamemode); //Crea els sons de level 1
    
    if (total == 0){//No crear més nivells
        return;
    }
    else{
        for(int i=0; i < root -> n_sons; i++){
            for(int j=0; j < root -> sons[i] -> n_sons; j++){
                makeTree(root -> sons[i] -> sons[j], gamemode, total -1);
            }
        }
    }
    return;
}

void makeLevelpair(Node *father, int gamemode){
    make1level(father, gamemode);
    for (int i = 0; i < father -> n_sons; i++){
        make1level(father -> sons[i], gamemode);
    }
    
}

//FUNCIONS PER A FER LA TIRADA

int calcSons(char board[N][N]){
    
    int num = 0;
 
    for (int j = 0; j <= N-1; j++){
        
        if (board[0][j] == ' '){
            num++;
        }
    }
    
    return num;
    
}

void eraseTree(Node *root){ // Funció que esborra tot l'arbre de baix cap a dalt recursivament
    
    if (root -> n_sons == 0){ //Si no te sons, l'esborrem
            free(root);
    }
    else{
        
        for (int i=0; i < root -> n_sons; i++){ //Si te sons, entrem a dins dels sons
            eraseTree(root -> sons[i]);
        }
        free (root -> sons);
        free (root -> plays);
    }
    
    
} //esborra tots els nodes de l’arbre, passant-li l’root.

void valueLeafs (Node *root){ //Recursiva, comencem des d'abaix, si és leaf valueem, si no baixem.
    
    if (root -> n_sons == 0){
        root -> value = heuristic(root);
    }
    else {
        for (int i = 0; i < root -> n_sons; i++){
            valueLeafs(root -> sons[i]);
        }
    }
    
    
}

int heuristic (Node *leaf){
    
        //Per a la funció heuristica, donarem un value molt alt si ordinador fa 4 en ratlla (guanya) molt baix si jugador fa 4 en ratlla (perd) i força alt si fa ordinador fa 3 en ratlla amb potencial 4 en ratlla.
    
    if (checkWin(p2, leaf -> board)){ //Guanya ordinador
        return WIN;
        
    }
    else if (checkWin(p1, leaf -> board)){ //Guanya el jugador
        return -WIN;
    }
    
    /*else if (check3(p2, leaf -> board, leaf -> index)){ //Bona jugada
        return THREE;
    }
     */
    else{
        return STANDARD; //Jugada normal
    }
}

void doMinimax(Node *root){
    if (root -> n_sons != 0){
        
        for (int i = 0; i < root -> n_sons; i++){ //Baixem a l'ultim node de l'arbre
            if (root -> sons[i] -> n_sons != 0){ //Fins que no sigui una leaf, fem el minimax
                doMinimax(root -> sons[i]);
            }
        }
        
        if (root -> level % 2 == 0){ // És torn jugador, per tant agafarem el maxim dels seus sons
            root -> value = root -> sons[0] -> value;
            for (int i = 1; i < root -> n_sons; i++){
                if (root -> sons[i] -> value > root -> value){
                    root -> value = root -> sons[i] -> value;
                }
            }
        }
        
        if (root -> level % 2 == 1){ // És torn jugador, per tant agafarem el mínim dels seus sons
            root -> value = root -> sons[0] -> value;
            for (int i = 1; i < root -> n_sons; i++){
                if (root -> sons[i] -> value < root -> value){
                    root -> value = root -> sons[i] -> value;
                }
            }
        }
    }
}

int applyMinimax(char board[N][N], int gamemode){
    
    int j = 0;
    
    Node *p = malloc(sizeof(Node)); //Creem el node father
    copyBoard(p -> board, board);
    p -> n_sons = calcSons(p -> board);
    p -> sons = malloc(p -> n_sons * sizeof(Node *));
    p -> level = 0;
    p -> plays = (int *) malloc(p -> n_sons*sizeof(int));
    
    for (int i=0; i < N; i++){//Omplim els indexos amb les columnes NO plenes
        
        if (p -> board[0][i] == ' '){
            p -> plays[j] = i;
            j++;
        }
    }
    
//Create tree, value leafs and apply minimax
    
    makeTree(p, gamemode, gamemode);
    valueLeafs(p);
    doMinimax(p);
    
    //printTreeVal(p);
    
    int possible_plays[N];
    int n = 0;
    int result = 0;
    for (int i = 0; i < N; i++){
        possible_plays[i] = 99;
    }
        
    for (int i = 0; i < p -> n_sons; i++){
        
        if (p -> sons[i] -> value == p -> value){ //Check if son value is equal to father (then its a possible throw)
                
            possible_plays[n] = p -> plays[i];
            n++;
        }
    }
    eraseTree(p);
    
    srand(time(NULL));
    
    for (int i = 0; i < 60; i++){//We give enough "room" for all indexes to be obtained
        result = rand() % p -> n_sons;
        
        if (possible_plays[result] != 99){//Then its a possible throw
            return possible_plays[result];
        }
    }
    
//If every throw is possible just pick any
    
    result = rand()%p -> n_sons;
    return possible_plays[result];
    
}


void printTreeVal(Node *root){

    /*
    printf(" value root: %i ", root -> value);
    for (int i = 0; i < root -> n_sons; i++){
        printf("--------------");
        printf("value node %i: %i \n", i, root -> sons[i] -> value);
        for (int j = 0; j < root -> sons[i] -> n_sons; j++){
            printf("value leaf %i; %i \n", j, root -> sons[i] -> sons[j] -> value);
        }
    }
     */
    
    char * tab = "";
    if (root -> level != 0){
        tab = (char *) malloc((2*root -> level + 1) * sizeof(char));
        int j; for (j=0; j < 2*root -> level; j++) tab[j] = ' ';
        tab[2*root->level] = '\0';
    }
    if (root->n_sons == 0) printf("%sNodo (valor %d)\n", tab, root -> value);
    else{
        int i;
        printf("%sNodo (valor %d)\n", tab, root -> value);
        for (i=0;i < root -> n_sons;i++) printTreeVal(root->sons[i]);
    }
    free(tab);
}

void copyBoard(char board1[N][N], char board2[N][N]){
    
    for (int i = 0; i < N; i++){
        for(int j= 0; j < N; j++){
            board1[i][j] = board2[i][j];
        }
    }
    
}
