/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"
#define AVALABLE_COMMANDS "At this stage of the program only two commands are acceptable: \n"
#define GREETING_STR "Welcome to Hunt the Wumpus\n --------------------------\n 1. Play game\n 2. Show student information\n 3. Quit "
#define COMMAND_LISTP1 "load <g>\n\tg: number of the game board to load (either 1 or 2)\ninit <x>,<y>\n\tx: horizontal position of the player on the board (between 0 & 4)\n\ty: vertical position of the player on the board (between 0 & 4)\n north (or n)\n south (or s)\n east (or e)\n west (or w)\nquit\n "
#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_NORTH "north"
#define COMMAND_NORTH_SHORTCUT "n"
#define COMMAND_SOUTH "south"
#define COMMAND_SOUTH_SHORTCUT "s"
#define COMMAND_EAST "east"
#define COMMAND_EAST_SHORTCUT "e"
#define COMMAND_WEST "west"
#define COMMAND_WEST_SHORTCUT "w"
#define COMMAND_SHOOT "shoot"
#define COMMAND_QUIT "quit"

typedef enum state
{
	nothing_LOADED,
	board_LOADED,
	position_LOADED,
	end_LOADED
} State;

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 * and marks are allocated to good coding practices.
 */
void game_PlayGame();
//first booted on game start, 1launches game 2 shows info 3 quits
void game_MainMenu();
void print_Commands(State state);
//displays board after any move, shot,load or placement
void game_ShowBoard(Board pBoard,Position playerPos);
//loads board if boardNo is a valid board number, else produces warning
Boolean game_LoadBoard(Board pBoard,int boardNo);
//check if position is within bounds and set
Boolean game_PlacePlayer(Board pBoard,int x,int y);
//returns a Direction type from input, assumes input is a valid direction
Direction game_SetDirection(char input[]);
//function to check if input is in array
Boolean game_CheckIn(char input[],const char *array[]);
//
void game_position(Position * position,int x,int y);
/* TODO not provided */
void game_EqualPositions(Position * pos1, Position pos2);
#endif
