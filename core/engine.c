#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "timer.h"
#include "engine.h"
#include "tank_player.h"
#define SIZE 32

/* Capture les evenements clavier/fenetre */
/* Retourne 1 si il faut quitter le jeu, 0 sinon.*/
/* A REMPLIR */
int getEvent(map_t *m, Tank_Player *tk_p) {
  SDL_Event event;
  /* Ecoute les événements qui sont arrivés */
  while( SDL_PollEvent(&event) ){
    /* On a fermé la fenetre -> quitter le jeu */
    if (event.type==SDL_QUIT) return 1;
    /* On a appuyé sur une touche */
    if (event.type==SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE: printf("escape pressed\n"); return 1;
      case SDLK_LEFT: update_tank(m, tk_p, SDLK_LEFT); break;
      case SDLK_RIGHT: update_tank(m, tk_p, SDLK_RIGHT); break;
      case SDLK_UP: update_tank(m, tk_p, SDLK_UP); break;
      case SDLK_DOWN: update_tank(m, tk_p, SDLK_DOWN); break;
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

void update_tank(map_t *m, Tank_Player *tk_p, int move) {

	switch(move)
	{
	    Tile *neighbour_tile;
		case SDLK_LEFT:
		    neighbour_tile = adjacent_tile(m, tk_p->x, tk_p->y, SDLK_LEFT);
            if (tk_p->x > 0)
            {
                if (next - now > tk_p->move_frequency)
                {
                    if (!(tile_collision(neighbour_tile, tk_p) && neighbour_tile->collision_settings.no_crossable))
                        tk_p->x--;
                    now = next;
                }
            }
            //if (tk_p->col > 0 && !m->tiles[tk_p->row*m->width + tk_p->col-1].collision_settings.no_crossable)
		break;
		case SDLK_RIGHT:
		    neighbour_tile = adjacent_tile(m, tk_p->x, tk_p->y, SDLK_RIGHT);
		    if (tk_p->x < SIZE*m->width -1)
            {
                if (next - now > tk_p->move_frequency)
                {
                    if (!(tile_collision(neighbour_tile, tk_p) && neighbour_tile->collision_settings.no_crossable))
                        tk_p->x++;
                    now = next;
                }
            }
			//if (tk_p->col < m->width-1 && !m->tiles[tk_p->row*m->width + tk_p->col+1].collision_settings.no_crossable)
					//tk_p->col++;
		break;
		case SDLK_UP:
		    neighbour_tile = adjacent_tile(m, tk_p->x, tk_p->y, SDLK_UP);
            if (tk_p->y > 0)
            {
                if (next - now > tk_p->move_frequency)
                {
                    if (!(tile_collision(neighbour_tile, tk_p) && neighbour_tile->collision_settings.no_crossable))
                        tk_p->y--;
                    now = next;
                }
            }
            //if (tk_p->row > 0 && !m->tiles[(tk_p->row-1)*m->width + tk_p->col].collision_settings.no_crossable)
				//tk_p->row--;
		break;
		case SDLK_DOWN:
		    neighbour_tile = adjacent_tile(m, tk_p->x, tk_p->y, SDLK_DOWN);
            if (tk_p->y < SIZE*m->height - 1)
            {
                if (next - now > tk_p->move_frequency)
                {
                    if (!(tile_collision(neighbour_tile, tk_p) || neighbour_tile->collision_settings.no_crossable))
                        tk_p->y++;
                    now = next;
                }
            }
            //if (tk_p->row < m->height && !m->tiles[(tk_p->row+1)*m->width + tk_p->col].collision_settings.no_crossable)
				//tk_p->row++;
		break;
	}
}

Tile* adjacent_tile(map_t *m, int x, int y, int move) {

    int row = y / SIZE;
    int col = x / SIZE;

    printf("[Before translation] Row : %d | Col : %d\n", row, col);

    switch(move)
    {
        case SDLK_LEFT:
            col--;
		break;
		case SDLK_RIGHT:
            col++;
		break;
		case SDLK_UP:
            row--;
		break;
		case SDLK_DOWN:
            row++;
		break;
    }

    printf("[After translation] Row : %d | Col : %d\n", row, col);

    Tile *t = &m->tiles[row * m->width + col];

    printf("[Object Kind] %d\n", t->object_kind);
    return t;

}

int tile_collision(Tile* t, Tank_Player *tk_p) {

    return tk_p->x+1 >= t->col*(SIZE) && tk_p->x-1 <= SIZE*(t->col + 1)
           && tk_p->y+1 >= t->row*(SIZE) && tk_p->y-1 <= SIZE*(t->row + 1);

}
