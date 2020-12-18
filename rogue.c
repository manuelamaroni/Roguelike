#include"rogue.h"

cella **load_map(int *size, char filename[])
{
  cella **map;
  int i, j;
  FILE *f;

  f = fopen(filename, "r");

  if(f!=NULL)
  {
    map = calloc(*size,sizeof(cella*));
    for (i=0; i<*size; i++)
    {
      map[i] = calloc(*size,sizeof(cella));
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
    printf("Errore! Non sono riuscito ad aprire il file.\n");

  fclose(f);

  return map;
}

void visualize_map(cella **map, int size, int px, int py, int win_size)
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

cella **inizializemap(cella **map, int size)
{
  int i, j;

  map = calloc(size, sizeof(cella*));
  for(i=0;i<size;i++)
  {
    map[i] = calloc(size, sizeof(cella));
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

int generate_random(cella **map, int size, int x, int y)
{
  int random; //0 -> basso; 1 -> alto; 2 -> destra; 3 -> sinistra

  if(x+2==size && y-2<0) //sono nell'angolo in basso a sinistra
    {
      if(map[x-2][y].visited!=1 && map[x][y+2].visited!=1)
        random = rand()%2+1;
      else if(map[x-2][y].visited==1)
        random = 2;
      else if(map[x][y+2].visited==1)
        random = 1;
    }
  else if(x+2==size && y+2==size) //sono nell'angolo in basso a destra
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
  else if(x+2==size) //sono nell'ultima linea in basso
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
  else if(x-2<0 && y+2==size) //sono nell'angolo in alto a destra
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
  else if(x-2<0 && y-2<0) //sono nell'angolo in alto a sinistra
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
  else if(x-2<0) //sono nella prima riga in alto
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
  else if(y+2==size) //sono nell'ultima colonna a destra
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
  else if(y-2<0) //sono nella prima colonna a sinistra
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
  else //sono in mezzo alla mappa
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

int torno_indietro(cella **map, int size)
{
  int i, j, ritorna=0;
  for(i=1;i<size;i+=2)
  {
    for(j=1;j<size;j+=2)
    {
      if(map[i][j].visited!=1)
        ritorna = 1;
    }
  }
  return ritorna;
}

cella **generate_map(cella **map, int size, int x, int y)
{
  int mosse, random;
  map[x][y].visited = 1;
  map[x][y].value = 0;
  mosse = torno_indietro(map, size);
  if(mosse==0) //non ci sono più mosse disponobili nemmeno se torno indietro
    return map;
  else //sono bloccata da qualche parte, posso tornare indietro e fare altre mosse
  {
    //sono negli angoli e ho visitato le celle adiacenti
    if(((x==1 && y==1) && (map[x][y+2].visited==1 && map[x+2][y].visited==1)) || ((x==1 && y==size-2) && (map[x+2][y].visited==1 && map[x][y-2].visited==1)) || ((x==size-2 && y==1) && (map[x-2][y].visited==1 &&map[x][y+2].visited==1)) || ((x==size-2 && y==size-2) && (map[x-2][y].visited==1 && map[x][y-2].visited==1)))
      return generate_map(map, size, map[x][y].xbefore, map[x][y].ybefore);
    //sono negli angoli ma non ho visitato le celle adiacenti
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
    //sono ai lati e ho visitato le celle adiacenti
    else if((x==1 && (map[x][y+2].visited==1 && map[x+2][y].visited==1 && map[x][y-2].visited==1)) || (x==size-2 && (map[x][y+2].visited==1 && map[x-2][y].visited==1 && map[x][y-2].visited==1)) || (y==1 && (map[x-2][y].visited==1 && map[x][y+2].visited==1 && map[x+2][y].visited==1)) || (y==size-2 && (map[x-2][y].visited==1 && map[x][y-2].visited==1 && map[x+2][y].visited==1)))
      return generate_map(map, size, map[x][y].xbefore, map[x][y].ybefore);
    //sono ai lati ma non ho visitato le celle adiacenti
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
    //sono all'interno della mappa ma ho visitato tutte le celle adiacenti
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

void insert_player_exit_enemies(cella **map, int size)
{
  int xp, yp, xe, ye, xn, yn, i;

  //inserisco il player
  do{
    xp = rand()%size;
    yp = rand()%size;
  }while(map[xp][yp].visited!=1);

  map[xp][yp].value = 2;

  //inserisco l'uscita
  do{
    xe = rand()%size;
    ye = rand()%size;
  }while(map[xe][ye].visited!=1 || xe==xp || ye==yp);

  map[xe][ye].value = 3;

  //inserisco i nemici
  for(i=0;i<size/4;i++)
  {
    do{
      xn = 1 + rand()%(size - 3);
      yn = 1 + rand()%(size - 3);
    }while((xn==xp && yn==yp) && xn==xp-1 && yn==yp+1 && xn==xp+1 && yn==yp-1);

    map[xn][yn].value = 4;
  }
}

void save_map(cella **map, int size, char filename[])
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
    printf("Errore! Non sono riuscito ad aprire il file.\n");
}

void movimento(cella **map, int size, int xp, int yp, int xe, int ye, int mosse, int mossaprec)
{
  char move, abbandona, salva, filename[20];

  if(mossaprec==1) //se la mossa precedente era valida, stampo la mappa aggiornata, altrimenti no
  {
    if(size<20)
      visualize_map(map, size, xp, yp, size);
    else
      visualize_map(map, size, xp, yp, 20);
  }

  if(xp==xe && yp==ye)
  {
    printf("\nCOMPLIMENTI, HAI RAGGIUNTO L'USCITA IN %d MOSSE!\n\n", mosse);
    return;
  }
  else
  {
    mosse++;

    printf("\nMossa numero %d", mosse);
    do{
      printf("\nScegli il comando [w]->su [a]->sinistra [s]->giu [d]->destra [q]->abbandona:\n");
      scanf("%c%*c", &move);
    }while(move!='w' && move!='s' && move!='d' && move!='a' && move!='q');

    if(move == 'w') //su
    {
      if(map[xp-1][yp].value==0 || map[xp-1][yp].value==3)
      {
        map[xp-1][yp].value = 2;
        map[xp][yp].value = 0;
        xp--;
        mossaprec = 1;
      }
      else if(map[xp-1][yp].value==4)
      {
        printf("\nHAI PERSO! Un nemico ti ha ucciso.\n");
        return;
      }
      else
      {
        printf("\nMOSSA NON DISPONIBILE, non puoi passare in mezzo ai muri!\n");
        mossaprec = 0;
      }
    }
    else if(move == 's') //giù
    {
      if(map[xp+1][yp].value==0 || map[xp+1][yp].value==3)
      {
        map[xp+1][yp].value = 2;
        map[xp][yp].value = 0;
        xp++;
        mossaprec = 1;
      }
      else if(map[xp+1][yp].value==4)
      {
        printf("\nHAI PERSO! Un nemico ti ha ucciso.\n");
        return;
      }
      else
      {
        printf("\nMOSSA NON DISPONIBILE, non puoi passare in mezzo ai muri!\n");
        mossaprec = 0;
      }
    }
    else if(move == 'd') //destra
    {
      if(map[xp][yp+1].value==0 || map[xp][yp+1].value==3)
      {
        map[xp][yp+1].value = 2;
        map[xp][yp].value = 0;
        yp++;
        mossaprec = 1;
      }
      else if(map[xp][yp+1].value==4)
      {
        printf("\nHAI PERSO! Un nemico ti ha ucciso.\n");
        return;
      }
      else
      {
        printf("\nMOSSA NON DISPONIBILE, non puoi passare in mezzo ai muri!\n");
        mossaprec = 0;
      }
    }
    else if(move == 'a') //sinistra
    {
      if(map[xp][yp-1].value==0 || map[xp][yp-1].value==3)
      {
        map[xp][yp-1].value = 2;
        map[xp][yp].value = 0;
        yp--;
        mossaprec = 1;
      }
      else if(map[xp][yp-1].value==4)
      {
        printf("\nHAI PERSO! Un nemico ti ha ucciso.\n");
        return;
      }
      else
      {
        printf("\nMOSSA NON DISPONIBILE, non puoi passare in mezzo ai muri!\n");
        mossaprec = 0;
      }
    }
    else if(move == 'q')
    {
      do{
        printf("\nSei sicuro di voler abbandonare? [y/n]\n");
        scanf("%c%*c", &abbandona);
      }while(abbandona!='y' && abbandona!='n');
      if(abbandona=='y')
      {
        do{
          printf("\nVuoi salvare i progressi della partita? [y/n]\n");
          scanf("%c%*c", &salva);
        }while(salva!='y' && salva!='n');
        if(salva=='y')
        {
          printf("\nInserisci il nome del file su cui salvare la mappa:\n");
          scanf("%s", filename);
          save_map(map, size, filename);
        }
        return;
      }
      else
        mossaprec = 1;
    }

    //muovo i nemici
    move_enemies(map, size);

    return movimento(map, size, xp, yp, xe, ye, mosse, mossaprec);
  }
}

void move_enemies(cella **map, int size)
{
  int i, j, k=0, xn[size/4], yn[size/4], move, temp, xp, yp, xe, ye;

  //trovo dove sono i nemici, il giocatore e l'uscita
  for(i=1;i<size-1;i++)
  {
    for(j=1;j<size-1;j++)
    {
      if(map[i][j].value==4) //nemici
      {
        xn[k] = i;
        yn[k] = j;
        k++;
      }
      else if(map[i][j].value==2) //giocatore
      {
        xp = i;
        yp = j;
      }
      else if(map[i][j].value==3) //uscita
      {
        xe = i;
        ye = j;
      }
    }
  }

  //muovo i nemici
  for(i=0;i<k;i++)
  {
    int x, y;
    x = xn[i];
    y = yn[i];

    move = rand()%4;
    if(move==0 && x!=1 && x!=xp && y!=yp && x!=xe && y!=ye) //non deve andare sopra il giocatore o sopra l'uscita
    {
      map[x][y].value = 0;
      x--;
    }
    else if(move==1 && y!=size-2 && x!=xp && y!=yp && x!=xe && y!=ye) //non deve andare sopra il giocatore o sopra l'uscita
    {
      map[x][y].value = 0;
      y++;
    }
    else if(move==2 && x!=size-2 && x!=xp && y!=yp && x!=xe && y!=ye) //non deve andare sopra il giocatore o sopra l'uscita
    {
      map[x][y].value = 0;
      x++;
    }
    else if(move==3 && y!=1 && x!=xp && y!=yp && x!=xe && y!=ye) //non deve andare sopra il giocatore o sopra l'uscita
    {
      map[x][y].value = 0;
      y--;
    }

    map[x][y].value = 4;
  }
}
