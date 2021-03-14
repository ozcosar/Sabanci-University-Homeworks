#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include "strutils.h"


using namespace std;

struct node
{
	 int month, year; 
	 vector<string> cards;
	 node* next;		 

	//default constructor
	node::node ()
		:month(0),year(0),next(NULL)
	{}

	//constructor
	node::node (int i, int j,string k)
		:month(i),year(j)

	{
		cards.push_back(k);
		next = NULL;
	}
	
};

void PrintList(node*head){ // to print the list
	node* ptr = head->next;// to control to print the first 0 0 node.
	if (ptr == NULL)
	{
		cout << "List is empty " << endl;
	}
	while (ptr != NULL) // check the ptr is null or not
	{
		cout << "Expiration Date: " << ptr->month << " " << ptr->year<< endl;
		for (int i = 0; i < ptr->cards.size(); i++) // print the all elements in the cards vector
		{
			cout << ptr->cards[i] << endl;
		}
		cout << "-------------------" << endl;
		cout << endl;
		ptr = ptr->next ;
	}
}

void sortList(node* &head)
{
    if (head != NULL)
    {
        node* current = head;
        node* ptr = NULL;
        node* temp = NULL;
		node* tail = NULL;
		int cnt = 0;
        bool found = false;
		while (current != NULL) // find the lenght of list with cnt variable
		{
			current = current->next;
			cnt++;

		}
		current = head;
        for (int i = 0; i < cnt; i++) // check the all nodes with the length of list 
        {
            while (current->next != NULL) // in order to reach last node
            {
                temp = current->next;

                if ((current->year > temp->year) || (current->year == temp->year && current->month > temp->month)) //compare the values in current and the next value in the next node.
                {
                    found = true;
                    current->next = temp->next; // change the current one 
                    temp->next = current;		// with the next one
                    if (ptr != NULL){
                        ptr->next = temp;
					}
                    ptr = temp;
                    if (head == current){ // if head still equal the current one 
                        head = temp;	// change the head with temp
					}
                    if (current->next == NULL){ // if current's next is null 
                        tail = current;			// current one also equal the tail of list.
					}
                }
                else
                {
                    ptr = current;
                    current = current->next;
                }
            }
            if (found == false) // at the if cannot change the any value in the list stop the loop because list is already sorted.
                break;
			else
            {
                ptr = NULL;	// if found not false start the process again.
                current = head;
                found = false;
            }
        }
    }
}


