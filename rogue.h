#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifdef _WIN32
  #define CLEARSCREEN system("cls")
#else
  #define CLEARSCREEN system("clear")
#endif

typedef struct{
  int visited; // if the cell has been visited, this value is 1
  int value; //value of the cell
  int xbefore; //x of the cell from which I am coming
  int ybefore; //y of the cell from which I am coming
}cell;

cell **load_map(int *size, char filename[]); //loads the map from file, returns the map using a double pointer

void visualize_map(cell **map, int size, int px, int py, int win_size); //prints the map

cell **initializemap(cell **map, int size); //initializes the map to 1

int generate_random(cell **map, int size, int x, int y); //generates a random number based on the player's position

cell **generate_map(cell **map, int size, int x, int y); // generates the map randomly and returns it

void save_map(cell **map, int size, char filename[]); //saves the map on a .txt file named filename

void insert_player_exit_enemies(cell **map, int size); //chooses randomly the player's, the exit's and the enemies' positions

int go_back(cell **map, int size); //returns 0 if there are not any more paths available

void movement(cell **map, int size, int xp, int yp, int xe, int ye, int moves, int precmove); //asks the user the next move and moves the player

void move_enemies(cell **map, int size); //finds the enemies and moves them of one cell
