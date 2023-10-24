#include <iostream>
#include <cstdio>
#include <conio.h>

#include "header.h"

bool playing = true;

void initMapFile(MAP* map)
{
	FILE* file;

	fopen_s(&file, "mapa.txt", "r");
	if (file == NULL)
	{
		std::cout << "ERROR: File mapa.txt not found." << std::endl;
		exit(1);
	}

	fscanf_s(file, "%d %d", &(map->x), &(map->y));

	allocMap(map);

	for (int i = 0; i < map->x; i++)
	{
		fscanf_s(file, "%s", map->grid[i], map->y);
	}

	fclose(file);
}

void allocMap(MAP* map)
{
	map->grid = (char**)malloc(sizeof(char*) * map->x);
	for (int i = 0; i < map->x; i++)
	{
		map->grid[i] = (char*)malloc(sizeof(char) * ((int)map->y + 1));
	}
}

void displayMap(MAP* map)
{
	system("cls");

	for (int i = 0; i < map->x; i++)
	{
		std::cout << map->grid[i] << std::endl;
	}
}

bool emptyPosition(MAP* map, int x, int y)
{
	if (x > map->x || x < 0 || y > map->y || y < 0)
		return false;

	if (map->grid[x][y] == EMPTY)
		return true;

	return false;
}

bool checkMonsterColision(MAP* map, int x, int y)
{
	if (map->grid[x][y] == MONSTER || map->grid[x][y] == PLAYER)
	{
		playing = false;
		return true;
	}

	return false;
}

void addCreature(MAP* map, CREATURE* creature, char body, int x, int y)
{
	if (!emptyPosition(map, x, y))
		return;

	creature->body = body;
	creature->x = x;
	creature->y = y;

	map->grid[creature->x][creature->y] = creature->body;
}

bool checkActions(char key)
{
	if (key != 'w' || key != 'a' || key != 's' || key != 'd')
		return false;

	return true;
}

void movePlayer(MAP* map, CREATURE* player)
{
	char key;
	int newx, newy;

	newx = player->x;
	newy = player->y;

	key = _getch();
	if (checkActions(key))
		return;

	switch (key)
	{
		case('w'):
		{
			newx--;
			break;
		}

		case('a'):
		{
			newy--;
			break;
		}

		case('s'):
		{
			newx++;
			break;
		}

		case('d'):
		{
			newy++;
			break;
		}
	}

	if (checkMonsterColision(map, newx, newy))
		return;

	if (!emptyPosition(map, newx, newy))
		return;

	map->grid[player->x][player->y] = EMPTY;
	
	player->x = newx;
	player->y = newy;

	map->grid[player->x][player->y] = PLAYER;
}

void moveMonster(MAP* map, CREATURE* monster)
{
	int dir;
	int newx, newy;

	srand((int)time(0));
	dir = rand() % 4;

	newx = monster->x;
	newy = monster->y;

	switch (dir)
	{
		case(0): // North
		{
			newx--;
			break;
		}

		case(1): // West
		{
			newy--;
			break;
		}

		case(2): // South
		{
			newx++;
			break;
		}

		case(3): // East
		{
			newy++;
			break;
		}
	}

	if (!emptyPosition(map, newx, newy))
		return;

	map->grid[monster->x][monster->y] = EMPTY;

	monster->x = newx;
	monster->y = newy;
	map->grid[monster->x][monster->y] = monster->body;
}


int main()
{
	MAP world;
	CREATURE player;
	CREATURE mobBlue, mobYellow;

	initMapFile(&world);

	addCreature(&world, &player, PLAYER, 2, 7);
	addCreature(&world, &mobBlue, MONSTER, 5, 1);
	addCreature(&world, &mobYellow, MONSTER, 5, 13);

	while (playing)
	{
		displayMap(&world);
		movePlayer(&world, &player);
		moveMonster(&world, &mobBlue);
		moveMonster(&world, &mobYellow);
	}
};