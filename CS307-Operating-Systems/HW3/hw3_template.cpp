#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h> 
#include <queue> 
#include <semaphore.h>
using namespace std;

#define NUM_THREADS 10
#define MEMORY_SIZE 150

struct node
{
	int id;
	int size;
};


queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores

int thread_message[NUM_THREADS]; // thread memory information
char  memory[MEMORY_SIZE]; // memory size
int left_memory = MEMORY_SIZE;




void my_malloc(int thread_id, int size)
{
	//This function will add the struct to the queue
	pthread_mutex_lock(&sharedLock);
	node* p = new node();
	p->id = thread_id;
	p->size = size;
	myqueue.push(*p);
	pthread_mutex_unlock(&sharedLock);
	
}

void * server_function(void *)
{
	//This function should grant or decline a thread depending on memory size.
	while(true){
		pthread_mutex_lock(&sharedLock);
		while(!myqueue.empty()){
			node * t = new node();
			t = &myqueue.front();
			if(t->size <= left_memory){
				thread_message[t->id] = MEMORY_SIZE - left_memory;
				left_memory -= t->size;
			}
			else{
				thread_message[t->id] = -1;
			}
			myqueue.pop();
			sem_post(&semlist[t->id]);
		}
		pthread_mutex_unlock(&sharedLock);
	}
}

void * thread_function(void * id) 
{
	//This function will create a random size, and call my_malloc
	//Block
	//Then fill the memory with id's or give an error prompt
	pthread_mutex_lock(&sharedLock);
	int min = 1; 
	int max = MEMORY_SIZE/6;
	int rand_size = rand()%(max)+1;
	int* ptr_id = (int*) id;
	pthread_mutex_unlock(&sharedLock);
	
	my_malloc(*ptr_id, rand_size);
	sem_wait(&semlist[*ptr_id]);
	
	pthread_mutex_lock(&sharedLock);
	if(thread_message[*ptr_id] != -1){
		for(int i = 0; i < rand_size; i++){
			memory[thread_message[*ptr_id]] = *ptr_id + '0';
			thread_message[*ptr_id]++;
		}
	}
	else if(thread_message[*ptr_id] == -1){
		cout << "Thread " << *ptr_id << ": not enough memory!"<< endl;
	}
	pthread_mutex_unlock(&sharedLock);
}

void init()	 
{
	pthread_mutex_lock(&sharedLock);	//lock
	for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
	{	
		sem_init(&semlist[i],0,0);
	}
	for (int i = 0; i < MEMORY_SIZE; i++)	//initialize memory 
  	{
		char zero = '0'; 
		memory[i] = zero;
	}
   	pthread_create(&server,NULL,server_function,NULL); //start server 
	pthread_mutex_unlock(&sharedLock); //unlock
}



void dump_memory() 
{
 // You need to print the whole memory array here.
	pthread_mutex_lock(&sharedLock);
	for(int i = 0; i < MEMORY_SIZE ; i++){
		cout << memory[i];
	}
	cout << endl;
	pthread_mutex_unlock(&sharedLock);
}

int main (int argc, char *argv[])
{

 	//You need to create a thread ID array here
	pthread_t th_array[NUM_THREADS];
	int id_array[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
    {
        id_array[i] = i;
    }
 	init();	// call init
	
	srand(time(NULL));
 	//You need to create threads with using thread ID array, using pthread_create()
	for (int i=0; i < NUM_THREADS; i++){
        pthread_create(&th_array[i],NULL,thread_function,(void *) &id_array[i]);
	}
	
 	//You need to join the threads
	for (int i = 0; i < NUM_THREADS; i++){
		pthread_join(th_array[i], NULL);
	}
 	dump_memory(); // this will print out the memory
 	
 	printf("\nMemory Indexes:\n" );
 	for (int i = 0; i < NUM_THREADS; i++)
 	{
 		printf("[%d]" ,thread_message[i]); // this will print out the memory indexes
 	}
 	printf("\nTerminating...\n");
}