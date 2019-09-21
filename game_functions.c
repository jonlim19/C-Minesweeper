#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_functions.h"
/*Name: Jonathan Lim Kean Lee
Student number: R00157806*/
char get_user_char() {

    char res = getchar();
    bool finish = false;
    char dummy_char = ' ';

    while (finish == false) {
        dummy_char = getchar();
        if (dummy_char == '\n')
            finish = true;
    }

    return res;
}

void display(int known_location_info[][DIM], int size){
    printf("A B C D\n");
    for(int i = 0; i <size; i++){
        for(int j = 0; j < DIM; j++ ){
            if(known_location_info[i][j]==-1){
                printf("* ");
            }else if(known_location_info[i][j]==BOMB){
                printf("B");
            }else{
                printf("%d ",known_location_info[i][j]);
            }
        }
        printf("\n");
    }
}

void update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM]){
    known[row-65][col-65]=bomb_info[row-65][col-65];
}

void check_found(int row, int col, struct locations bombs[], int size, bool* found){
    int* x0 = &bombs[0].x;
    int* y0 = &bombs[0].y;
    int* x1 = &bombs[1].x;
    int* y1 = &bombs[1].y;
    if(*x0==row-'A' && *y0==col-'A'){
        bombs[0].found = true;
        *found = true;

    }else if(*x1==row-'A' && *y1==col-'A'){
        bombs[1].found = true;
        *found = true;
    }else{
        *found = false;
    }
}

void give_clues(struct locations *   bombs,int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM]){
    printf("Would you like to have 2 clues?[y/n]");
    char answer = get_user_char();
    if(answer=='y'){
        srand(time(NULL));
        int num = (rand() % (DIM)) + 0;
        int num1 = (rand() % (DIM)) + 0;
        int num2 = (rand() % (DIM)) + 0;
        int num3 = (rand() % (DIM)) + 0;

        int clues_given = 0;

        if(((num==bombs[0].x&&num1==bombs[0].y)||(num==bombs[1].x&&num1==bombs[1].y))||((num2==bombs[0].x&&num3==bombs[0].y)||(num2==bombs[1].x&&num3==bombs[1].y)/*is_it_a_bomb==true&&is_it_a_bomb2==true*/)){
            printf("Invalid clue spot");
            num = (rand() % (DIM)) + 0;
            num1 = (rand() % (DIM)) + 0;
            num2 = (rand() % (DIM)) + 0;
            num3 = (rand() % (DIM)) + 0;
        }else{
            update_known_info(num+65,num1+65,bomb_location_info,players_info);
            update_known_info(num2+65,num3+65,bomb_location_info,players_info);
            display(players_info, DIM);
            int i = 0;
            while(i<3){
                printf("Would you like more clues?(Type clues to get a clue)");
                char want_clues = get_user_char();
                if(want_clues=='c'){
                    update_known_info(((rand() % (DIM)) + 0)+65,((rand() % (DIM)) + 0)+65,bomb_location_info,players_info);
                    display(players_info, DIM);
                }else{
                    i = 3;
                }
                i++;
            }
        }
    }
}

int generate_values(int row,int col,struct locations bombs[]){
    int num_bombs = 0;
    //Bottom right diagonal
    if(((row+1)==bombs[0].x&&(col+1)==bombs[0].y)||((row+1)==bombs[1].x&&(col+1)==bombs[1].y)){
            num_bombs = num_bombs + 1;
    }
    //Top left diagonal
    if(((row-1)==bombs[0].x&&(col-1)==bombs[0].y)||((row-1)==bombs[1].x&&(col-1)==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }
    //Top Right diagonal
    if(((row+1)==bombs[0].x&&(col-1)==bombs[0].y)||((row+1)==bombs[1].x&&(col-1)==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }
    //Bottom left diagonal
    if(((row-1)==bombs[0].x&&(col+1)==bombs[0].y)||((row-1)==bombs[1].x&&(col+1)==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }

    if((row==bombs[0].x&&(col+1)==bombs[0].y)||(row==bombs[1].x&&(col+1)==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }

    if((row==bombs[0].x&&(col-1)==bombs[0].y)||(row==bombs[1].x&&(col-1)==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }

    if(((row+1)==bombs[0].x&&col==bombs[0].y)||((row+1)==bombs[1].x&&col==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }

    if(((row-1)==bombs[0].x&&col==bombs[0].y)||((row-1)==bombs[1].x&&col==bombs[1].y)){
        num_bombs = num_bombs + 1;
    }
    return num_bombs;
}

void start_game(struct locations *   bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs){
    enum game_status  {STILL_ALIVE, GAME_OVER};
    enum game_status status = STILL_ALIVE;
    bool found = false;
    int number_clues_found = 0;
    bool phaseonecomplete = false;
   while(status==STILL_ALIVE&&phaseonecomplete==false){
        printf("Number of clues guessed: %d\n",number_clues_found);
        display(players_info, DIM);
        printf("Enter a row position: ");
        char row = get_user_char();
        printf("Enter a column position: ");
        char col = get_user_char();
        if((row <= 65 && col >= 90)){
            printf("Please enter an uppercase character between A-D");
        }else{
            if(players_info[row-65][col-65] != UNKNOWN){
                printf("You have tried that location");
            }else{
                check_found(row, col, bombs, DIM, &found);
                if(found==true){
                    status=GAME_OVER;
                    bomb_location_info[row][col] = 'B';
                    printf("You stepped on a bomb! You lost!");
                    break;
                }else{
                    status=STILL_ALIVE;
                    update_known_info(row,col,bomb_location_info,players_info);
                    number_clues_found = number_clues_found + 1;
                    if(number_clues_found==5){
                        phaseonecomplete = true;
                    }
                }
            }
        }

        display(players_info, DIM);
   }
    printf("Begin Phase 2: \n");
    int number_found = 0;
    while(status==STILL_ALIVE&&phaseonecomplete==true){
        printf("bomb location: ");
        printf("%d",bombs[0].x);
        printf("%d",bombs[0].y);
        printf("\nbomb location: ");
        printf("%d",bombs[1].x);
        printf("%d",bombs[1].y);
        printf("\n");
        printf("Number of bombs found: %d\n",number_found);
        display(players_info, DIM);
        printf("Enter a row position: ");
        char row = get_user_char();
        printf("Enter a column position: ");
        char col = get_user_char();
        if((row <= 65 && col >= 90)){
            printf("Please enter an uppercase character between A-D");
        }else{
            display(players_info, DIM);
            if(players_info[row-65][col-65] != UNKNOWN){
                printf("You have tried that location");
            }else{
                check_found(row, col, bombs, DIM, &found);
                if(found==true){
                    update_known_info(row,col,bomb_location_info,players_info);
                    number_found = number_found + 1;

                }else{
                    printf("You did not find all 2 bombs! You lost!");
                    status = GAME_OVER;
                }

                if(number_found==2){
                    status=GAME_OVER;
                    printf("Congratulations you won");
                }

            }
        }


    }

}
