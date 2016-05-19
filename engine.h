typedef enum
{
    ROAD=0,
    HARDH,
    SOFTH,
    SOFTH2,
    WOOD,
    WOOD2,
    RIVER,
    TEAM1_SMALL,
    TEAM1_MEDIUM,
    TEAM1_BIG,
    TEAM2_SMALL,
    TEAM2_MEDIUM,
    TEAM2_BIG,
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

typedef struct {
   Tile *tiles;
   int width;
   int height;
} map_t;

typedef enum {
	
	SMALL=0,
	MEDIUM,
	BIG
	
} TankKind;

typedef enum {
	TEAM1=0,
	TEAM2
} TankTeam;

typedef struct {
	
	TankTeam team;
	TankKind kind;
	int row;
	int col;
	int lifepoints;
	
} Tank_Player;

int getEvent(map_t *m);
void update(map_t *m);

void init_tile(Tile* t);
