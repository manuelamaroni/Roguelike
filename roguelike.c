#include"rogue.h"

int main()
{
  char scelta, filename[20], scelta2;
  int size, i, j, xp, yp, xe, ye;
  FILE *f;
  cella **map;
  srand(time(NULL));

  printf("\n-COME SI GIOCA-\n\n");
  printf("Lo scopo del gioco e' raggiungere l'uscita del labirinto evitando i nemici. Se il giocatore occupa la stessa cella di un nemico, verra' ucciso. Il giocatore NON puo' passare attraverso i muri, i nemici si'. I nemici si muovono casualmente a ogni turno e scavano i muri quando ci passano attraverso, creando altri passaggi. Il labirinto e' centrato sul giocatore, non ti sara' quindi possibile vedere l'intero labirinto. \n");
  printf("All'inizio del gioco, verra' chiesto all'utente se vuole caricare la mappa da file o se preferisce generarla casualmente, il file deve essere salvato nella stessa cartella del programma. Se si decide di generare casualmente la mappa, sara' necessario inserire la sua dimensione, che dovra' dispari e maggiore di 9. Verra' successivamente chiesto se si vuole salvare la mappa generata su file. Se non presente, il file verra' creato nella stessa cartella in cui si trova il programma. \n");
  printf("In caso si decida di abbandonare la partita, il programma chiedera' se si vogliono salvare i progressi della partita e, in caso affermativo, bisognera' inserire il nome del file su cui salvarli. Questo file puo' essere lo stesso su cui si era deciso di salvare la mappa iniziale oppure un altro.\n");
  printf("Si puo' uscire dal programma in qualsiasi momento, senza possibilita' di salvare i progressi, premendo ctrl+c.\n");

  do{
    printf("\nInserire 'c' se si vuole caricare la mappa da file, inserire 'g' se si vuole generare casualmente la mappa:\n");
    scanf("%c%*c", &scelta);
  }while(scelta!='c' && scelta!='g');

  if(scelta=='c')
  {
    printf("Inserire il nome del file contenente la mappa:\n");
    scanf("%s%*c", filename);

    f=fopen(filename, "r");

    if(f!=NULL)
    {
      fscanf(f, "%d", &size);
      map = load_map(&size, filename);
    }
    else
      printf("Errore in apertura del file %s", filename);

    fclose(f);
  }
  else if(scelta=='g')
  {
    do{
      printf("Inserire la dimensione della mappa (deve essere dispari e maggiore di 9):\n");
      scanf("%d%*c", &size);
    }while(size%2==0 || size<=9);


    map = inizializemap(map, size);

    map = generate_map(map, size, 1, 1);

    insert_player_exit_enemies(map, size);

    do{
      printf("Vuoi salvare la mappa su un file?[y/n]\n");
      scanf("%c%*c", &scelta2);
    }while(scelta2!='y' && scelta2!='n');

    if(scelta2=='y')
    {
      printf("Inserire il nome del file in cui salvare la mappa:\n");
      scanf("%s%*c", filename);
      save_map(map, size, filename);
    }
  }

  for(i=0;i<size;i++)
  {
    for(j=0;j<size;j++)
    {
      if(map[i][j].value==2) //trovo la posizione del giocatore
      {
        xp = i;
        yp = j;
      }
      else if(map[i][j].value==3) //trovo la posizione dell'uscita
      {
        xe = i;
        ye = j;
      }
    }
  }

  printf("\nLegenda:\nP -> giocatore\nN -> nemico\nE -> uscita\n# -> muro\n  -> spazio percorribile\n");
  printf("\nPer muoversi inserire i seguenti comandi:\nw -> su\ns -> giu\nd -> destra\na -> sinistra\nq -> abbandona\n\nPremere invio per confermare la mossa. Potrebbe essere necessario inserire due volte il comando prima di premere invio\n");

  movimento(map, size, xp, yp, xe, ye, 0, 1);

  return 0;
}
