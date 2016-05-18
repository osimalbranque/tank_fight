#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#define SIZE 32

/* Capture les evenements clavier/fenetre */
/* Retourne 1 si il faut quitter le jeu, 0 sinon.*/
/* A REMPLIR */
int getEvent(map_t *m) {
  SDL_Event event;
  /* Ecoute les événements qui sont arrivés */
  while( SDL_PollEvent(&event) ){
    /* On a fermé la fenetre -> quitter le jeu */
    if (event.type==SDL_QUIT) return 1;
    /* On a appuyé sur une touche */
    if (event.type==SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE: printf("escape pressed\n"); return 1;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
      case SDLK_UP: break;
      case SDLK_DOWN: printf("down arrow pressed\n"); break;
      case SDLK_SPACE: printf("space bar pressed\n"); break;
	/* Par exemple, les touches de direction du clavier. A remplir */
	/* A REMPLIR */
      default: ;
      }
      /* On a relaché une touche */
    } else if (event.type==SDL_KEYUP) {
    }
  }
  return 0;
} 

void update(map_t *m) {  
}
