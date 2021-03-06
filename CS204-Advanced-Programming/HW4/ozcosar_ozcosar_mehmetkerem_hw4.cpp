
/*This program reaf the txt file and create 2D matrix with the characters in the txt file. after that finds the empty spaces with respext to given coordinate
and fill empty areas with the given character*/

#include <iostream>
#include <string>
#include <fstream>
#include "strutils.h"
#include "dynStack.h"
using namespace std;

/*Begin : taken form the matrix.cpp and updated */
void PrintMatrix(char **matrix, int size, int c)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<c; j++) 
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}
/*End : taken form the matrix.cpp and updated */

/* Begin: taken from matrix.cpp */
void DeleteMatrix(char ** matrix, int size)
{
	for(int i=0; i<size; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}
/* End: taken from matrix.cpp */

void FillEmptyArea(DynStack CoorStack, char **mat, int j, int k, int r, int c)
{
	if (mat[j][k] == 'X') // look at the given coord is empty or not. If is not empty close the program.
	{
		cout << "Starting point is already occupied. " << endl;
		cout << "Terminating..." << endl;
	}

	else
	{
		char ch;  
		cout << "Enter the filling char: " ; // take the char for the filling area
		cin >> ch;
		while (ch == 'X' || ch == 'x') // given char cannot be the X or x 
		{
			cout << "Filling char is not valid! " << endl;
			cout << "Enter the filling char: " ;
			cin >> ch;
		}
		
		CoorStack.push(j,k);  // push given coord into a stack
		mat[j][k] = ch; // change char in the given coord with the given char
		while(!CoorStack.isEmpty()) // control the stack is empty or not if is empty go out of the loop
		{
			if (mat[j][k+1] == ' ' || mat[j][k-1] == ' ' || mat[j+1][k] == ' ' || mat[j-1][k] == ' ') // checks the neighboorhod of the given coord is empty or not
			{
				
				while (mat[j][k+1] == ' ') // while right of the coord is empty fill the empty area with the given char
				{
					k++;				 // increment column index
					CoorStack.push(j,k); // push stack the coord
					mat[j][k] = ch;      // change char in the right of the given coord
				}
				while (mat[j][k-1] == ' ') // checks left
				{
					k--;				// go left
					CoorStack.push(j,k);
					mat[j][k] = ch;
				}
				while (mat[j+1][k] == ' ') // checks down
				{
					j++;					// go down
					CoorStack.push(j,k);
					mat[j][k] = ch;
				}
				while (mat[j-1][k] == ' ') // checks up
				{
					j--;					// go up
					CoorStack.push(j,k);
					mat[j][k] = ch;
				}
			}
			else // if cannot go anywhere 
			{

				/*pop the coord in stack and checks its neighboorhood, it like checks the coord in reverse way. Checks the all popped coordinates*/
				while (!CoorStack.isEmpty())
				{
					CoorStack.pop(j,k); //pop the coord 

				 //checks the popped coord's neighborhood
					while (mat[j][k-1] == ' ') //while left neighboors are empty go left and fill with the char
					{
						k--;
						CoorStack.push(j,k);
						mat[j][k] = ch;
					}
					while (mat[j][k+1] == ' ') //while right neighboors are empty go right and fill with the char
					{
						k++;
						CoorStack.push(j,k);
						mat[j][k] = ch;
					}
					while (mat[j+1][k] == ' ') //while down neighboors are empty go down and fill with the char
					{
						j++;
						CoorStack.push(j,k);
						mat[j][k] = ch;
					}
					while (mat[j-1][k] == ' ') //while up neighboors are empty go up and fill with the char
					{
						j--;
						CoorStack.push(j,k);
						mat[j][k] = ch;
					}
				}
			}
		}
		PrintMatrix(mat, r, c);
	}
}


int main()
{
	DynStack CoorStack;
	string row, col;
	string filename, line;
	ifstream input;
	cout << "Enter the number of rows: " ;
	cin >> row;
	int r = atoi(row);
	while (r != 3 && r != 10 && r != 11 && r != 22  && r != 34) // checks the number of rows is true or not
	{
		cout << row << " is invalid" << endl;
		cout << "Enter the number of rows: " ;
		cin >> row;
		r = atoi(row);
	}
	cout << "Enter the number of columns: " ;
	cin >> col;
	int c = atoi(col);
	while ((r == 3 && c != 10) || (r == 10 && c != 3 ) || (r == 11 && c != 12) || (r == 22 && c != 40) || (r == 34 && c != 51)) // checks the number of columns are true or not with the respect of number of rows
	{
		cout << col << " is invalid" << endl;
		cout << "Enter the number of columns: " ;
		cin >> col;
		c = atoi(col);
	}
	cout << "Please enter file name: " ;
	cin >> filename;
	input.open(filename.c_str());
	while (input.fail())
	{
		cout << "Cannot find a file named " << filename << endl;
		cout << "Please enter file name: " ;
		cin >> filename;
		input.open(filename.c_str());
	}
	
	char** dmatrix = new char*[r]; // it creates the char pointers with size of rows and dmatrix points those pointers(pointer to pointers)
	for(int i =0; i<r; i++)
	{
		dmatrix[i] = new char[c]; // every row pointers points to the new char with the size of column
	}

	while (!input.eof())
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c;)
			{
				getline(input,line); // takes the line in txt file 
				for (int k = 0; k < line.length(); k++) 
				{
					dmatrix[i][j] = line.at(k); // takes the character of the line and put in the node in the 2d matrix 
					j++; //increment the column index 
				}
			}
		}
	}
	string coor_row, coor_col;
	cout << "Enter the starting point: " ;
	cin >> coor_row >> coor_col;
	int j = atoi(coor_row);
	int k = atoi(coor_col);
	while (j >= r || k >= c || isalpha(coor_row[0]) || isalpha(coor_col[0]) || j < 0 || k < 0)
	{
		cout << "Invalid coordinate!!!" << endl;
		cout << "Enter the starting point: " ;
		cin >> coor_row >> coor_col;
		j = atoi(coor_row);
		k = atoi(coor_col);
	}
	FillEmptyArea(CoorStack,dmatrix,j,k,r,c);
	DeleteMatrix(dmatrix, r);
	return 0;
}
