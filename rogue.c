#include"rogue.h"

cell **load_map(int *size, char filename[])
{
  cell **map;
  int i, j;
  FILE *f;

  f = fopen(filename, "r");

  if(f!=NULL)
  {
    map = calloc(*size,sizeof(cell*));
    for (i=0; i<*size; i++)
    {
      map[i] = calloc(*size,sizeof(cell));
    }
    fscanf(f, "%d", size);
    for(i=0;i<*size;i++)
    {
      for(j=0;j<*size;j++)
      {
        fscanf(f, "%d", &map[i][j].value);
      }
    }
  }
  else
    printf("Error! Could not open the file.\n");

  fclose(f);

  return map;
}

void visualize_map(cell **map, int size, int px, int py, int win_size)
{
  int i,j;

  printf("\n");

  for(i=px-win_size/2;i<=px+win_size/2;i++)
  {
    for(j=py-win_size/2;j<=py+win_size/2;j++)
    {
      if(i<0 || j<0 || i>size-1 || j>size-1)
        printf("#");
      else
      {
        if(map[i][j].value==0)
          printf(" ");
        else if(map[i][j].value==1)
          printf("#");
        else if(map[i][j].value==2)
          printf("P");
        else if(map[i][j].value==3)
          printf("E");
        else if(map[i][j].value==4)
          printf("N");
      }
    }
    printf("\n");
  }
}

cell **initializemap(cell **map, int size)
{
  int i, j;

  map = calloc(size, sizeof(cell*));
  for(i=0;i<size;i++)
  {
    map[i] = calloc(size, sizeof(cell));
  }

  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      map[i][j].value = 1;
      map[i][j].visited = 0;
    }
  }

  return map;
}

