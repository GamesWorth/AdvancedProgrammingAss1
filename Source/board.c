/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#include "board.h"

Board BOARD_1 =
{
   	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_PIT,    board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_BATS,   board_EMPTY,  board_EMPTY,  board_WUMPUS, board_EMPTY},
	{ board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY}
};

Board BOARD_2 =
{
	{ board_PIT,    board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_BATS },
	{ board_EMPTY,  board_WUMPUS, board_EMPTY,  board_EMPTY,  board_EMPTY},
};

void board_Load(Board board, Board boardToLoad) {
   /* TODO */
	int i;   
	for(i=0;i<BOARD_HEIGHT;i++){
		int j;
		for(j=0;j<BOARD_WIDTH;j++){
			board[i][j] = boardToLoad[i][j];
		}
	}
}

Boolean board_PlacePlayer(Board board, Position position) {
	int x = position.x,y = position.y;
	//printf("\n(%d,%d\n)",x,y);
	Boolean result;
	if(board[y][x] == 0){
		board[y][x] = 5;
		printf("placed player\n");
		result  = 1;
		printf("function val is : %d",result);
		return result;
	}
	else if (board[y][x] != 0){
		result = FALSE;
		printf("function val is : %d",result);
		return 0;
   }
}
PlayerMove board_MovePlayer(Board board, Position playerPosition,Position nextPosition) {
	
	int nextX = nextPosition.x, nextY = nextPosition.y;	
	board[playerPosition.y][playerPosition.x] = 1;
 	
	if(nextY<BOARD_HEIGHT && nextX<BOARD_WIDTH){//check if move is within board
  		
		Cell refCell = board[nextX][nextY];
		if(refCell == board_EMPTY||refCell == board_TRAVERSED){
			board[nextX][nextY] = board_PLAYER;
			return board_PLAYER_MOVED;
		}
		else if(refCell == board_BATS){
			printf("a group of bats have moved you to a random location\n");
			return board_BAT_CELL;
		}
		else if(refCell == board_PIT){
			printf("you have fallen to your death down a pit\n");
			return board_PLAYER_KILLED;
		}
		else if(refCell == board_WUMPUS){
			printf("the wumpas has killed you\n");
			return board_PLAYER_KILLED;
		}
	}
	else{
		return board_OUTSIDE_BOUNDS;
	}
}

ArrowHit board_FireArrow(Board board, Position position) {
   /* TODO */
   return board_ARROW_MISSED;
}

void board_Display(Board board) {
	printf("    0  1  2  3  4 \n  ----------------\n");
	int i;
	for(i=0;i<BOARD_HEIGHT;i++){
		printf("%d |",i);
		int j;
		for(j=0;j<BOARD_WIDTH;j++){
			if(board[i][j]==1){
				printf("**|");
			}
			else if(board[i][j]==5){
				printf("##|");
			}
			else{
				printf("  |");
			}
		}
		printf("\n");
	}
}

void board_DisplayWarnings(Board board, Position position){
  	
	int x = position.x,y = position.y;
	int X;
	for (X = -1;X <= 1;X++){
		int Y;
		for(Y = -1;Y <= 1;Y++){
			if((x+X)<0||(x+X)>4||(y+Y)<0||(y+Y)>4){
			//out of bounds do nothing
			}
			else if (board[x+X][y+Y]==board_BAT_CELL){
				printf("You Hear Flapping\n");
			}
			else if (board[x+X][y+Y]==board_PIT){
				printf("You feel a breeze\n");
			}
			else if (board[x+X][y+Y]==board_WUMPUS){
				printf("You smell Wumpas\n");
			}
		}
	}	
}
