#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "../core/engine.h"
#include "graphics.h"
#include "../core/timer.h"
/* Toutes les tuiles du jeu */
SDL_Texture *tile[ALL];
/* Le nom de leur fichier.
   Doit etre avec le meme ordre que l'enum dans le .h
*/
const char *tilenames[]={
  "data/grass.bmp",
  "data/hardhouse.bmp",
  "data/house.bmp",
  "data/house2.bmp",
  "data/wood.bmp",
  "data/wood2.bmp",
  "data/river.bmp",
  "data/team1_small.bmp",
  "data/team1_medium.bmp",
  "data/team1_big.bmp",
  "data/team2_small.bmp",
  "data/team2_medium.bmp",
  "data/team2_big.bmp"
};

/*-------------------------------- OPERATIONS ON PIXELS -------------------------------- */

/* Lit un pixel d'une carte. A utiliser dans loadMap.
   Retourne la couleur RGB du pixel aux coordonnées x,y.
*/
int getpixel(SDL_Surface *surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 r,g,b,*p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  Uint32 pixel;
  switch(bpp) {
  case 1: pixel= *p; break;
  case 2: pixel= *(Uint16 *)p; break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) pixel= p[0] << 16 | p[1] << 8 | p[2];
    else pixel= p[0] | p[1] << 8 | p[2] << 16;
    break;
  case 4: pixel= *(Uint32 *)p; break;
  default: pixel= 0;
  }
  SDL_GetRGB(pixel, surface->format, &r, &g, &b);
  r=r>>4;
  g=g>>4;
  b=b>>4;
  return (r<<8)+(g<<4)+b;
}


/*-------------------------------- RESOURCES LOADING -------------------------------- */

/* Charge toutes les tuiles du jeu */
void loadTiles(SDL_Renderer *s) {
  int i;
  SDL_SetRenderDrawColor(s, 0, 0, 0, 0);
  for (i=0; i<ALL; i++)  {
    SDL_Surface *loadedImage=SDL_LoadBMP(tilenames[i]);
    if (loadedImage !=NULL) {
      Uint32 colorkey = SDL_MapRGB(loadedImage->format,0xff,0xff,0xff);
      SDL_SetColorKey(loadedImage,SDL_TRUE,colorkey);
      tile[i]=SDL_CreateTextureFromSurface(s, loadedImage );
      SDL_FreeSurface(loadedImage);
    } else fprintf(stderr,"Missing file %s:%s\n",tilenames[i],SDL_GetError());
  }
}

/* Lecture d'une mini carte, comme MAP
   A REMPLIR
*/
map_t *loadMap(char *filename) {

  int i, j;
  int pixel_color;
  SDL_Surface *s=SDL_LoadBMP(filename); // Reads map image
  map_t *m; // The future map
  m = malloc(sizeof(map_t));

  m->world_width = s->w;
  m->world_height = s->h;

  m->tiles = malloc(sizeof(Tile) * m->world_width * m->world_height);
  printf("%d\n", m->world_width);
  m->scroll_window = loadScrollWindow(m);

  for (i = 0; i < s->h; i++) {

	for (j = 0; j < s->w; j++) {

		pixel_color = getpixel(s, i, j);
		m->tiles[i*s->w + j].row = i;
        m->tiles[i*s->w + j].col = j;

		switch (pixel_color) {

            case 0xFFF: // White
				m->tiles[i*s->w + j].object_kind = ROAD;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 0;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 0;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 0;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 0;
			break;

			case 0x00F: // Blue
				m->tiles[i*s->w + j].object_kind = RIVER;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 1;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 0;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 0;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 1;
			break;

			case 0x000: // Black
				m->tiles[i*s->w + j].object_kind = HARDH;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 1;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 1;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 1;
			break;

			case 0xf00: // Red
				m->tiles[i*s->w + j].object_kind = SOFTH;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 1;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 1;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 1;

			break;

			case 0x0F0: // Green
				m->tiles[i*s->w + j].object_kind = WOOD;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 0;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 0;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 0;
			break;

			default: // No color
				m->tiles[i*s->w + j].object_kind = ROAD;

				m->tiles[i*s->w + j].collision_settings.no_crossable = 0;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 0;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 0;
			break;
		}
	}

  }
  return m;
}