int generate_random(cell **map, int size, int x, int y)
{
  int random; //0 -> down; 1 -> up; 2 -> right; 3 -> left

  if(x+2==size && y-2<0) //lower left corner
    {
      if(map[x-2][y].visited!=1 && map[x][y+2].visited!=1)
        random = rand()%2+1;
      else if(map[x-2][y].visited==1)
        random = 2;
      else if(map[x][y+2].visited==1)
        random = 1;
    }
  else if(x+2==size && y+2==size) //lower right corner
  {
    if(map[x][y-2].visited!=1 && map[x-2][y].visited!=1)
    {
      do{
        random = rand()%3+1;
      }while(random==2);
    }
    else if(map[x-2][y].visited==1)
      random = 3;
    else if(map[x][y-2].visited==1)
      random = 1;
  }
  else if(x+2==size) //last lower row
  {
    if(map[x][y-2].visited!=1 && map[x-2][y].visited!=1 && map[x][y+2].visited!=1)
      random = rand()%3+1;
    else if(map[x][y-2].visited==1 && map[x-2][y].visited==1)
      random = 2;
    else if(map[x-2][y].visited==1 && map[x][y+2].visited==1)
      random = 3;
    else if (map[x][y+2].visited==1 && map[x][y-2].visited==1)
      random = 1;
    else if(map[x][y-2].visited==1)
      random = rand()%2+1;
    else if(map[x-2][y].visited==1)
      random = rand()%2+2;
    else if(map[x][y+2].visited==1)
    {
      do{
        random = rand()%3+1;
      }while(random==2);
    }
  }
  else if(x-2<0 && y+2==size) //upper right corner
  {
    if(map[x+2][y].visited!=1 && map[x][y-2].visited!=1)
    {
      do{
        random = rand()%4;
      }while(random==1 || random==2);
    }
    else if(map[x+2][y].visited==1)
      random = 3;
    else if(map[x][y-2].visited==1)
      random = 0;
  }
  else if(x-2<0 && y-2<0) //upper left corner
  {
    if(map[x][y+2].visited!=1 && map[x+2][y].visited!=1)
    {
      do{
        random = rand()%3;
      }while(random==1);
    }
    else if(map[x][y+2].visited==1)
      random = 0;
    else if(map[x+2][y].visited==1)
      random = 2;
  }
  else if(x-2<0) //first upper row
  {
    if(map[x][y+2].visited!=1 && map[x+2][y].visited!=1 && map[x][y-2].visited!=1)
    {
      do{
        random = rand()%4;
      }while(random==1);
    }
    else if(map[x][y+2].visited==1 && map[x+2][y].visited==1)
      random = 3;
    else if(map[x+2][y].visited==1 && map[x][y-2].visited==1)
      random = 2;
    else if(map[x][y+2].visited==1 && map[x][y-2].visited==1)
      random = 0;
    else if(map[x][y+2].visited)
    {
      do{
        random = rand()%4;
      }while(random==1 || random==2);
    }
    else if(map[x+2][y].visited==1)
      random = rand()%2+2;
    else if(map[x][y-2].visited==1)
    {
      do{
        random = rand()%3;
      }while(random==1);
    }
  }
  else if(y+2==size) //last right column
  {
    if(map[x+2][y].visited!=1 && map[x][y-2].visited!=1 && map[x-2][y].visited!=1)
    {
      do{
        random = rand()%4;
      }while(random==2);
    }
    else if(map[x+2][y].visited==1 && map[x][y-2].visited==1)
      random = 1;
    else if(map[x][y-2].visited==1 && map[x-2][y].visited==1)
      random = 0;
    else if(map[x+2][y].visited==1 && map[x-2][y].visited==1)
      random = 3;
    else if(map[x+2][y].visited==1)
    {
      do{
        random = rand()%3+1;
      }while(random==2);
    }
    else if(map[x][y-2].visited==1)
      random = rand()%2;
    else if(map[x-2][y].visited==1)
    {
      do{
        random = rand()%4;
      }while(random==1 || random==2);
    }
  }
  else if(y-2<0) //first left column
  {
    if(map[x-2][y].visited!=1 && map[x][y+2].visited!=1 && map[x+2][y].visited!=1)
      random = rand()%3;
    else if(map[x-2][y].visited==1 && map[x][y+2].visited==1)
      random = 0;
    else if(map[x][y+2].visited==1 && map[x+2][y].visited==1)
      random = 1;
    else if(map[x-2][y].visited==1 && map[x+2][y].visited==1)
      random = 2;
    else if(map[x-2][y].visited==1)
    {
      do{
        random = rand()%3;
      }while(random==1);
    }
    else if(map[x][y+2].visited==1)
      random = rand()%2;
    else if(map[x+2][y].visited==1)
      random = rand()%2+1;
  }
  else //in the middle
  {
    if(map[x-2][y].visited!=1 && map[x][y+2].visited!=1 && map[x+2][y].visited!=1 && map[x][y-2].visited!=1)
      random = rand()%4;
    else if(map[x-2][y].visited==1 && map[x][y+2].visited==1 && map[x+2][y].visited==1)
      random = 3;
    else if(map[x][y+2].visited==1 && map[x+2][y].visited==1 && map[x][y-2].visited==1)
      random = 1;
    else if(map[x+2][y].visited==1 && map[x][y-2].visited==1 && map[x-2][y].visited==1)
      random = 2;
    else if(map[x][y-2].visited==1 && map[x-2][y].visited==1 && map[x][y+2].visited==1)
      random = 0;
    else if(map[x-2][y].visited==1 && map[x][y+2].visited==1)
    {
      do{
        random = rand()%4;
      }while(random==1 || random==2);
    }
    else if(map[x][y+2].visited==1 && map[x+2][y].visited==1)
    {
      do{
        random = rand()%3+1;
      }while(random==2);
    }
    else if(map[x+2][y].visited==1 && map[x][y-2].visited==1)
      random = rand()%2+1;
    else if(map[x][y-2].visited==1 && map[x-2][y].visited==1)
    {
      do{
        random = rand()%3;
      }while(random==1);
    }
    else if(map[x+2][y].visited==1 && map[x-2][y].visited==1)
      random = rand()%2+2;
    else if(map[x][y-2].visited==1 && map[x][y+2].visited==1)
      random = rand()%2;
    else if(map[x-2][y].visited==1)
    {
      do{
        random = rand()%4;
      }while(random==1);
    }
    else if(map[x][y+2].visited==1)
    {
      do{
        random = rand()%4;
      }while(random==2);
    }
    else if(map[x+2][y].visited==1)
      random = rand()%3+1;
    else if(map[x][y-2].visited==1)
      random = rand()%3;
  }

  return random;
}

