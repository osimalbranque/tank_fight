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
int getEvent(map_t *m, Tanks *tks, int controlled_player) {
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

      case SDLK_a: rotate_tank(tks->tank_players[controlled_player], -ANGLE_STEP); break;
      case SDLK_w: rotate_tank(tks->tank_players[controlled_player], ANGLE_STEP); break;
      case SDLK_ESCAPE: printf("escape pressed\n"); return 1;
      case SDLK_LEFT: update_tank(m, tks, 0, SDLK_LEFT); break;
      case SDLK_RIGHT: update_tank(m, tks, 0, SDLK_RIGHT); break;
      case SDLK_UP: update_tank(m, tks, 0, SDLK_UP); break;
      case SDLK_DOWN: update_tank(m, tks, 0, SDLK_DOWN); break;
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

void rotate_tank(Tank_Player *tk_p, double angle_delta) {

    tk_p->orientation += angle_delta;

}

void update_tank(map_t *m, Tanks *tks, int controlled_player, int move) {

	switch(move)
	{
	    Tile *neighbour_tile;
		case SDLK_LEFT:
		    neighbour_tile = adjacent_tile(m, tks, controlled_player, SDLK_LEFT);
            if (tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col > 0)
            {
                    if (!neighbour_tile->collision_settings.no_crossable)
                            make_move(m, tks, controlled_player, SDLK_LEFT);
            }
            //if (tks->tank_players[controlled_player]->col > 0 && !m->tiles[tks->tank_players[controlled_player]->row*m->width + tks->tank_players[controlled_player]->col-1].collision_settings.no_crossable)
		break;
		case SDLK_RIGHT:
		    neighbour_tile = adjacent_tile(m, tks, controlled_player, SDLK_RIGHT);
		    if (tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col < m->world_width)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                        make_move(m, tks, controlled_player, SDLK_RIGHT);
            }
			//if (tks->tank_players[controlled_player]->col < m->width-1 && !m->tiles[tks->tank_players[controlled_player]->row*m->width + tks->tank_players[controlled_player]->col+1].collision_settings.no_crossable)
					//tks->tank_players[controlled_player]->col++;
		break;
		case SDLK_UP:
		    neighbour_tile = adjacent_tile(m, tks, controlled_player, SDLK_UP);
            if (tks->tank_players[controlled_player]->rel_row + m->scroll_window->abs_row > 0)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                        make_move(m, tks, controlled_player, SDLK_UP);
            }
            //if (tks->tank_players[controlled_player]->row > 0 && !m->tiles[(tks->tank_players[controlled_player]->row-1)*m->width + tks->tank_players[controlled_player]->col].collision_settings.no_crossable)
				//tks->tank_players[controlled_player]->row--;
		break;
		case SDLK_DOWN:
		    neighbour_tile = adjacent_tile(m, tks, controlled_player, SDLK_DOWN);
            if (tks->tank_players[controlled_player]->rel_row + m->scroll_window->abs_row < m->world_height-1)
            {
                if (!neighbour_tile->collision_settings.no_crossable)
                            make_move(m, tks, controlled_player, SDLK_DOWN);
            }
            //if (tks->tank_players[controlled_player]->row < m->height && !m->tiles[(tks->tank_players[controlled_player]->row+1)*m->width + tks->tank_players[controlled_player]->col].collision_settings.no_crossable)
				//tks->tank_players[controlled_player]->row++;
		break;
	}
}

Tile* adjacent_tile(map_t *m, Tanks *tks, int controlled_player, int move) {

    int row = tks->tank_players[controlled_player]->rel_row + m->scroll_window->abs_row;
    int col = tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col;

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

    Tile *t = &m->tiles[row * m->world_width + col];

    return t;

}

