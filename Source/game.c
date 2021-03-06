/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Aidan Harris
 * Student number: s3691198
 */

#include "game.h"
#include "huntWump.h"
#include <conio.h>
#define MAXLINE 50
#define DIR_COMMAND_AMOUNT 8

void game_PlayGame(){
	
	printf(COMMAND_LISTP1);
	
	State state = nothing_LOADED;//lets system know what commands are avalable
	
	const char *DIRECTION_COMMANDS[DIR_COMMAND_AMOUNT] = {COMMAND_NORTH,COMMAND_NORTH_SHORTCUT,COMMAND_SOUTH,COMMAND_SOUTH_SHORTCUT,COMMAND_EAST,COMMAND_EAST_SHORTCUT,COMMAND_WEST,COMMAND_WEST_SHORTCUT};
	char input[MAXLINE],command[MAXLINE], addon[MAXLINE];//string values, mainly for input handling
	Boolean val,inRange;
	Board pBoard;
	PlayerMove moveResult;//for handling move result
	Player player;
	Position playerPos;
	int x , y;//placeholders for input values eg. init x y (or) load x
	do{
		fgets (input, MAXLINE, stdin);
		//generilised command scan, to get what the command is
		sscanf( input, "%s", command);

		if((strcmp(command,COMMAND_LOAD)==0)&&(sscanf( input, "%s %d", command, &x)==2)){
				if(game_LoadBoard(pBoard,x) == TRUE){
					state = board_LOADED;
				}
		}
		
		//check for init command
		else if ((sscanf( input, "%s %d  %d", command, &x, &y) == 3)&&(strcmp(command,COMMAND_INIT)==0)){
			if(state == board_LOADED && state != position_LOADED){	
			inRange = game_PlacePlayer(pBoard,x,y);//try place player function checks if location is empty
				printf(": returned value is %d\n",inRange);
				if(inRange == 1){
					game_position(&playerPos,x,y);
					state = position_LOADED;//update state

					player_Initialise(&player,playerPos);//initialise player position
					
					game_ShowBoard(pBoard,playerPos);//display board
				}
				else if(inRange == 0){
					printf("Cannot place player here\n");
				}
			}else printf("\nPlease Load a board before initilising a position\n");
		}
		

		else if (strcmp(command,COMMAND_SHOOT)==0 && sscanf( input, "%s %s", command, addon) == 2){
			
			if(state == position_LOADED){
				if(game_SetDirection(addon) == player_NULL){
					//shoot arrow
					printf("arrow shot at %s",addon);
				}
			}else printf("\nPlease Load Player Position before trying to fire an arrow\n");
		}

		else if (strcmp(command,COMMAND_QUIT)==0){
			state = end_LOADED;
			return;
		}
		//check  if command is valid direction
		else if (game_CheckIn(command,DIRECTION_COMMANDS)==TRUE){
			
			if(state == position_LOADED){
				//get direction and player pos
				Direction dMove = game_SetDirection(command);
				//game_EqualPositions(playerPos,player.position);

				Position nextPos;
				game_EqualPositions(&nextPos,(player_GetNextPosition(playerPos, dMove)));
				moveResult = board_MovePlayer(pBoard,playerPos,nextPos);
				
				printf("moving player from (%d,%d) to (%d,%d)",playerPos.x,playerPos.y,nextPos.x,nextPos.y);
				
				if(moveResult == board_PLAYER_MOVED){
					printf("p moved");
					playerPos = nextPos;
					game_ShowBoard(pBoard,playerPos);
				}
				else if(moveResult == board_PLAYER_KILLED){
					state = end_LOADED;
				}
				else if(moveResult == board_BAT_CELL){
					Boolean val;
					int bX;
					int bY;
					Position temp;
					do{
						bX = rand() % 5;
						bY = rand() % 5;
						game_position(&temp,bX,bY);
						val = board_PlacePlayer(pBoard,temp);
					}while(val != TRUE);
					game_position(&playerPos,bX,bY);
					player_UpdatePosition(&player,playerPos);
				}
				else if(moveResult == board_OUTSIDE_BOUNDS){
					printf("Cannot move outside bounds, try another direction");
				}
			}else printf("\nPlease Load Player Position before trying to move\n");
			
		}
		else printf("\nINVALID INPUT\n");
		*input = 0;

	}while(state != end_LOADED);
	
	srand(0);
}

void game_MainMenu(){
	printf(GREETING_STR);
	int n=0;
	do{
		printf("\nPlease enter your choice: ");
		char in = _getch();
		if(isdigit(in)){
			n = in -'0';
			printf("\n");
			if(n == 1){
				game_PlayGame();
				printf(GREETING_STR);			
			}
			else if(n == 2){
				showStudentInformation();
			}
			else if(n ==3){
				printf("Good bye! \n\n");
				exit(0);
			}
			else{
				printf("option out of bounds chosen\n");
			}
		}
	}while(n != 3);
}

void print_Commands(State state){
	printf(AVALABLE_COMMANDS);
	if (state == nothing_LOADED){
		printf("load <g>\nquit\n");
	}
	else if (state ==board_LOADED){
		printf("init <x>,<y>\nquit\n");
	}
	else if (state == position_LOADED){
		printf("<direction>\nshoot <direction>\nquit\n");
	}
}

void game_ShowBoard(Board pBoard, Position playerPos){
			board_Display(pBoard);
			board_DisplayWarnings(pBoard,playerPos);
}

Boolean game_LoadBoard(Board pBoard, int boardNo){
	if(boardNo == 1){
		printf("\nloading board 1\n");
		board_Load(pBoard,BOARD_1);
		return TRUE;
		}
	else if(boardNo == 2){
		printf("\nloading board 2\n");
		board_Load(pBoard,BOARD_2);
		return TRUE;
		}
	else{
		printf("\ninvalid choice\n");
		return FALSE;
		}
}
Boolean game_PlacePlayer(Board pBoard,int x,int y){
	Position pos;
	if(x >= 0 && x <= BOARD_WIDTH && y >= 0 && y <= BOARD_HEIGHT){
		//x &y are within bounds
		pos.x = x;
		pos.y = y;
		board_PlacePlayer(pBoard, pos);
		return TRUE;
	}
	else{ 
		printf("ERROR position out of bounds");
		return FALSE;
	}
}	

Direction game_SetDirection(char input[]){
	if(strcmp(input,COMMAND_NORTH)==0||strcmp(input,COMMAND_NORTH_SHORTCUT)==0){
		return player_NORTH;
	}
	else if(strcmp(input,COMMAND_EAST)==0||strcmp(input,COMMAND_EAST_SHORTCUT)==0){
		return player_EAST;
	}
	else if(strcmp(input,COMMAND_SOUTH)==0||strcmp(input,COMMAND_SOUTH_SHORTCUT)==0){
		return player_SOUTH;
	}
	else if(strcmp(input,COMMAND_WEST)==0||strcmp(input,COMMAND_WEST_SHORTCUT)==0){
		return player_WEST;
	}
	else return player_NULL;
}

Boolean game_CheckIn(char input[],const char *array[]){
	int length = DIR_COMMAND_AMOUNT;
	int i;
	for(i = 0; i < length; ++i)
	{
   		if(strcmp(input,array[i])==0){
			return TRUE;
		}
	}
	return FALSE;
}
void game_position(Position * position,int x,int y){
	position->x = x;
	position->y = y;
	printf("\nPOS %d,%d\n",position->x,position->y);
}
void game_EqualPositions(Position* pos1, Position pos2){
	//makes pos1 = pos2
	int x = pos2.x;
	int y = pos2.y;
	pos1->x=x;
	pos1->y=y;

}
