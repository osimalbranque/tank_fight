#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
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
  m->width = s->w;
  m->height = s->h;
  m->tiles = malloc(sizeof(Tile) * m->width * m->height);

  for (i = 0; i < s->h; i++) {

	for (j = 0; j < s->w; j++) {
		pixel_color = getpixel(s, i, j);
		switch (pixel_color) {
			case 0xf00: // Red
				m->tiles[i*s->w + j].object_kind = WOOD2;
			
				m->tiles[i*s->w + j].collision_settings.no_crossable = 1;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 1;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 1;
			break;

			case 0x000: // Black
				m->tiles[i*s->w + j].object_kind = HARDH;
				
				m->tiles[i*s->w + j].collision_settings.no_crossable = 1;
				m->tiles[i*s->w + j].collision_settings.stop_shoots = 1;
				m->tiles[i*s->w + j].collision_settings.is_destroyable = 1;
				m->tiles[i*s->w + j].collision_settings.no_crossable_light = 1;
			break;

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

Tank_Player *loadTankPlayers() {
	
	Tank_Player *tk_p;
	
	tk_p = malloc(sizeof(Tank_Player));
	tk_p->team = TEAM1;
	tk_p->kind = MEDIUM;
	tk_p->row = 1;
	tk_p->col = 3;
	tk_p->lifepoints = 100*(tk_p->kind+1);
	
	return tk_p;
	
}

/*-------------------------------- RENDERING -------------------------------- */

/* Initialisation de la bibliotheque SDL, ouverture d'une fenetre de taille 
   w*SIZE x h*SIZE
 */
SDL_Renderer *openWindow(int w,int h) {
  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    fprintf(stderr,"Initialization error:%s\n",SDL_GetError());
    exit(1);
  }
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
void paint(SDL_Renderer *s, map_t *m, Tank_Player *tk_p) {
	
  /* Fait un ecran noir */
  SDL_RenderClear(s);
  /* Definir ici le contenu graphique de la fenetre.
     A REMPLIR
   */
   
   paint_map(s, m);
   paint_tank(s, tk_p);
   

  /* Affiche le tout  */
  SDL_RenderPresent(s);
}

void paint_map(SDL_Renderer *s, map_t *m) {

   int i, j;
   SDL_Rect rect;
   rect.w = rect.h = SIZE;
   rect.x = 0;
   rect.y = 0;
   
   for(i = 0; i < m->height; i++) {
	   
	   for (j = 0; j < m->width; j++) {
		   
		   rect.x = j*SIZE;
		   rect.y = i*SIZE;
		   
		   SDL_RenderCopy(s, tile[ROAD], NULL, &rect); // Hides black background   
		   SDL_RenderCopy(s, tile[m->tiles[i*m->width + j].object_kind], NULL, &rect);
		   
	   }
	   
   }
	
}

void paint_tank(SDL_Renderer *s, Tank_Player *tk_p) {
	
   SDL_Rect rect;
   ObjectKind o_k;
   
   o_k = ALL-RIVER-1 + (tk_p->team+1)*(tk_p->kind+1);
   rect.w = rect.h = SIZE;
   rect.x = SIZE*tk_p->col;
   rect.y = SIZE*tk_p->row;
   
   SDL_RenderCopy(s, tile[o_k], NULL, &rect);
	
}

/*-------------------------------- RESOURCES DELLOCATION -------------------------------- */

void releaseMap(map_t *m) {

	free(m->tiles);
	free(m);
	
}

void releaseTank(Tank_Player *tk_p) {
	
	free(tk_p);
	
}