bool searchList(node * head, int search_month, int search_year, string cardsnum){
	
	node *p = head;
	if (p == NULL) 
	{
		return false;
	}
	if(p->month == search_month && p->year == search_year){ // if pointer's month and years are equal another one from the 
															// txt files their creditcards' numbers must be stored in the same node
		p->cards.push_back(cardsnum);						// pushback the new cardnum into the same node.
		cout << "Node with expiration date " << p->month <<" "<< p->year<<" already exists"<< endl;
		cout << "Credit card "<< cardsnum << " added to the " << p->month <<" "<< p->year<<endl;
		cout << "***********" << endl;
		cout << endl;
		return true;
	}
	return searchList(head->next,search_month,search_year,cardsnum); 
}
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
bool findNode(string cards_number, node* head){
	node * ptr = head;
	while (ptr != NULL)
	{
		for (int i = 0; i < ptr->cards.size(); i++) // to control the every cardsnumber in the nodes because
		{                                          // some nodes includes more than one cardsnumber

			if (ptr->cards[i] == cards_number)	// find the node from the given cardsnumber
			{
				cout << "There exists a credit card given number " << ptr->cards[i] << " with expiration date: " 
					<< ptr->month << " " << ptr->year << endl;
				cout << endl;
				return true;
			}
		}
		ptr = ptr->next; //increment 
	}
	return false;
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


bool search_list(node* head, int m, int y){ 
	node* ptr = head;
	while (ptr != NULL)
	{
		if (ptr->month == m && ptr->year == y) // in order to check given month and year are include in the list
		{
			return true;
		}
		ptr = ptr->next; //increment
	}
	return false;
}


void deleteNode(int month, int year, node *&head){
	node *ptr = head;

	while (ptr->next !=NULL && (ptr->next->month != month || ptr->next->year != year)) // to find the last node before the 
	{                                                                           // given month and year's node.
		ptr = ptr->next;
	}
	
	cout << "Node with expiration date " << ptr->next->month << " " << ptr->next->year <<" and the following credit cards have been deleted!" << endl;
	for (int i = 0; i < ptr->next->cards.size(); i++)
	{
		cout << ptr->next->cards[i] << endl;
	}
	cout << endl;
	ptr->next = ptr->next->next; // delete part , ptr is previous node before the founded node and ptr->next point the founded one 
								// ptr->next->next point to the next node from the founded in the end ptr->next not point to the 
								// founded node it points to the founded one's next so that founded one is deleted.
}

/* start : taken from the lab3 linkedlist.cpp*/
void ClearList(node *head) 
{
	while(head!=NULL)
	{
		head=head->next;
		delete head;
	}
}
/* end : taken from the lab3 linkedlist.cpp*/

int main(){
	string line,filename, cardsnum;
	int m, y;
	ifstream input;

	node * head = NULL;
	node * tail = NULL;
	node * temp = NULL;
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
	//input.open(filename);
	head = new node(); // create new node
	temp = head;		// point to new node
	tail = head;// point to new node
	while (getline(input,line))
	{			
		istringstream iss(line); 
		iss >> cardsnum >> m >> y; // to get the all element with separate space
		if (searchList(head,m,y,cardsnum)==false) // if it is not already in the list
		{
			temp->month = m; // add the mont that node
			temp->year = y;	// add the year
			temp->cards.push_back(cardsnum); // add the cardsnum
			cout <<"New node is created with expiration date: " << temp->month << " " << temp->year << endl;
			cout << "Credit card " << cardsnum << " added to the " << temp->month << " " << temp->year << endl;
			cout << "***********" << endl;
			temp = new node(); // create new node
			tail->next = temp;
			tail = tail->next;
		}
		
	}

	int num = 0;
	while (num != 4)
	{
		cout <<"1)Display List" << endl;
		cout << "2)Card Search via Credit Number"<< endl;
		cout << "3)Delete Card with respect to Expiration Date"<< endl;
		cout << "4)Exit" << endl;
		cout << "Please choose option from the menu: ";
		cin >> num;
		cout << endl;
		if (num == 1)
		{
			sortList(head);
			PrintList(head);
		}
		if (num == 2)
		{
			string cards_number;
			cout << "Please enter the credit card number:  ";
			cin >> cards_number;
			while (cards_number.length() != 16 || isDigit(cards_number) == false ) // to check cardsnumber is only consist of digits																		//
			{                                                                      // and the length is 16
				cout << "Invalid Format!" << endl;
				cout << "Please enter the credit card number:  ";
				cin >> cards_number;
			}
			if (findNode(cards_number,head) == false ) // if given credit cards number is not in the list
			{
				cout << "There  is  no  credit  card  with  given  credit  card  number: " << cards_number << endl;
				cout << endl;
			}
		}
		if (num == 3)
		{
			string month, year;
			cout << "Please enter month and year: ";
			cin >> month >> year;
			while (foundAlpha(month,year) == true || atoi(month) > 12) // to check month year includes only digits 
			{                                                         // and also month cannot bigger than 12
				cout << "Invalid Date!" << endl;
				cout << "Please enter month and year: ";
				cin >> month >> year;
			}
			int x = atoi(month); // convert the string month to int month
			int z = atoi(year);	 // convert the string year to int year
			if (search_list(head,x,z) == false)
			{
				cout << "There is no node with expiration date " << x << " " << z << ", nothing deleted!" << endl;
			}
			else
			{
				deleteNode(x,z,head);

			}
		}
		if (num == 4)
		{
			cout << "Terminating!!!" << endl;
			ClearList(head);
			//cout << "Terminating!!!" << endl;
			
		}

	}


	cin.get();
	cin.ignore();
	return 0;
}
