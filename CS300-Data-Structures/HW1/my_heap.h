#ifndef MY_HEAP
#define MY_HEAP
#define MAX_CAPACITY 512
struct memory_block
{
	memory_block* right;
	memory_block* left;
	bool used;
	int size;
	int starting_address;
};


class My_heap
{
public:
	My_heap();
	~My_heap();
	memory_block* bump_allocate(int num_bytes);
	memory_block* first_fit_allocate(int num_bytes);
	memory_block* best_fit_allocate(int num_bytes);
	memory_block* first_fit_split_allocate(int num_bytes);
	void deallocate(memory_block* to_delete);
	void print_heap();
	float get_fragmentation();

private:
	memory_block* heap_begin;
	memory_block* blk;
	int used_bytes;

};











#endif 