Tanks *loadTankPlayers(map_t *m, int players_nb) {

	//Tanks *tks = malloc(sizeof(int) + players_nb*sizeof(Tank_Player));
	Tanks *tks = malloc(sizeof(Tanks));

    tks->players_nb = players_nb;
	tks->tank_players = malloc(players_nb*sizeof(Tank_Player*));

	tks->tank_players[0] = malloc(sizeof(Tank_Player));

	tks->tank_players[0]->team = TEAM1;
	tks->tank_players[0]->kind = SMALL;
	tks->tank_players[0]->move_frequency = SMALL*(tks->tank_players[0]->kind+1); // 10 for small, 20 for medium, 30 for big...
	tks->tank_players[0]->rel_row = 1;
	tks->tank_players[0]->rel_col = 3;
	tks->tank_players[0]->abs_col = m->scroll_window->abs_col + tks->tank_players[0]->rel_col;
	tks->tank_players[0]->abs_row = m->scroll_window->abs_row + tks->tank_players[0]->rel_row;
	tks->tank_players[0]->lifepoints = 100*(tks->tank_players[0]->kind+1);
	tks->tank_players[0]->orientation = 0;

    tks->tank_players[1] = malloc(sizeof(Tank_Player));

	tks->tank_players[1]->team = TEAM1;
	tks->tank_players[1]->kind = SMALL;
	tks->tank_players[1]->move_frequency = SMALL*(tks->tank_players[1]->kind+1); // 10 for small, 20 for medium, 30 for big...
	tks->tank_players[1]->abs_col = 11;
	tks->tank_players[1]->abs_row = 0;
	tks->tank_players[1]->rel_row = tks->tank_players[1]->abs_row - m->scroll_window->abs_row;
	tks->tank_players[1]->rel_col = tks->tank_players[1]->abs_col - m->scroll_window->abs_col;
	tks->tank_players[1]->lifepoints = 100*(tks->tank_players[1]->kind+1);
	tks->tank_players[1]->orientation = 0;

    tks->tank_players[2] = malloc(sizeof(Tank_Player));

	tks->tank_players[2]->team = TEAM1;
	tks->tank_players[2]->kind = SMALL;
	tks->tank_players[2]->move_frequency = SMALL*(tks->tank_players[2]->kind+1); // 10 for small, 20 for medium, 30 for big...
	tks->tank_players[2]->abs_col = 2;
	tks->tank_players[2]->abs_row = 0;
	tks->tank_players[2]->rel_row = tks->tank_players[2]->abs_row - m->scroll_window->abs_row;
	tks->tank_players[2]->rel_col = tks->tank_players[2]->abs_col - m->scroll_window->abs_col;
	tks->tank_players[2]->lifepoints = 100*(tks->tank_players[2]->kind+1);
	tks->tank_players[2]->orientation = 0;

	return tks;

}

ScrollWindow *loadScrollWindow(map_t *m) {

    ScrollWindow *s_w;
    s_w = malloc(sizeof(ScrollWindow));

    s_w->rel_width = 16;
    s_w->rel_height = 16;

    s_w->abs_col = 2;
    s_w->abs_row = 0;

    return s_w;

}

/*-------------------------------- RENDERING -------------------------------- */

/* Initialisation de la bibliotheque SDL, ouverture d'une fenetre de taille
   w*SIZE x h*SIZE
 */
SDL_Renderer *openWindow(int w,int h) {
    printf("debut\n");
  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    fprintf(stderr,"Initialization error:%s\n",SDL_GetError());
    printf("foin\n");
    exit(1);
  }
    printf("fin\n");
  atexit(SDL_Quit);
  SDL_Window *sdlWindow;
  SDL_Renderer *sdlRenderer;
  if (SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &sdlWindow, &sdlRenderer)) {
    fprintf(stderr,"Couldn't create window and renderer: %s",SDL_GetError());
    exit(1);
  }
  SDL_RenderSetLogicalSize(sdlRenderer, w, h);
  return sdlRenderer;
}