int go_back(cell **map, int size)
{
  int i, j, out=0;
  for(i=1;i<size;i+=2)
  {
    for(j=1;j<size;j+=2)
    {
      if(map[i][j].visited!=1)
        out = 1;
    }
  }
  return out;
}

cell **generate_map(cell **map, int size, int x, int y)
{
  int moves, random;
  map[x][y].visited = 1;
  map[x][y].value = 0;
  moves = go_back(map, size);
  if(moves==0) //there are no more moves available, not even if I go back
    return map;
  else //I am blocked somewhere, I can go back and make other moves
  {
    //I am in the corners and I have visited the adjacent cells
    if(((x==1 && y==1) && (map[x][y+2].visited==1 && map[x+2][y].visited==1)) || ((x==1 && y==size-2) && (map[x+2][y].visited==1 && map[x][y-2].visited==1)) || ((x==size-2 && y==1) && (map[x-2][y].visited==1 &&map[x][y+2].visited==1)) || ((x==size-2 && y==size-2) && (map[x-2][y].visited==1 && map[x][y-2].visited==1)))
      return generate_map(map, size, map[x][y].xbefore, map[x][y].ybefore);
    //I am in the corners but I have not visited the adjacent cells
    else if((x==1 && y==1) || (x==1 && y==size-2) || (x==size-2 && y==1) || (x==size-2 && y==size-2))
    {
      random = generate_random(map, size, x, y);

      if(random==0)
      {
        map[x+1][y].visited = 1;
        map[x+1][y].value = 0;
        map[x+2][y].xbefore = x;
        map[x+2][y].ybefore = y;
        x += 2;
      }
      else if(random==1)
      {
        map[x-1][y].visited = 1;
        map[x-1][y].value = 0;
        map[x-2][y].xbefore = x;
        map[x-2][y].ybefore = y;
        x -= 2;
      }
      else if(random==2)
      {
        map[x][y+1].visited = 1;
        map[x][y+1].value = 0;
        map[x][y+2].xbefore = x;
        map[x][y+2].ybefore = y;
        y += 2;
      }
      else if(random==3)
      {
        map[x][y-1].visited = 1;
        map[x][y-1].value = 0;
        map[x][y-2].xbefore = x;
        map[x][y-2].ybefore = y;
        y -= 2;
      }

      return generate_map(map, size, x, y);
    }
    //I am on the sides and I have visited the adjacent cells
    else if((x==1 && (map[x][y+2].visited==1 && map[x+2][y].visited==1 && map[x][y-2].visited==1)) || (x==size-2 && (map[x][y+2].visited==1 && map[x-2][y].visited==1 && map[x][y-2].visited==1)) || (y==1 && (map[x-2][y].visited==1 && map[x][y+2].visited==1 && map[x+2][y].visited==1)) || (y==size-2 && (map[x-2][y].visited==1 && map[x][y-2].visited==1 && map[x+2][y].visited==1)))
      return generate_map(map, size, map[x][y].xbefore, map[x][y].ybefore);
    //I am on the sides but I have not visited the adjacent cells
    else if(x==1 || x==size-2 || y==1 || y==size-2)
    {
      random = generate_random(map, size, x, y);

      if(random==0)
      {
        map[x+1][y].visited = 1;
        map[x+1][y].value = 0;
        map[x+2][y].xbefore = x;
        map[x+2][y].ybefore = y;
        x += 2;
      }
      else if(random==1)
      {
        map[x-1][y].visited = 1;
        map[x-1][y].value = 0;
        map[x-2][y].xbefore = x;
        map[x-2][y].ybefore = y;
        x -= 2;
      }
      else if(random==2)
      {
        map[x][y+1].visited = 1;
        map[x][y+1].value = 0;
        map[x][y+2].xbefore = x;
        map[x][y+2].ybefore = y;
        y += 2;
      }
      else if(random==3)
      {
        map[x][y-1].visited = 1;
        map[x][y-1].value = 0;
        map[x][y-2].xbefore = x;
        map[x][y-2].ybefore = y;
        y -= 2;
      }

      return generate_map(map, size, x, y);
    }
    //I am in the middle of the map and I have visited the adjacent cells
    else if(map[x+2][y].visited==1 && map[x-2][y].visited==1 && map[x][y+2].visited==1 && map[x][y-2].visited==1)
      return generate_map(map, size, map[x][y].xbefore, map[x][y].ybefore);
    else
    {
      random = generate_random(map, size, x, y);

      if(random==0)
      {
        map[x+1][y].visited = 1;
        map[x+1][y].value = 0;
        map[x+2][y].xbefore = x;
        map[x+2][y].ybefore = y;
        x += 2;
      }
      else if(random==1)
      {
        map[x-1][y].visited = 1;
        map[x-1][y].value = 0;
        map[x-2][y].xbefore = x;
        map[x-2][y].ybefore = y;
        x -= 2;
      }
      else if(random==2)
      {
        map[x][y+1].visited = 1;
        map[x][y+1].value = 0;
        map[x][y+2].xbefore = x;
        map[x][y+2].ybefore = y;
        y += 2;
      }
      else if(random==3)
      {
        map[x][y-1].visited = 1;
        map[x][y-1].value = 0;
        map[x][y-2].xbefore = x;
        map[x][y-2].ybefore = y;
        y -= 2;
      }

      return generate_map(map, size, x, y);
    }
  }
}

