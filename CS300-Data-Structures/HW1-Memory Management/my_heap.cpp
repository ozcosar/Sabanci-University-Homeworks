#include "my_heap.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

My_heap::My_heap()
{
	heap_begin = nullptr;
	blk = nullptr;
	used_bytes = 0; 
}

memory_block * My_heap::bump_allocate(int num_bytes){
	if (heap_begin == nullptr && blk == nullptr) //checks list empty or not
	{
		heap_begin = new memory_block();
		used_bytes += num_bytes;
		heap_begin->size = num_bytes;
		heap_begin->used = true;
		heap_begin->starting_address = 0;
		heap_begin->right = nullptr;
		heap_begin->left = nullptr;
		blk = heap_begin;
		return heap_begin;
	}
	else if (used_bytes != MAX_CAPACITY) // if it is not empty end not violate the max capacity create new block
	{
		memory_block* temp = heap_begin;
		while (temp->right != nullptr)
		{
			temp = temp->right;
		}
		memory_block* p = new memory_block();
		temp->right = p;
		p->left = temp;
		p->size = num_bytes;
		p->used = true;
		p->starting_address = used_bytes;
		used_bytes += num_bytes;
		p->right = nullptr;
		blk = p;
		return blk;
	}
	else
	{
		return nullptr;
	}
}

memory_block* My_heap::first_fit_allocate(int num_bytes){
	memory_block* temp = nullptr;
	temp = heap_begin;
	bool found = false;
	while (temp != nullptr && found == false)
	{
		if (temp->used == false && temp->size >= num_bytes) //if block is free and size bigger than num 
		{
			found = true;
			temp->used = true; // turn used
			used_bytes += temp->size; // add num to block size
			return temp;
		}
		temp = temp->right; // go to the right block
	}
	if (used_bytes != MAX_CAPACITY && found == false) // if it cannot found a block create a new block if it is not violate the limit
	{
		return temp = bump_allocate(num_bytes);
	}
	else
	{
		return nullptr;
	}
	
}

memory_block* My_heap::best_fit_allocate(int num_bytes){
	memory_block* temp = nullptr;
	memory_block* p = nullptr;
	temp = heap_begin;
	int min = MAX_CAPACITY;
	bool found = false;
	while (temp != nullptr) // search in list
	{
		if (temp->used == false && temp->size >= num_bytes)
		{
			if (temp->size <= min) // find the nearest size in order to leak little memory
			{
				min = temp->size;
				p = temp;
				found = true;
			}
		}
		temp = temp->right;
	}
	if (found) // if it founds
	{
		p->used = true; //turn used
		used_bytes+=p->size; // add size to he used bytes
		
	}
	else
	{
		p = bump_allocate(num_bytes); // else create new node
	}
	return p;
}

memory_block* My_heap::first_fit_split_allocate(int num_bytes){
	memory_block* temp = nullptr;
	temp = heap_begin;
	bool found = false;
	while (temp != nullptr)
	{
		if (temp->used == false && temp->size >= num_bytes)
		{
			if (num_bytes == temp->size) // if their size equal 
			{
				temp->used = true; // turn used
				found = true;
				return temp;
			}
			else
			{
				found = true;
				int sub = temp->size - num_bytes; //find diffirence of size and num bytes
				temp->size = num_bytes; // put given size to the left
				temp->used = true; // turn used
				used_bytes += num_bytes; // add bytes
				memory_block* new_block = new memory_block(); // vreate new block for remaining bytes
				new_block->right = temp->right;
				if (temp->right == nullptr) // if temp is blk
				{
					temp->right = new_block; 
					new_block->left = temp;
					new_block->size = sub;
					new_block->used = false;
					new_block->starting_address = temp->starting_address + num_bytes;
					blk = new_block; // new_block is new blk
					return blk;
				}
				else
				{
					temp->right->left = new_block;
					temp->right = new_block;
					new_block->left = temp;
					new_block->size = sub;
					new_block->starting_address = temp->starting_address + num_bytes;
					new_block->used = false;
					return temp;
				}
			}
		}
		temp = temp->right;
	}
	if (!found) //cannot find proper block
	{
		temp = bump_allocate(num_bytes); // create new block
		return temp;
	}
	else
	{
		return nullptr;
	}
	
}

