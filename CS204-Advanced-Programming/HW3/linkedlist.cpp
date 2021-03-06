#include<iostream>
#include "linkedlist.h"
#include <string>

using namespace std;

CardList::CardList()
{
	head = NULL;
	tail = NULL;
}

bool CardList::searchList(string cardsnum, int month, int year){
	expirationNode* ptr = head;
	while (ptr != NULL)
	{
		if (ptr->month == month && ptr->year == year) 
		{
			creditCardNode* temp;
			temp = ptr->cHead; 
			creditCardNode* p = temp;
			bool exist = false; /*checks it is already exist or not*/
			while (p != NULL) /*search the in the creditcardno linkedlist */
			{
				if (p->creditCardNo == cardsnum) 
				{
					cout << p->creditCardNo << " " << ptr->month << " " << ptr->year << ": this cards was already exist." << endl;
					exist = true; 
				}
				p = p->next;
			}
			if (temp->next == NULL && exist == false)
			{
				temp->next = new creditCardNode(cardsnum, NULL); /*if exist false create a new creditCardNode in the current expiration date node*/
				cout << temp->next->creditCardNo << " " << ptr->month << " " << ptr->year << ": inserted to an existing node." << endl;
			}
			else
			{
				while (temp->next != NULL) /* in order to reach the end of the creditcards linkedlist*/
				{
					temp = temp->next;
				}
				if (exist == false) 
				{
					temp->next = new creditCardNode(cardsnum,NULL); /* add the new node end of the creditcards linkedlist*/
					cout << temp->next->creditCardNo << " " << ptr->month << " " << ptr->year << ": inserted to an existing node." << endl;
				}
			}
			return true;
		}
		ptr = ptr->next; // increment the head
	}
	return false;
}
void CardList::printList(){
	expirationNode* p = head;
	if (p == NULL)
	{
		cout << "List is empty..." << endl;
	}
	while (p != NULL)
	{
		cout << "Expiration Date: " << p->month << " " << p->year << endl;
		creditCardNode* ptr = p->cHead;
		while (ptr != NULL)
		{
			cout << ptr->creditCardNo << endl;
			ptr = ptr->next;
		}
		cout << "-------------------" << endl;
		p = p->next;
	}
}

/* start: taken from doublylinkedkist.cpp */
void CardList::insertCard(string creditCardNo, int month, int year)
{
	expirationNode* ptr = head;

	if (tail == NULL) 
	{
		expirationNode* temp = new expirationNode(month, year, NULL, NULL, NULL); /*add the first line of the txt file in the linked list*/
		tail = temp;
		head = tail; // head = tail beacuse it is the first node in the linked list
		head->cHead = new creditCardNode(creditCardNo,NULL); // create a creditcards node in the expirationdate node
		cout << temp->cHead->creditCardNo << " " << temp->month << " " << temp->year << ": added to a new expiration date node" << endl;

	}
	else
	{
		if (searchList(creditCardNo,month,year) == false) /*if cannot found the same month and year create new node*/
		{
			expirationNode* temp = new expirationNode(month,year,NULL,tail,NULL); // create a new node and previous of the node is point to the previous node in the linkedlist
			temp->cHead = new creditCardNode(creditCardNo,NULL); // create a new creditcards node in the expirationdate node
			cout << temp->cHead->creditCardNo << " " << temp->month << " " << temp->year << ": added to a new expiration date node" << endl;
			tail->next = temp; // connect the nodes together
			tail = temp; // increment the tail
		}
	}
}
/*stop: taken from doublylinkedlist.cpp*/

void CardList::displayListChronological() 
{ 
	if (head != NULL)
    {
        expirationNode* current = head;
        expirationNode* ptr = NULL;
        expirationNode* temp = NULL;
		expirationNode* last = NULL;
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
                    temp->next = current;// with the next one
					current->prev = temp->prev; // connect the prev pointers

                    if (ptr != NULL){
                        ptr->next = temp;
					}
                    ptr = temp;
                    if (head == current){ // if head still equal the current one 
                        head = temp;// change the head with temp
						head->prev = NULL; // head prev always equal to the null
					}
                    if (current->next == NULL){ // if current's next is null 
                        last = current;			// current one also equal the tail of list.
					}
                }
				else // cannot found
                {
                    ptr = current; 
					current->next->prev = current; 
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
void CardList::displayListReverseChronological(){
	displayListChronological(); // run the chronological 
	expirationNode* temp = head;
	if (head == NULL)
	{
		cout << "List is empty..." << endl;
	}
	else
	{
		while (temp->next != NULL) // found the last node 
		{
			temp = temp->next;
		}
		while (temp != NULL) // last node not equal to null
		{
			cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
			creditCardNode* ptr = temp->cHead;
			while (ptr != NULL) // print creditcards node while ptr not equal to the null
			{
				cout << ptr->creditCardNo << endl;
				ptr = ptr->next;
			}
			cout << "-------------------" << endl;
			temp = temp->prev; // in order to move backforward
		}
	}
}

void CardList::cardsSearch(string creditCardNo){/*search the given creditcardno in the linked list*/
	expirationNode* ptr = head;
	creditCardNode* pHead = ptr->cHead;
	while (ptr!= NULL) // ptr not equal to the null
	{
		while (pHead != NULL) // pHead not equal to the null
		{
			if (pHead->creditCardNo == creditCardNo) // search the given creditcardno in the creditcardno linkedlist
			{
				cout << "There exists a credit card given number " << pHead->creditCardNo << " " << ptr->month << " " << ptr->year << endl; 
			}
			pHead = pHead->next; // increment the creditcardnode pointer
		}
		ptr = ptr->next; // increment the expirationdatenode's pointer
	}
	cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
}

void CardList::bulkDelete(int month, int year){ /*delete the nodes smaller than the given month and year*/
	expirationNode* temp = head;
	creditCardNode* ptr;
	expirationNode* p;
	//bool delhead = false;
	while (temp != NULL)
	{
		bool delhead = false; // checks the head was deleted or not
		if ((temp->year < year && temp->month > month) || (temp->year < year && temp->month <= month))
		{
			cout << "Node with expiration date " << temp->month << " " << temp->year <<" and the following credit cards have been deleted!" << endl;
			ptr = temp->cHead; // take the creditcardsnode with respect to founding expiraitondatenode's pointer
			while (ptr != NULL)
			{
				creditCardNode* cHead = ptr;
				cout << ptr->creditCardNo << endl;
				ptr = ptr->next;
				delete cHead; // delete the creditcardsnode 
			}
			if (temp == head) // if deleting node is equal to the head
			{
				p = head;
				head = temp->next; // increment the head
				temp = temp->next; // increment the head
				delhead = true; 
				delete p; // delete head
			}
			else //if deleteng node is not equal to the head
			{
			/*connect the nodes with extract the founding node*/
				temp->prev->next = temp->next; 
				temp->next->prev = temp->prev;
			}
		}
		if (delhead == false)
		{
			temp = temp->next;
		}
	}
}

void CardList::deleteAll(){ // delete the al nodes in the linkedlist in order to clear the heap
	while (head != NULL)
	{
		head = head->next;
		delete head;
	}
}




	
