
#include "ozcosar_ozcosar_mehmetkerem_hw6_Board.h"
#include <iostream>

using namespace std;

//constructor
Board::Board(){
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			myBoard[i][j] = '-';
		}
	}
}
//return the char in the given row and column
char Board::getOwner(int row, int col){

	return myBoard[row][col];
}
//put the given char in the given row and column
void Board::setOwner(int row, int col, char c){
	
	myBoard[row][col] = c;

}
// count the number of given char
int Board::countOwnedCells(char c){
	
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (myBoard[i][j] == c)
			{
				count++;
			}
		}
	}
	return count;
}
void Board::displayBoard()const{
	cout << "Board: " << endl;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			cout << myBoard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
// checks board is full or not
bool Board::isFull()const
{
	int countFullCells = 0;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(CellIsEmpty(i,j))
			{
				return false;
			}
		}
	}
	return true;
}
// checks given coordinate is empty or not
bool Board::CellIsEmpty(int row, int col)const
{
	if(myBoard[row][col] == '-')
	{
		return true;
	}

	return false;
}
