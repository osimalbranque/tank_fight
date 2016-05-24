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
  int previous_move;

  /* Ecoute les événements qui sont arrivés */
  while( SDL_PollEvent(&event) ){
    /* On a fermé la fenetre -> quitter le jeu */
    if (event.type==SDL_QUIT) return 1;
    /* On a appuyé sur une touche */
    if (event.type==SDL_KEYDOWN) {
            if (event.key.keysym.sym != previous_move)
                previous_move = event.key.keysym.sym;
      switch (event.key.keysym.sym) {

      case SDLK_a: rotate_tank(tk_p, -ANGLE_STEP); break;
      case SDLK_w: rotate_tank(tk_p, ANGLE_STEP); break;
      case SDLK_ESCAPE: printf("escape pressed\n"); return 1;
      case SDLK_LEFT: update_tank(m, tk_p, previous_move, SDLK_LEFT); break;
      case SDLK_RIGHT: update_tank(m, tk_p, previous_move, SDLK_RIGHT); break;
      case SDLK_UP: update_tank(m, tk_p, previous_move, SDLK_UP); break;
      case SDLK_DOWN: update_tank(m, tk_p, previous_move, SDLK_DOWN); break;
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

void rotate_tank(Tank_Player *tk_p, double angle_delta) {

    tk_p->orientation += angle_delta;

}

void update_tank(map_t *m, Tank_Player *tk_p, int previous_move, int move) {

	switch(move)
	{
	    Tile *neighbour_tile;
		case SDLK_LEFT:
		    neighbour_tile = adjacent_tile(m, tk_p, SDLK_LEFT);
            if (tk_p->x > 0)
            {
                    if (!neighbour_tile->collision_settings.no_crossable)
                        //if (next - now > tk_p->move_frequency)
                            make_move(tk_p, previous_move, SDLK_LEFT);
                        //now = next;
            }
            //if (tk_p->col > 0 && !m->tiles[tk_p->row*m->width + tk_p->col-1].collision_settings.no_crossable)
		break;
		case SDLK_RIGHT:
		    neighbour_tile = adjacent_tile(m, tk_p, SDLK_RIGHT);
		    if (tk_p->x < SIZE*m->width -1)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                        //if (next - now > tk_p->move_frequency)
                        make_move(tk_p, previous_move, SDLK_RIGHT);
                        //now = next;
            }
			//if (tk_p->col < m->width-1 && !m->tiles[tk_p->row*m->width + tk_p->col+1].collision_settings.no_crossable)
					//tk_p->col++;
		break;
		case SDLK_UP:
		    neighbour_tile = adjacent_tile(m, tk_p, SDLK_UP);
            if (tk_p->y > 0)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                        //if (next - now > tk_p->move_frequency)
                        make_move(tk_p, previous_move, SDLK_UP);
                        //now = next;
            }
            //if (tk_p->row > 0 && !m->tiles[(tk_p->row-1)*m->width + tk_p->col].collision_settings.no_crossable)
				//tk_p->row--;
		break;
		case SDLK_DOWN:
		    neighbour_tile = adjacent_tile(m, tk_p, SDLK_DOWN);
            if (tk_p->y < SIZE*m->height - 1)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                        //if (next - now > tk_p->move_frequency)
                            make_move(tk_p, previous_move, SDLK_DOWN);
                        //now = next;
            }
            //if (tk_p->row < m->height && !m->tiles[(tk_p->row+1)*m->width + tk_p->col].collision_settings.no_crossable)
				//tk_p->row++;
		break;
	}
}

Tile* adjacent_tile(map_t *m, Tank_Player *tk_p, int move) {

    int row = tk_p->row;
    int col = tk_p->col;

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

    Tile *t = &m->tiles[row * m->width + col];

    return t;

}

int tile_collision(Tile* t, Tank_Player *tk_p) {

    if((tk_p->x >= t->col*SIZE + SIZE)      // trop à droite

    || (tk_p->x + SIZE <= t->col*SIZE) // trop à gauche

    || (tk_p->y >= t->row*SIZE + SIZE) // trop en bas

    || (tk_p->y + SIZE <= t->col*SIZE))  // trop en haut

          return 0;

    return 1;

}

void make_move(Tank_Player* tk_p, int previous_move, int move)
{
    switch(move)
    {
        case SDLK_LEFT:
            //if (next - now > tk_p->move_frequency)
                tk_p->x -= SIZE;
                tk_p->col--;
            //now = next;
        break;
        case SDLK_RIGHT:
            //if (next - now > tk_p->move_frequency)
                tk_p->x += SIZE;
                tk_p->col++;
            //now = next;
        break;
        case SDLK_UP:
            //if (next - now > tk_p->move_frequency)
                tk_p->y -= SIZE;
                tk_p->row--;
            //now = next;
        break;
        case SDLK_DOWN:
            //if (next - now > tk_p->move_frequency)
                tk_p->y += SIZE;
                tk_p->row++;
            //now = next;
        break;
    }

}
