#pragma once
#include <iostream>

#define PLAYER 'O'
#define MONSTER 'C'
#define WALL '#'
#define EMPTY '.'

struct Map
{
	char** grid;
	int x;
	int y;
};

typedef struct Map MAP;

struct Creature
{
	char body;
	int x;
	int y;
};

typedef struct Creature CREATURE;

void initMapFile(MAP* map);
void allocMap(MAP* map);
void displayMap(MAP* map);
bool emptyPosition(MAP* map, int x, int y);
bool checkMonsterColision(MAP* map, int x, int y);
void addCreature(MAP* map, CREATURE* creature, char body, int x, int y);
bool checkActions(char key);
void movePlayer(MAP* map, CREATURE* player);