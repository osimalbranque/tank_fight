#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "core/tank_player.h"
#include "core/engine.h"
#include "view/graphics.h"
#include "core/timer.h"
#define MAP "data/map2.bmp"

int main() {
  map_t *m;
  Tanks *tks;
  int finished=0;

  m = loadMap(MAP);
  tks = loadTankPlayers(m, 3);

  SDL_Renderer *s = openWindow(512, 512);
  loadTiles(s);

  while (!finished) {
    timerInit();
    printf("timer\n");
    finished=getEvent(m, tks, 0);
    printf("event\n");
    paint(s,m, tks);
    fprintf(stderr,".");
    timerWait();
  }

  releaseMap(m);
  releaseTank(tks);

  return 0;
}
