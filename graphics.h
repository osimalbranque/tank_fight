#define SIZE 32

void loadTiles(SDL_Renderer *s);
map_t *loadMap(char *filename);
SDL_Renderer *openWindow(int w,int h);
void paint(SDL_Renderer *s,map_t *m);
void releaseMap(map_t *m);
