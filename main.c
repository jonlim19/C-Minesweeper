#include <stdio.h>
#include <stdlib.h>
#include "game_functions.h"
/*Name: Jonathan Lim Kean Lee
Student number: R00157806*/
int main()
{
   int _of_bombs = 2;
   struct locations* bombs = (struct locations*)malloc(sizeof(struct locations)*2) ;
   int bomb_location_info[DIM][DIM];
    int known_location_info[DIM][DIM] ={-1,-1,-1,-1,
                                    -1,-1,-1,-1,
                                    -1,-1,-1,-1,
                                    -1,-1,-1,-1};
    for(int i = 0; i <DIM; i++){
        for(int j = 0; j < DIM; j++ ){
            bomb_location_info[i][j] = generate_values(i,j,bombs);
        }
    }
    srand(time(NULL));
   bombs[0].x = (rand() % (DIM)) + 0;//1;
   bombs[0].y  = (rand() % (DIM)) + 0;//1;
   bombs[0].found = false;

   bombs[1].x = (rand() % (DIM)) + 0;//2;
   bombs[1].y  = (rand() % (DIM)) + 0;//3;
   bombs[1].found = false;

    if((bombs[0].x==bombs[1].x)&&(bombs[0].y==bombs[1].y)){
        bombs[0].x = (rand() % (DIM)) + 0;
        bombs[0].y  = (rand() % (DIM)) + 0;
        bombs[1].x = (rand() % (DIM)) + 0;
        bombs[1].y  = (rand() % (DIM)) + 0;
    }
    for(int i = 0; i <DIM; i++){
        for(int j = 0; j < DIM; j++ ){
            bomb_location_info[i][j] = generate_values(i,j,bombs);
        }
    }
    printf("bomb location: ");
    printf("%d",bombs[0].x);
    printf("%d",bombs[0].y);
    printf("\nbomb location: ");
    printf("%d",bombs[1].x);
    printf("%d",bombs[1].y);
    printf("\n");
     give_clues(bombs,bomb_location_info,DIM,known_location_info);
   start_game(bombs,bomb_location_info,DIM,known_location_info,_of_bombs);

   free(bombs);
}
