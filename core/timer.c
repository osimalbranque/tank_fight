#include <SDL2/SDL.h>
#include "timer.h"
#define TICK_INTERVAL 10

void timerInit() {
  next= SDL_GetTicks() + TICK_INTERVAL;
}

void timerWait() {
  //Uint32 now;
  now = SDL_GetTicks();
  if(next>now) SDL_Delay(next-now);
  next+=TICK_INTERVAL;
}
