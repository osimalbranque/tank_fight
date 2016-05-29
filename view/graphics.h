#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#define SIZE 32

#include <SDL2/SDL.h>

void loadTiles(SDL_Renderer *s);

map_t *loadMap(char *filename);
ScrollWindow *loadScrollWindow(map_t *map);
Tank_Player *loadTankPlayers();

SDL_Renderer *openWindow(int w,int h);

void paint(SDL_Renderer *s, map_t *m, Tank_Player *tk_p);
void paint_map(SDL_Renderer *s, map_t *m);
void paint_tank(SDL_Renderer *s, map_t *m, Tank_Player *tk_p);

void releaseMap(map_t *m);
void releaseTank(Tank_Player *tk_p);


#endif // GRAPHICS_H_INCLUDED
