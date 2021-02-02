#include"rogue.h"

int main()
{
  char choice, filename[20], choice2, continue;
  int size, i, j, xp, yp, xe, ye;
  FILE *f;
  cell **map;
  srand(time(NULL));

  printf("\n-HOW TO PLAY-\n\n");
  printf("The goal of the game is to reach the exit of the maze avoiding the enemies.If the player occupies the same cell as an enemy, they will be killed. The player CANNOT go through walls, the enemies can. The enemies move randomly at the end of every turn and dig the walls as they pass through them, creating new passages. The maze is centred on the player, therefore you will not be able to see the whole maze. \n");
  printf("At the beginnning of the game, you will be asked if you want to load the map from file or if you prefer to generate it randomly, the file must be saved in the same folder as the program. If you decide to generate the map randomly, you will be asked to enter its dimension, which must be an uneven number greater than 9. Next, you will be asked whether or not you want to save the generated map on file. If it is not an already existing file, it will be automatically created in the same folder of the program.\n");
  printf("If you want to quit the game, the program will ask you if you want to save the progress of the game and, if that is the case, you will have to enter the name of the file. This file can be the same as the one on which you had decided to save the map or not.\n");

  do{
    printf("\nEnter 'c' if you want to load the map from file, enter 'g' if you want to generate it randomly:\n");
    scanf("%c%*c", &choice);
  }while(choice!='c' && choice!='g');

  if(choice=='c')
  {
    printf("Enter the name of the file containing the map:\n");
    scanf("%s%*c", filename);

    f=fopen(filename, "r");

    if(f!=NULL)
    {
      fscanf(f, "%d", &size);
      map = load_map(&size, filename);
    }
    else
      printf("Error! Could not open the file %s.", filename);

    fclose(f);
  }
  else if(choice=='g')
  {
    do{
      printf("Enter the dimension of the map (it must be uneven and greater than 9):\n");
      scanf("%d%*c", &size);
    }while(size%2==0 || size<=9);


    map = initializemap(map, size);

    map = generate_map(map, size, 1, 1);

    insert_player_exit_enemies(map, size);

    do{
      printf("Do you want to save the map on file? [y/n]\n");
      scanf("%c%*c", &choice2);
    }while(choice2!='y' && choice2!='n');

    if(choice2=='y')
    {
      printf("Enter the name of the file in which you want to save the map:\n");
      scanf("%s%*c", filename);
      save_map(map, size, filename);
    }
  }

  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      if(map[i][j].value==2) //finds the position of the player
      {
        xp = i;
        yp = j;
      }
      else if(map[i][j].value==3) //finds the position of the exit
      {
        xe = i;
        ye = j;
      }
    }
  }

  printf("\nLegend:\nP -> player\nN -> enemy\nE -> exit\n# -> wall\n  -> viable passage\n");
  printf("\nEnter the following letters to move:\nw -> up\ns -> down\nd -> right\na -> left\nq -> quit\n\nPress enter to confirm your move. It may be necessary to insert the same letter twice before before pressing enter.\n");
  printf("Press Enter to continue\n");
  scanf("%c", &continue);
  
  movement(map, size, xp, yp, xe, ye, 0, 1);

  return 0;
}