int tile_collision(map_t *m, Tile* t, Tanks *tks, int controlled_player) {

    if((tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col >= t->col*SIZE + SIZE)      // too much at the right

    || (tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col + SIZE <= t->col*SIZE) // too much at the left

    || (tks->tank_players[controlled_player]->rel_row + m->scroll_window->abs_row >= t->row*SIZE + SIZE) // too much at the bottom

    || (tks->tank_players[controlled_player]->rel_col + m->scroll_window->abs_col + SIZE <= t->col*SIZE))  // too much at the top

          return 0;

    return 1;

}

void make_move(map_t *m, Tanks *tks, int controlled_player, int move)
{
    int i;
    switch(move)
    {
        case SDLK_LEFT:
            //if (next - now > tks->tank_players[controlled_player]->move_frequency)

                for (i = 0; i < tks->players_nb; i++)
                {
                    if (i != controlled_player)
                        tks->tank_players[i]->rel_col = tks->tank_players[i]->abs_col - m->scroll_window->abs_col;
                    else
                    {
                        if (m->scroll_window->abs_col > 0) {
                        m->scroll_window->abs_col--;
                         //tk_p->rel_col--;
                        }
                        else {

                            if (tks->tank_players[controlled_player]->rel_col > 0)
                                tks->tank_players[controlled_player]->rel_col--;
                        }
                    }

                }

                //if (tk_p->rel_col < 0) {
                    //tk_p->rel_col = m->scroll_window->rel_width-1;

                //}
            //now = next;
        break;
        case SDLK_RIGHT:
            //if (next - now > tk_p->move_frequency)

                for (i = 0; i < tks->players_nb; i++)
                {
                    if (i != controlled_player)
                        tks->tank_players[i]->rel_col = tks->tank_players[i]->abs_col - m->scroll_window->abs_col;
                    else
                    {
                        if (m->scroll_window->abs_col+m->scroll_window->rel_width <= m->world_width) {
                     m->scroll_window->abs_col++;
                     //tk_p->rel_col++;
                        }
                        else {
                            if (tks->tank_players[controlled_player]->rel_col+m->scroll_window->abs_col < m->world_width) {
                                tks->tank_players[controlled_player]->rel_col++;
                            }
                        }
                    }
                }



                //if (tk_p->rel_col > m->scroll_window->rel_width) {

                  //   tk_p->rel_col--;
                //}

            //now = next;
        break;
        case SDLK_UP:

            for (i = 0; i < tks->players_nb; i++)
                {
                    if (i != controlled_player)
                        tks->tank_players[i]->rel_col = tks->tank_players[i]->abs_col - m->scroll_window->abs_col;
                    else
                    {
                        if (m->scroll_window->abs_row > 0) {
                        m->scroll_window->abs_row--;
                        //tk_p->rel_row--;
                        }
                    else {

                        if (tks->tank_players[controlled_player]->rel_row > 0) {
                            tks->tank_players[controlled_player]->rel_row--;
                        }

                    }
                    }

                }
            //if (next - now > tk_p->move_frequency)

                //if (tk_p->rel_row < 0) {
                  //  tk_p->rel_row = m->scroll_window->rel_height-1;
                //}
            //now = next;
        break;
        case SDLK_DOWN:
        for (i = 0; i < tks->players_nb; i++)
        {
                    if (i != controlled_player)
                        tks->tank_players[i]->rel_col = tks->tank_players[i]->abs_col - m->scroll_window->abs_col;
                    else
                    {
                        if (m->scroll_window->abs_row+m->scroll_window->rel_height < m->world_height) {
                    m->scroll_window->abs_row++;
                    //tk_p->rel_row++;
                    }
                    else {
                        if (tks->tank_players[controlled_player]->rel_row+m->scroll_window->abs_row < m->world_height) {
                            tks->tank_players[controlled_player]->rel_row++;
                        }
                    }
                    }
        }
            //if (next - now > tk_p->move_frequency)

                //if (tk_p->rel_row > m->scroll_window->rel_height) {
                    //tk_p->rel_row--;
                //}
            //now = next;
        break;
    }

}
