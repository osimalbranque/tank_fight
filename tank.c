#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "engine.h"
#include "graphics.h"
#include "timer.h"
#define MAP "data/map.bmp"

int main() {
  map_t *m;
  int finished=0;
  m=loadMap(MAP);
  SDL_Renderer *s = openWindow(512, 512);
  loadTiles(s);
  timerInit();
  while (!finished) {
    finished=getEvent(m);
    paint(s,m);
    update(m);
    fprintf(stderr,".");
    timerWait();
  }
  
  releaseMap(m);

  return 0;
}
