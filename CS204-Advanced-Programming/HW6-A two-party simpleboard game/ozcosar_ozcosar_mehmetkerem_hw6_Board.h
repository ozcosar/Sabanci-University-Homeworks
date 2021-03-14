#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board
{
	public:
		Board(); //constructor
		//These functions are not called by main function; but are called by
		//Player class and since we did not declare friend class we should make
		//these functions public.
		char getOwner(int, int);
		void setOwner(int, int, char);
		int countOwnedCells(char);
		
		void displayBoard()const;
		bool isFull()const;

	private:
		char myBoard[2][6];
		bool CellIsEmpty(int row, int col)const;
};
#endif
