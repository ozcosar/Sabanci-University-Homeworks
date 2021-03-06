
#ifndef _INTEGERSET_H
#define _INTEGERSET_H

using namespace std;
class IntegerSet
{
private:
	int *array;
	int size;

public:
	IntegerSet(); // default constructor
	~IntegerSet(); // destructor
	IntegerSet(int); // construct with the size of array
	IntegerSet(const IntegerSet &); // copy constructor
	const IntegerSet& operator=(const IntegerSet &); // assignment operator (=)
	const IntegerSet& operator+=(const IntegerSet &); // += operator
	/*IntegerSet operator+(const IntegerSet&);*/ // + operator
	const IntegerSet& operator+(int); // adds elemenr
	IntegerSet operator*(IntegerSet &); // intersection
	bool operator!=(IntegerSet); // checks arrays are same or not
	bool operator<=(const IntegerSet&rhs); // subset 
	int getSize(); // return size
	int getElement(int); // get element in specified index
	void setElement(int,int); // push element the given index
};
ostream& operator<<(ostream& os, IntegerSet rhs); // for print set
bool operator<=(const int& element, IntegerSet rhs); // given element is in arrya or not
IntegerSet operator+(const IntegerSet&lhs,const IntegerSet& rhs); // union
#endif