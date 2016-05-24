#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "tank_player.h"

#define ANGLE_STEP 10

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
   int row;
   int col;
} Tile;

typedef struct {
   Tile *tiles;
   int width;
   int height;
} map_t;

int getEvent(map_t *m, Tank_Player *tk_p);
void update(map_t *m);
void update_tank(map_t *m, Tank_Player *tk_p, int previous_move, int move);
void rotate_tank(Tank_Player *tk_p, double angle_delta);

void init_tile(Tile* t);

Tile* adjacent_tile(map_t *m, Tank_Player *tk_p, int move);
int tile_collision(Tile* t, Tank_Player *tk_p);
void make_move(Tank_Player* tk_p, int previous_move, int move);

#endif // ENGINE_H_INCLUDED
