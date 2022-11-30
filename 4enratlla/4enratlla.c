//
//  4enratlla.c
//  4 en ratlla
//
//  Created by Ricard Skrudlik on 13/10/22. NIU: 1516055
//  Programació Avançada UAB


//The code is divided in 3.c files, minimax.c has all the minimax functions, 4enratlla.c has all the 4enratlla functions and
//I've created an extra .c file for the functions which are both used in the minimax.c and 4enratlla.c. It has been coded for
//a MAC OSX user so some functionalities like color display or clean output won't work on a windows PC. Enjoy!!

#include "4enratlla.h"
#include "minimax.h"

//Board var, where we play the game

int main(){
    
    mainScreen();
    
    int mode = 0;
    char name1[20];
    char name2[20];
    int gamemode = 0;
    
    printf("Which game do you wish to play, 1vPC (1) or 1v1 (2)?: ");
    
    scanf(" %d", &mode);
    
    if (mode < 1 || mode > 2){
        printf("You chose a non possible gamemode, setting to gamemode 1 by default... \n");
        mode = 1;
    }
    
    if (mode == 1){
        
        printf("Which gamemode do you wish to play (1-EASY 2-MEDIUM 3-REALLY REALLY HARD): ");
        scanf("%d", &gamemode);
        
        if (gamemode > 0 && gamemode < 3){
            printf("HA HA HA, it seems you are going for an easy route... \n");
        }
        if (gamemode < 0 || gamemode > 3){
            printf("You chose a non valid gamemode, playing by default medium difficulty. \n");
            gamemode = 2;
        }
        
        printf("What's your name? ");
        scanf("%s", name1);
        
        char *namePC = computerName();
        printf("\n");
        printf("Very well %s, you will be playing against %s!! and %s will throw the first play (press ENTER to begin...) \n", name1, namePC, namePC);
        printf("\n");
        getchar();
        getchar();
        
        playComputer(gamemode, namePC, name1);
    }
    if (mode == 2){
        
        printf("Player 1, what's your name?: ");
        scanf("%s", name1);
        getchar();
        printf("Player 2, what's yours?: ");
        scanf("%s", name2);
        printf("\n");
        printf("Alright, let the game begin! to make a play choose a column (A---H). press ENTER to start... \n");
        getchar();
        getchar();
        
        twoPlayer(name1, name2);
    }
    return 0;
}

void twoPlayer(char name1[20], char name2[20]){
    
    int play;
    char board[N][N]; //Board var, where we play the game
    int turn = 0;
    char play_char = ' ';
    
    initBoard(board);
    
    printBoard(board);
    
    //Make a loop to keep playing, when someone wins, break the loop
    
    while(1){
        
        if (turn % 2 == 1){ //Then its player 1 turn
            printf("%s, your turn: ", name1);
            scanf(" %c", &play_char);
            
            play = choosePlay(play_char);
            if (checkFull(board, play)){
                printf("That is not an allowed move, try again (A--H) \n");
                turn--;
            }
            
            makePlay(board, play, p1);
            system("clear");
            printBoard(board);
            
            turn++;
            
            if (checkWin(p1, board)){//Check if player wins
                printf("%s wins! \n", name1);
                break;
            }
            
        }
        else{
            printf("%s, your turn: ", name2);
            scanf(" %c", &play_char);
            
            play = choosePlay(play_char);
            
            if (checkFull(board, play)){
                printf("That is not an allowed move, try again (A--H) \n");
                turn--;
            }
            makePlay(board, play, p2);
            system("clear");
            printBoard(board);
            turn++;
            
            if (checkWin(p2, board)){
                printf("%s wins! \n", name2);
                break;
            }
        }
    }
}

void playComputer(int gamemode, char *namePC, char name1[20]){
    
    int play;
    char play_char = ' ';
    char board[N][N]; //Board var, where we play the game
    
    initBoard(board);
    
    //Make a loop to keep playing, when someone wins, break the loop
    
    int turn = 1;
    
    while(1){
        
        if (turn % 2 == 0){ //Then its player
            printf("Choose play: ");
            scanf("%s", &play_char);
            play = choosePlay(play_char);
            
            if (play == 99 || checkFull(board, play)){ //If the play is not legal nor supported.
                printf("That is not an allowed move, try again (A--H) \n");
                turn -= 1;
            }
            //system("clear");
            turn++;
            makePlay(board, play, p1);
            printBoard(board);
            if (checkWin(p1, board)){//Check if player wins
                printf("%sYou won!!! \n %s \n", AC_GREEN, AC_NORMAL);
                break;
            }
        }
        else if (turn % 2 == 1){ //Computer
            system("clear");
            turn++;
            play = applyMinimax(board, gamemode);
            makePlay(board, play, p2);
            printBoard(board);
            if (checkWin(p2, board)){//Check if player wins
                printf("%sOh... %s wins :( \n %s", AC_RED, namePC, AC_NORMAL);
                break;
            }
        }
    }
}

//Function to init the board array, we will put empty strings

void initBoard(char board[N][N]) {
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            board[i][j] = ' ';
        }
    }
}

//We make the player choose which column does he want to play on.

int choosePlay(char play_char){
    
    int play;
    
    if (play_char == 'A' || play_char == 'a'){
        play = 0;
    }
    else if (play_char == 'B' || play_char == 'b'){
        play = 1;
    }
    else if (play_char == 'C' || play_char == 'c'){
        play = 2;
    }
    else if (play_char == 'D' || play_char == 'd'){
        play = 3;
    }
    else if (play_char == 'E' || play_char == 'e'){
        play = 4;
    }
    else if (play_char == 'F' || play_char == 'f'){
        play = 5;
    }
    else if (play_char == 'G' || play_char == 'g'){
        play = 6;
    }
    else if (play_char == 'H' || play_char == 'h'){
        play = 7;
    }
    else {
        play = 99;
    }
    
    return play;
    
}

void mainScreen(){
    
    printf("%s\n",AC_YELLOW);
    printf("\n");
    printf("\n");
    printf("\n");
    printf("              -----------     -----------    ---      --    ---      --    -----------    -----------    -----------         -----  \n");
    printf("              -----------     -----------    ----     --    ----     --    -----------    -----------    -----------       ---- --  \n");
    printf("              ----            --       --    --  ---  --    --  ---  --    ----           ----               ---         ----   --  \n");
    printf("              ----            --       --    --   --- --    --   --- --    -----------    ----               ---        ----    --  \n");
    printf("              ----            --       --    --     -- -    --     -- -    ----           ----               ---        ----------- \n");
    printf("              -----------     -----------    --      ---    --      ---    -----------    -----------        ---                --  \n");
    printf("              -----------     -----------    --      ---    --      ---    -----------    -----------        ---               ---  \n");
    printf("\n");
    printf("\n");
    printf("                                                             By Ricard Skrudlik, 2022                                             \n ");
    printf("                            %s\n", AC_NORMAL);
    
    
}

char *computerName(){
    
    char *names[4];
    names[0] = "Mike";
    names[1] = "Alo";
    names[2] = "Linda";
    names[3] = "Gabby";
    
    srand(time(NULL));
    
    int index = rand()%4;
    
    return names[index];
}
