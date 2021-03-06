#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "linkedlist.h"
#include "strutils.h"

using namespace std;

bool isDigit(string cards_number){ // checks whether string include any alphabetic characters or not.
	for (int i = 0; i < cards_number.length(); i++)
	{
		if (!isdigit(cards_number[i]))
		{
			return false;
			break; // when found any alphabetic characters stop the loop because it includes alphabetic characters
		}
	}
	return true;
}
bool foundAlpha(string a, string b){ // check whether include alphabetic characters or not 
	for (int i = 0; i < a.length(); i++)
	{
		if (isalpha(a[i]) || isalpha(b[i]))
		{
			return true;
		}
	}
	return false;

}
int main(){
	CardList myList;
	string filename, line, cardsnum, cardno, month, year;
	int num = 0, m, y, inty, intm;
	ifstream input;

	while (num != 6)
	{ 
		cout << "1) Upload Card(s) from a File" << endl;
		cout << "2) Display List Chronological"<< endl;
		cout << "3) Display List Reverse Chronological"<< endl;
		cout << "4) Card Search" << endl;
		cout << "5) Bulk Delete" << endl;
		cout << "6) Exit" << endl;
		cout << "Please choose option from the menu: ";
		cin >> num;
		cout << endl;
		if (num == 1)
		{
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
			while (getline(input,line))

			{
				istringstream iss(line);
				iss >> cardsnum >> m >> y;
				myList.insertCard(cardsnum,m,y);
			}
		}
		if (num == 2)
		{
			myList.displayListChronological();
			myList.printList();
		}
		if (num == 3)
		{
			myList.displayListReverseChronological();
		}
		if (num == 4)
		{

			cout <<"Please enter the credit card number: " ;
			cin >> cardno;
			while (cardno.length() != 16 || isDigit(cardno) == false)
			{
				cout << "Invalid Format" << endl;
				cout <<"Please enter the credit card number: " ;
				cin >> cardno;
			}
			myList.cardsSearch(cardno);
		}
		if (num == 5)
		{
			cout << "Please enter month and year: " ;
			cin >> month >> year ;
			while (foundAlpha(month,year) || atoi(month) > 12)
			{
				cout << "Invalid Format" << endl;
				cout << "Please enter month and year: ";
				cin >> month >> year;
			}
			intm = atoi(month);
			inty = atoi(year);
			myList.bulkDelete(intm,inty);
		}
		if (num == 6)
		{
			cout << "All the nodes have been deleted!" << endl;
			cout << "Terminating..." << endl;
			myList.deleteAll();

		}
	}
	return 0;
}
