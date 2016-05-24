#ifndef TANK_PLAYER_H_INCLUDED
#define TANK_PLAYER_H_INCLUDED

typedef enum {

	SMALL=0,
	MEDIUM,
	BIG

} TankKind;

typedef enum {

    SLOW=10,
    AVERAGE=20,
    FAST=30

} TankSpeed;

typedef enum {
	TEAM1=0,
	TEAM2
} TankTeam;

typedef struct {

	TankTeam team;
	TankKind kind;
	TankSpeed move_frequency; // In millis

	int row;
	int col;

	unsigned int x;
	unsigned int y;

	int lifepoints;

} Tank_Player;


#endif // TANK_PLAYER_H_INCLUDED
