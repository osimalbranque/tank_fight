#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#define SIZE 32

#include <SDL2/SDL.h>

void loadTiles(SDL_Renderer *s);

map_t *loadMap(char *filename);
ScrollWindow *loadScrollWindow(map_t *map);
Tanks *loadTankPlayers(map_t *m, int players_nb);

SDL_Renderer *openWindow(int w,int h);

void paint(SDL_Renderer *s, map_t *m, Tanks *tks);
void paint_map(SDL_Renderer *s, map_t *m);
void paint_tank(SDL_Renderer *s, map_t *m, Tanks *tks);

void releaseMap(map_t *m);
void releaseTank(Tanks *tks);


#endif // GRAPHICS_H_INCLUDED
