
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;

struct creditCardNode
{
	string creditCardNo;
	creditCardNode* next;
	creditCardNode::creditCardNode()
	{}
	creditCardNode::creditCardNode(string s, creditCardNode* ptr)
		:creditCardNo(s), next(ptr)
	{}
};

struct expirationNode
{
	creditCardNode* cHead;
	int month;
	int year;
	expirationNode* prev;
	expirationNode* next;
	expirationNode::expirationNode()
	{}
	
	expirationNode::expirationNode(int m, int y, creditCardNode* c, expirationNode* p,expirationNode* n)
		:month(m), year(y), cHead(c), prev(p), next(n)
	{}


};

class CardList
{
public:
	CardList();
	void insertCard(string creditCardNo, int month, int year); // insert the data from the txt file into the linkedlist
	void displayListChronological (); // display list in the chronological order
	void displayListReverseChronological (); // display list in the reverse chronological order
	void cardsSearch (string creditCardNo); // found the credit card number with respect to the given creditcard number
	void bulkDelete(int month, int year); // delete the nodes smaller than the given month and year
	void deleteAll(); // clear the heap
	bool searchList(string creditCardNo, int month, int year); // check the taken month and year from the txt file is already exists or not
	void printList();
private:
	expirationNode* head;
	expirationNode* tail;

};

#endif
