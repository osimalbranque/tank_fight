typedef enum
{
    ROAD=0,
    HARDH,
    SOFTH,
    SOFTH2,
    WOOD,
    WOOD2,
    RIVER,
    PLAYER1,
    PLAYER2,
    ALL
} ObjectKind;

typedef enum
{
    LIFEPOINT
} BonusKind;

typedef struct {

   char no_crossable;
   char stop_shoots;
   char is_destroyable;
   char no_crossable_light;

} CollisionSettings;

typedef struct {
   ObjectKind object_kind;
   BonusKind bonus_kind;
   CollisionSettings collision_settings;
} Tile;


void init_tile(Tile* t);

typedef struct {
   Tile *tiles;
   int width;
   int height;
} map_t;

int getEvent(map_t *m);
void update(map_t *m);
