/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :Aidan Harris
 * Student number: S3691198
 */
#include "player.h"

void player_Initialise(Player * player, Position position){
   	player->position.x = position.x;
	player->position.y = position.y;
	printf("\n--%d,%d--\n",position.x,position.y);
	player->numArrows = INIT_ARROW_COUNT;
}


Position player_GetNextPosition(Position position, Direction direction){
 	Position newPosition;
	int X = position.x, Y = position.y;
	printf("\n-%d,%d-\n",X,Y);
	if(direction == player_NORTH){
		Y = Y-1;
	}
	else if(direction == player_EAST){
		//move right (x+1)
		X = X+1;
	}
	else if(direction == player_SOUTH){
		//move down (y -1)
		Y = Y+1;
	}
	else if(direction == player_WEST){
		//move left (x -1)
		X = X-1;
	}
	newPosition.x = X;
	newPosition.y = Y;
   	return newPosition;
}

void player_UpdatePosition(Player * player, Position position) {
   	player->position.x = position.x;
	player->position.y = position.y;
}

