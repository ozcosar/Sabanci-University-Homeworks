
#ifndef PLAYER_H
#define PLAYER_H

#include "ozcosar_ozcosar_mehmetkerem_hw6_Board.h"
#include<iostream>
using namespace std;

class Player
{
public:
	Player(Board&,char,int); //constructor
	void move(int);//move in board
	void claimOwnership();//set player char 
	bool wins();
	//accesors
	int getRow();
	int getCol();

private:
	Board& board; //sharing board
	char PlayerChr;
	int dir; //in order to set the moving direction, 1 for clockwise, 0 for counter-clockwise
	int row,col;
};



#endif