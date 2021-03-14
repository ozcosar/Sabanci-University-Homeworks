

#include <iostream>
#include "ozcosar_ozcosar_mehmetkerem_hw5_IntegerSet.h"

using namespace std;

//constructor
IntegerSet::IntegerSet()
{
	size = 0;
	array = NULL;
}

// constructor with array size
IntegerSet::IntegerSet(int arraysize)
{
	if (arraysize < 0)
	{
		size = 0;
		array = NULL;
	}
	else
	{
		array = new int[arraysize];
		size = arraysize;
		for (int i = 0; i < size; i++)
		{
			array[i] = i;
		}
	}
}

// destructor
IntegerSet::~IntegerSet()
{
	size = 0;
	delete[] array;
}
/* BEGIN : taken from mathvector.cpp */
// copy constructor
IntegerSet::IntegerSet(const IntegerSet & copy)
{
	size = copy.size;
	array = new int[size]; // deep copy

	for(int i = 0; i < size; i++)
	{
		array[i] = copy.array[i];
	}
}
/* END : taken from mathvector.cpp */

/* BEGIN: taken from mathvector.cpp */
// assignment operator
const IntegerSet& IntegerSet::operator=(const IntegerSet & rhs)
{
	if (this != &rhs) // if they are not already equal
	{
		// first delete left hand side
		size = 0;
		delete[] array;

		// create new array for left hand side
		size = rhs.size;
		array = new int[size];

		for(int i = 0; i < size; i++)
		{
			array[i] = rhs.array[i]; // assign content
		}
	}

	return *this;
}
/* END : taken from mathvector.cpp */

// += operator
const IntegerSet& IntegerSet::operator+=(const IntegerSet & rhs)
{
	int count = 0;
	/*Find the number of common elements in two arrays*/
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < rhs.size; j++)
		{
			if (array[i] == rhs.array[j])
			{
				count++;
			}
		}
	}
	int newSize = size+rhs.size-count; // create new size with respect to number of common elements
	IntegerSet result(newSize); 
	int k = size; // keep the lhs size
	for (int i = 0; i < size; i++) // copy to all lhs element in result
	{
		result.array[i] = array[i]; 
	}
	/*Search for the common elements in the rhs and results arrays*/
	for (int j = 0; j < rhs.size; j++) 
	{
		bool duplicate = false;
		for (int x = 0; x < newSize; x++)
		{
			if (rhs.array[j] == result.array[x])
			{
				duplicate = true; // if it finds turn true the bool variable
			}
		}
		if (!duplicate) // if it does not find move element in the rhs to the result array
		{
			result.array[k] = rhs.array[j]; // push new elemt in the size index of lhs 
			k++; // increment the index
		}
	}
	*this = result; // change current one with result because my current is equal to result
	return *this; // return result in "this"
}

// add element 
const IntegerSet& IntegerSet::operator+(int element){
	int *temp = array;
	if(array == NULL)
	{
		array = new int[++size]; // create a node with keeping the size in the memory
		array[size-1] = element; // push element in the index of size-1
		for (int i = 0; i < size-1; i++)
		{
			array[i] = temp[i]; // move element in the temp to the array
		}
		delete [] temp; // for memory
	}
	else
	{
		int count = 0;
		/*Finds the given element has already in the array or not*/
		for (int i = 0; i < size; i++)
		{
			if (array[i] == element) 
			{
				count++; // increment counts if it finds
			}
		}
		/*If there given element has not already in the array, push that element into the array*/
		if (count == 0) 
		{
			array = new int[++size];
			array[size-1] = element;
			for (int i = 0; i < size-1; i++)
			{
				array[i] = temp[i];
			}
			delete [] temp;
		}
	}
	return *this;
}

//Intersection
IntegerSet IntegerSet::operator*(IntegerSet& rhs){

	IntegerSet result;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < rhs.size; j++)
		{
			if (array[i] == rhs.array[j]) // find the common elements and push the new array
			{
				result = result + array[i];
			}
		}
	}
	return result;
}

bool IntegerSet::operator!=(IntegerSet rhs){
	if (size != rhs.size) // their sizes are not equal they cannot be equal to each other
	{
		return true;
	}
	else
	{
		//Search same elements in arrays
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (array[i] == rhs.array[j])
				{
					return false;
				}
			}
		}
	}
	return false;
}

//Subset
bool IntegerSet::operator<=(const IntegerSet&rhs){
	//Search common elements in arrays
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < rhs.size; j++)
		{
			if (array[i] == rhs.array[j])
			{
				return true;
			}
		}
	}
	return false;
}

int IntegerSet::getSize(){

	return size;
}

int IntegerSet::getElement(int index){

	return array[index];
}
void IntegerSet::setElement(int index, int element){
	array[index] = element;
}

bool operator<=(const int& element, IntegerSet rhs){
	// search for the given element is in the list or not, if it in arrya return true
	for (int i = 0; i < rhs.getSize(); i++)
	{
		if (element == rhs.getElement(i))
		{
			return true;
		}
	}
	return false;
}
ostream& operator<<(ostream& os, IntegerSet rhs){
	
	if (rhs.getSize() == 0)
	{
		os << "{}" ;
	}
	else
	{
		cout << "{" ;
		for (int i = 0; i < rhs.getSize()-1; i++)
		{
			os << rhs.getElement(i) << ", ";
		}
		os << rhs.getElement(rhs.getSize()-1) << "}";
		
	}
	return os;
}
// Union operator
IntegerSet operator+(const IntegerSet& lhs, const IntegerSet& rhs){
	int count = 0;
	IntegerSet lhs_res(lhs); // copy of lhs
	IntegerSet rhs_res(rhs); // copy of rhs
	// Find same element in lhs and rhs, increment count
	for (int i = 0; i < lhs_res.getSize(); i++)
	{
		for (int j = 0; j < rhs_res.getSize(); j++)
		{
			if (lhs_res.getElement(i) == rhs_res.getElement(j))
			{
				count++;
			}
		}
	}
	int newSize = lhs_res.getSize()+rhs_res.getSize()-count; // set a new size for result with respect to count in other words subtract the number of same elements in arrays' size
	IntegerSet result(newSize);
	int k = lhs_res.getSize(); // keep the lhs's size
	for (int i = 0; i < lhs_res.getSize(); i++) // push lhs' elements into the result
	{
		result.setElement(i,lhs_res.getElement(i));  
	}
	// Search for the same elements in rhs and result
	for (int j = 0; j < rhs_res.getSize(); j++)
	{
		bool duplicate = false;
		for (int x = 0; x < newSize; x++)
		{
			if (rhs_res.getElement(j) == result.getElement(x)) // taken rhs' element has already inside the result
			{
				duplicate = true;								// turn true, it means there is a same element in result
				if (rhs_res.getElement(j) == result.getElement(k)) // also check the taken element is the same with the k, k = lhs_res.getSize()
				{
					k++; // if founding element and the kth index element same increment the k, because kth index already with fill the element so move 
						// next index in order to push new item
				}
			}
		}
		if (!duplicate) 
		{
			result.setElement(k,rhs_res.getElement(j)); // push neew elemrnt in array
			k++; // increment index
		}
	}
	return result;
}
