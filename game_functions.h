#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED
#define DIM 4
#define UNKNOWN -1
#define BOMB -2
#include <stdbool.h>
/*Name: Jonathan Lim Kean Lee
Student number: R00157806*/
struct locations {
    int x;
    int y;
    bool found;
};
int generate_values(int row,int col,struct locations bombs[]);
void display(int known_location_info[][DIM], int size);
void update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM]);
void check_found(int row, int col, struct locations bombs[], int size, bool* found);
void start_game(struct locations *   bombs, int bomb_location_info[][DIM], int size_of_grid, int players_info[][DIM], int no_of_bombs);
char get_user_char();
#endif // GAME_FUNCTIONS_H_INCLUDED
