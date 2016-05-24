#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "core/tank_player.h"
#include "core/engine.h"
#include "view/graphics.h"
#include "core/timer.h"
#define MAP "data/map.bmp"

int main() {
  map_t *m;
  Tank_Player *tk_p;
  int finished=0;

  m = loadMap(MAP);
  tk_p = loadTankPlayers();

  SDL_Renderer *s = openWindow(512, 512);
  loadTiles(s);
  while (!finished) {
    timerInit();
    finished=getEvent(m, tk_p);
    paint(s,m, tk_p);
    update(m);
    //fprintf(stderr,".");
    timerWait();
  }

  releaseMap(m);
  releaseTank(tk_p);

  return 0;
}
