#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
  int visited; // se la cella è stata visitata, questo valore è 1
  int value; //valore della cella
  int xbefore; //x della cella da cui provengo
  int ybefore; //y della cella da cui provengo
}cella;

cella **load_map(int *size, char filename[]); //carica la mappa da file, restituisce la mappa attraverso un doppio puntatore

void visualize_map(cella **map, int size, int px, int py, int win_size); //stampa a video la mappa

cella **inizializemap(cella **map, int size); //inizializza a 1 la mappa

int generate_random(cella **map, int size, int x, int y); //genera un numero random congruo con la posizione in cui mi trovo

cella **generate_map(cella **map, int size, int x, int y); // genera casualmente la mappa e la ritorna

void save_map(cella **map, int size, char filename[]); //salva la mappa in un file .txt di nome filename

void insert_player_exit_enemies(cella **map, int size); //sceglie casualmente la posizione del giocatore, dell'uscita dal labirinto e dei nemici

int torno_indietro(cella **map, int size); //restituisce 0 se non ci sono altre strade disponibili

void movimento(cella **map, int size, int xp, int yp, int xe, int ye, int mosse, int mossaprec); //chiede all'utente la mossa e muove il giocatore

void move_enemies(cella **map, int size); //trova i nemici nella mappa e li muove di una cella