/* Redessine la carte, les joueurs, les effets, ...
   A REMPLIR
*/
void paint(SDL_Renderer *s, map_t *m, Tanks *tks) {

  /* Fait un ecran noir */
  SDL_RenderClear(s);
  printf("paint render clear\n");

   paint_map(s, m);
   paint_tank(s, m, tks);


  /* Affiche le tout  */
  SDL_RenderPresent(s);
}

void paint_map(SDL_Renderer *s, map_t *m) {

   int i, j;
   int min_row, max_row, min_col, max_col;
   int tile_id;

   min_col = m->scroll_window->abs_col;
   max_col = m->scroll_window->abs_col + m->scroll_window->rel_width;

   min_row = m->scroll_window->abs_row;
   max_row = m->scroll_window->abs_row + m->scroll_window->rel_height;

   SDL_Rect rect;
   rect.w = rect.h = SIZE;
   rect.x = 0;
   rect.y = 0;

   for (i = min_row; i < max_row; i++)
   {
       for (j = min_col; j < max_col; j++)
       {
           rect.x = (j-min_col)*SIZE;
           rect.y = (i-min_row)*SIZE;

           if (i < 0 || i >= m->world_height || j < 0 || j >= m->world_width)
            tile_id = ROAD;
           else
            //tile_id = m->tiles[(min_row+i)*m->world_width + j+min_col].object_kind;
            tile_id = m->tiles[(i)*m->world_width + j].object_kind;

           SDL_RenderCopy(s, tile[ROAD], NULL, &rect);
           SDL_RenderCopy(s, tile[tile_id], NULL, &rect);
       }
   }

   /*for(i = 0; i < m->height; i++) {

	   for (j = 0; j < m->width; j++) {

		   rect.x = j*SIZE;
		   rect.y = i*SIZE;

		   SDL_RenderCopy(s, tile[ROAD], NULL, &rect); // Hides black background
           SDL_RenderCopy(s, tile[m->tiles[i*m->width + j].object_kind], NULL, &rect);

	   }

   }*/

}

void paint_tank(SDL_Renderer *s, map_t *m, Tanks *tks) {

   SDL_Rect rect;
   ObjectKind o_k;
   int i;

   for (i = 0; i < tks->players_nb; i++) {

       o_k = ALL-RIVER-1 + (tks->tank_players[i]->team+1)*(tks->tank_players[i]->kind+1);
       rect.w = rect.h = SIZE;
       rect.x = tks->tank_players[i]->rel_col*SIZE;
       rect.y = tks->tank_players[i]->rel_row*SIZE;

       printf("%d %d\n", tks->tank_players[i]->rel_col, tks->tank_players[i]->rel_row);

       SDL_Point center = {SIZE/2, SIZE/2};

       if (tks->tank_players[i]->rel_row >= 0 && tks->tank_players[i]->rel_row <= m->scroll_window->rel_height &&
           tks->tank_players[i]->rel_col >= 0 && tks->tank_players[i]->rel_col <= m->scroll_window->rel_width)
       {
            SDL_RenderCopyEx(s, tile[o_k], NULL, &rect, tks->tank_players[i]->orientation, &center, SDL_FLIP_NONE);

       if (m->tiles[tks->tank_players[i]->rel_row*m->world_width + tks->tank_players[i]->rel_col].object_kind == WOOD
           || m->tiles[tks->tank_players[i]->rel_row*m->world_width + tks->tank_players[i]->rel_col].object_kind == WOOD2)
            SDL_RenderCopy(s, tile[m->tiles[tks->tank_players[i]->rel_row*m->world_width + tks->tank_players[i]->rel_col].object_kind], NULL, &rect);
       }

   }

}

/*-------------------------------- RESOURCES DEALLOCATION -------------------------------- */

void releaseMap(map_t *m) {

	free(m->tiles);
	free(m->scroll_window);
	free(m);

}

void releaseTank(Tanks *tks) {

    int i = 0;
    for (i = 0; i < tks->players_nb; i++)
        free(tks->tank_players[i]);

	free(tks->tank_players);

}
