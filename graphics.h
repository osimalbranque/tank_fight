#define SIZE 32

void loadTiles(SDL_Renderer *s);

map_t *loadMap(char *filename);
Tank_Player *loadTankPlayers();

SDL_Renderer *openWindow(int w,int h);

void paint(SDL_Renderer *s, map_t *m, Tank_Player *tk_p);
void paint_map(SDL_Renderer *s, map_t *m);
void paint_tank(SDL_Renderer *s, Tank_Player *tk_p);

void releaseMap(map_t *m);
void releaseTank(Tank_Player *tk_p);
