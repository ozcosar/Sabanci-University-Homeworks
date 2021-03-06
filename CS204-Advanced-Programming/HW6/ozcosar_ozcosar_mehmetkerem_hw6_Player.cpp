#include "ozcosar_ozcosar_mehmetkerem_hw6_Board.h"
#include "ozcosar_ozcosar_mehmetkerem_hw6_Player.h"

using namespace std;

//constructor
Player::Player(Board& board, char c, int dir)
	: board(board), PlayerChr(c), dir(dir), row(0), col(0)
{}

void Player::move(int num){
	if (dir == 1) // go clockwise
	{
		int count = 0;
		if (row == 0) // in the row 0 go right
		{
			while (col < 6 && count < num)  // # of column must smaller than the 6 and count smaller than given number
			{
				col++; //increment column
				if (col < 6)
				{
					count++; // increment count
				}
			}
			if (col >= 6 && count < num) // if exceed the column limit
			{ 
				count++; // increment count for the moving down
				row = 1; // set row = 1
				col = 5; // set col = 5
			}
			while(count < num) 
			{
				col--; // go left in the row 1 for dir = 1
				count++; // increment count
			}
		}
		else // if row == 1
		{
			while (col > 0 && count < num) 
			{
				col--; // go left
				if (col >= 0) 
				{
					count++; // increment count
				}
			}
			if (col <= 0 && count < num) // if exceed the column limit
			{
				count++; // increment count for moving up 
				row = 0; // set row = 0
				col = 0; // set column = 0
			}
			while (count < num)
			{
				count++; 
				col++; // go right
			}
		}
	}
	if (dir == 0) // go counter-clockwise
	{
		int k = 0;
		if (row == 0)
		{
			while (col >= 0 && k < num) 
			{
				col--; // decrease column, go left 
				if (col >= 0)
				{
					k++; // increment
				}
			}
			if (col <= 0 && k < num) // if exceeds the limit
			{
				k++; // increment for moving down
				row = 1; // set row = 1
				col = 0; // set col = 0
			}
			while (k < num)
			{
				k++; // increment
				col++; // go right in the row 1
			}
		}
		else // if row == 1
		{
			while (col < 6 && k < num) 
			{
				col++; // go right 
				if (col < 6)
				{
					k++; // increment step
				}
			}
			if (col >= 6 && k < num) // exceeds limit
			{
				k++; // increment for moving up
				row = 0; // set row = 0
				col = 5; // set col = 5
			}
			while (k < num)
			{
				k++; // increment step
				col--; // go left
			}
		}
	}

}
// set char in the empty spaces
void Player::claimOwnership(){
	if (board.getOwner(row,col) == '-') // if given coordinat is empty 
	{
		board.setOwner(row,col,PlayerChr); // set the player char in the taken coordinates
	}
}	


bool Player::wins(){
	if (board.countOwnedCells(PlayerChr) > 6) // if number of player char is bigger than 6 that player wins
	{
		return true;
	}
	return false;
}

//accessors
int Player::getRow(){ 
	return row;
}
//accessors
int Player::getCol(){
	return col;
}