void insert_player_exit_enemies(cell **map, int size)
{
  int xp, yp, xe, ye, xn, yn, i;

  //inserts the player
  do{
    xp = rand()%size;
    yp = rand()%size;
  }while(map[xp][yp].visited!=1);

  map[xp][yp].value = 2;

  //inserts the exit
  do{
    xe = rand()%size;
    ye = rand()%size;
  }while(map[xe][ye].visited!=1 || xe==xp || ye==yp);

  map[xe][ye].value = 3;

  //inserts the enemies
  for(i=0;i<size/4;i++)
  {
    do{
      xn = 1 + rand()%(size - 3);
      yn = 1 + rand()%(size - 3);
    }while((xn==xp && yn==yp) && xn==xp-1 && yn==yp+1 && xn==xp+1 && yn==yp-1);

    map[xn][yn].value = 4;
  }
}

void save_map(cell **map, int size, char filename[])
{
  FILE *f;
  int i, j;

  f = fopen(filename, "w");
  if(f!=NULL)
  {
    fprintf(f, "%d\n", size);
    for(i=0;i<size;i++)
    {
      for(j=0;j<size;j++)
      {
        fprintf(f, "%d ", map[i][j].value);
      }
      fprintf(f, "\n");
    }
  }
  else
    printf("Error! Could not open the file.\n");
}

