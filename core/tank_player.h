#ifndef TANK_PLAYER_H_INCLUDED
#define TANK_PLAYER_H_INCLUDED

typedef enum {

	SMALL=0,
	MEDIUM,
	BIG

} TankKind;

typedef enum {

    SLOW=5,
    AVERAGE=10,
    FAST=20

} TankSpeed;

typedef enum {
	TEAM1=0,
	TEAM2
} TankTeam;

typedef struct {

	TankTeam team;
	TankKind kind;
	TankSpeed move_frequency; // In millis

	int rel_row;
	int rel_col;

	int lifepoints;

	double orientation;

} Tank_Player;


#endif // TANK_PLAYER_H_INCLUDED
