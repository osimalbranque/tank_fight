#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
#define MAP "data/map.bmp"

int main() {
  map_t *m;
  Tank_Player *tk_p;
  int finished=0;
  
  m = loadMap(MAP);
  tk_p = loadTankPlayers();
  
  SDL_Renderer *s = openWindow(512, 512);
  loadTiles(s);
  timerInit();
  while (!finished) {
    finished=getEvent(m);
    paint(s,m, tk_p);
    update(m);
    fprintf(stderr,".");
    timerWait();
  }
  
  releaseMap(m);
  releaseTank(tk_p);

  return 0;
}
