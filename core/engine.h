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

    int rel_width; // Width of window
    int rel_height; // Height of window
    int abs_row; // Absolute row of window
    int abs_col; // Absolute col of window

} ScrollWindow;

typedef struct {
   Tile *tiles;
   int world_width; // In rows
   int world_height; // In cols

   ScrollWindow *scroll_window;
} map_t;

int getEvent(map_t *m, Tanks *tks, int controlled_player);
void update_tank(map_t *m, Tanks *tks, int controlled_player, int move);
void rotate_tank(Tank_Player *tk_p, double angle_delta);

void init_tile(Tile* t);

Tile* adjacent_tile(map_t *m, Tanks *tks, int controlled_player, int move);
int tile_collision(map_t *m, Tile* t, Tanks *tks, int controlled_player);
void make_move(map_t *m, Tanks *tks, int controlled_player, int move);

#endif // ENGINE_H_INCLUDED