float My_heap::get_fragmentation(){
	memory_block* temp = heap_begin;
	int max = 0;
	int sub = 0;
	if (temp == nullptr)
	{
		return 	0.0;
	}
	while (temp!=nullptr)
	{
		sub+=temp->size;
		temp=temp->right;
	}
	float biggest_free_block = MAX_CAPACITY - sub;
	float free_memory = MAX_CAPACITY - used_bytes;
	float fragmentation = ((free_memory - biggest_free_block)/free_memory) * 100.0;
	delete temp;
	return fragmentation;
}

void My_heap::print_heap(){
	int count = 0, free = 0, use = 0;
	memory_block* head = nullptr;
	memory_block* p = heap_begin;
	head = heap_begin;
	while (head != nullptr)
	{
		count++;
		if (head->used == false)
		{
			free++;
		}
		else
		{
			use++;
		}
		head = head->right;
	}
	cout << "Maximum capacity of heap: " << MAX_CAPACITY << "B" << endl;
	cout << "Currently used memory (B): " << used_bytes << endl;
	cout << "Total memory blocks: " << count << endl;
	cout << "Total used memory blocks: " << use << endl;
	cout << "Total free memory blocks: " << free << endl;
	cout << "Fragmentation: "<< get_fragmentation() << endl;
	cout << "------------------------------" << endl;
	if (p != nullptr)
	{
		for (int i = 0; i < count; i++)
		{
			stringstream sstream;
			sstream << hex << p->starting_address;
			string result = sstream.str();

			cout << "Block " << i << "\t\tUsed: " << boolalpha << p->used << "\tSize (B): " << p->size << "\tStarting Address: " << "0x" << result << endl;
			p = p->right;
		}
	}
	cout << "------------------------------" << endl;
	cout << "------------------------------" << endl;
	delete head;
	delete p;
}
My_heap::~My_heap()
{
	memory_block* next;
	cout << "At destruction, the heap had a memory leak of " << used_bytes <<  " bytes" << endl; 
	while (heap_begin != nullptr)
	{
		next = heap_begin->right;
		delete heap_begin;
		heap_begin = next;
	}
	delete heap_begin;
	//delete blk;
	delete next;
}
void My_heap::deallocate(memory_block* to_delete){

	used_bytes -= to_delete->size; //decrement used bytes 

	if (to_delete->right != nullptr && to_delete->right->used == false) // if its right not blk and not used
	{
		to_delete->used = false; // turn free
		to_delete->size += to_delete->right->size; // add size to left one
		if (to_delete->right->right == nullptr) // if its right of right is blk, new blk is to_delete
		{
			memory_block* temp = to_delete->right; 
			to_delete->right = nullptr; 
			blk = to_delete;
			delete temp;
		}
		else
		{
			memory_block* temp = to_delete->right;
			to_delete->right = to_delete->right->right; // connect with to_delete->right to to_delete->right->right
			to_delete->right->right->left = to_delete; //connect the last free node left to to_delete
			delete temp;
		}
	}
	if (to_delete->left != nullptr && to_delete->left->used == false) //check left is null and left is free
	{
		to_delete->used = false;
		to_delete->left->size += to_delete->size;
		if (to_delete->right == nullptr) // right is blk add to_delete to to_delete->left
		{
			memory_block* temp = to_delete;
			to_delete->left->right = nullptr;
			to_delete->left = nullptr;
			blk = to_delete->left; // to_delete->left is new blk
			delete temp;
		}
		else
		{
			to_delete->left->right = to_delete->right;
			to_delete->right->left = to_delete->left;
			delete to_delete;
		}
	}
	else // if there is no free block surroundings 
	{
		to_delete->used = false;
	}
}