void movement(cell **map, int size, int xp, int yp, int xe, int ye, int moves, int precmove)
{
  char move, quit, save, filename[20];
  
  CLEARSCREEN;

   if(size<20)
     visualize_map(map, size, xp, yp, size);
   else
     visualize_map(map, size, xp, yp, 20);
  
  if(precmove == 0)
      printf("\nMOVE NOT AVAILABLE, you cannot go through walls!\n");

  if(xp==xe && yp==ye)
  {
    printf("\nCONGRATULATIONS, YOU HAVE REACHED RHE EXIT IN %d MOVES!\n\n", moves);
    return;
  }
  else
  {
    moves++;

    printf("\nMove number %d", moves);
    do{
      printf("\nChoose the letter: [w]->up [a]->left [s]->down [d]->right [q]->quit:\n");
      scanf("%c%*c", &move);
    }while(move!='w' && move!='s' && move!='d' && move!='a' && move!='q');

    if(move == 'w') //up
    {
      if(map[xp-1][yp].value==0 || map[xp-1][yp].value==3)
      {
        map[xp-1][yp].value = 2;
        map[xp][yp].value = 0;
        xp--;
        precmove = 1;
      }
      else if(map[xp-1][yp].value==4)
      {
        printf("\nYOU LOST! An enemy has killed you.\n");
        return;
      }
      else
        precmove = 0;
    }
    else if(move == 's') //down
    {
      if(map[xp+1][yp].value==0 || map[xp+1][yp].value==3)
      {
        map[xp+1][yp].value = 2;
        map[xp][yp].value = 0;
        xp++;
        precmove = 1;
      }
      else if(map[xp+1][yp].value==4)
      {
        printf("\nYOU LOST! An enemy has killed you.\n");
        return;
      }
      else
        precmove = 0;
    }
    else if(move == 'd') //right
    {
      if(map[xp][yp+1].value==0 || map[xp][yp+1].value==3)
      {
        map[xp][yp+1].value = 2;
        map[xp][yp].value = 0;
        yp++;
        precmove = 1;
      }
      else if(map[xp][yp+1].value==4)
      {
        printf("\nYOU LOST! An enemy has killed you.\n");
        return;
      }
      else
        precmove = 0;
    }
    else if(move == 'a') //left
    {
      if(map[xp][yp-1].value==0 || map[xp][yp-1].value==3)
      {
        map[xp][yp-1].value = 2;
        map[xp][yp].value = 0;
        yp--;
        precmove = 1;
      }
      else if(map[xp][yp-1].value==4)
      {
        printf("\nYOU LOST! An enemy has killed you.\n");
        return;
      }
      else
        precmove = 0;
    }
    else if(move == 'q')
    {
      do{
        printf("\nAre you sure you want to quit? [y/n]\n");
        scanf("%c%*c", &quit);
      }while(quit!='y' && quit!='n');
      if(quit=='y')
      {
        do{
          printf("\nDo you want to save the progress of the game? [y/n]\n");
          scanf("%c%*c", &save);
        }while(save!='y' && save!='n');
        if(save=='y')
        {
          printf("\nEnter the name of the file on which you want to save the map:\n");
          scanf("%s", filename);
          save_map(map, size, filename);
        }
        return;
      }
      else
        precmove = 1;
    }

    //moves the enemies
    move_enemies(map, size);

    return movement(map, size, xp, yp, xe, ye, moves, precmove);
  }
}

void move_enemies(cell **map, int size)
{
  int i, j, k=0, xn[size/4], yn[size/4], move, temp, xp, yp, xe, ye;

  //finds where the enemies, the player and the exit are
  for(i=1;i<size-1;i++)
  {
    for(j=1;j<size-1;j++)
    {
      if(map[i][j].value==4) //enemies
      {
        xn[k] = i;
        yn[k] = j;
        k++;
      }
      else if(map[i][j].value==2) //player
      {
        xp = i;
        yp = j;
      }
      else if(map[i][j].value==3) //exit
      {
        xe = i;
        ye = j;
      }
    }
  }

  //moves the enemies
  for(i=0;i<k;i++)
  {
    int x, y;
    x = xn[i];
    y = yn[i];

    move = rand()%4;
    if(move==0 && x!=1 && x!=xp && y!=yp && x!=xe && y!=ye) //it cannot go over the player or the exit
    {
      map[x][y].value = 0;
      x--;
    }
    else if(move==1 && y!=size-2 && x!=xp && y!=yp && x!=xe && y!=ye) //it cannot go over the player or the exit
    {
      map[x][y].value = 0;
      y++;
    }
    else if(move==2 && x!=size-2 && x!=xp && y!=yp && x!=xe && y!=ye) //it cannot go over the player or the exit
    {
      map[x][y].value = 0;
      x++;
    }
    else if(move==3 && y!=1 && x!=xp && y!=yp && x!=xe && y!=ye) //it cannot go over the player or the exit
    {
      map[x][y].value = 0;
      y--;
    }

    map[x][y].value = 4;
  }
}
