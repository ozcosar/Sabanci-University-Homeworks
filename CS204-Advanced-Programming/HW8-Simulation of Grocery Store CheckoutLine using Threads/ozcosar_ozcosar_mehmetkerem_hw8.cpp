#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <time.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include"ozcosar_ozcosar_mehmetkerem_HW8DynIntQueue.h"

using namespace std;

mutex myMutex, coutMutex;
HW8DynIntQueue myQueue;
int treshold, total_number_customer, queue_size, arrival_time, checkout_time, counter;

int random_range(const int& min, const int& max){
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

/*begin:  taken from and changed in lab12*/
void consumer(int min, int max)
{
	for(int i = 1; i <= total_number_customer; i++) //takes customer with respect to total customer size
	{
		arrival_time = random_range(min,max); //create a random arrival time for consumers
		myMutex.lock();
		if (queue_size < total_number_customer) 
		{  
			myQueue.enqueue(i);
			queue_size = myQueue.getCurrentSize();
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"New customer with ID "<< i << " has arrived "<<  " (queue size is " << queue_size << "):  " << put_time(ptm,"%X")<< endl;
			this_thread::sleep_for(chrono::seconds(arrival_time));
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
			i--;
		}
		
	}
}
/*end:  taken from and changed in lab12*/

/*begin:  taken from and changed in lab12*/
void cashier(int consId, int open_second, int min, int max)
{
	
	checkout_time = random_range(min,max); //create random checkout tþme for cashiers
	this_thread::sleep_for(chrono::seconds(checkout_time));
	int item;
	int size1;
	while(counter != total_number_customer) // if counter equal to the total number of customer stop to take customer
	{	
		/*checkout_time = random_range(min,max);
		this_thread::sleep_for(chrono::seconds(checkout_time));*/
		myMutex.lock();
		if (!myQueue.isEmpty()) 
		{  
			myQueue.dequeue(item);
			counter++; //increment 
			size1 = myQueue.getCurrentSize(); // get current size
			myMutex.unlock(); 

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier " << consId <<" started transaction with customer "<< item << " (queue size is " << size1 << "):  " << put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
			
			this_thread::sleep_for(chrono::seconds(checkout_time)); // simulation for consume

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier " << consId <<" finished transaction with customer "<< item << " " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
		}
	}
}
/*end:  taken from and changed in lab12*/

/*begin:  taken from and changed in lab12*/
void cashier2(int consId, int checkout_time, int treshold)
{
	this_thread::sleep_for(chrono::seconds(checkout_time)); //sleep the thread for chechk out time
	int item;
	int size2;
	
	while(counter != total_number_customer) //if counter equal to the total number of customer stop to take customer
	{	
		//this_thread::sleep_for(chrono::seconds(checkout_time));
		myMutex.lock();
		if (!myQueue.isEmpty() && myQueue.getCurrentSize() >= treshold) 
		{  
			myQueue.dequeue(item);
			counter++; //increment
			//queue_size = myQueue.getCurrentSize();
			size2 = myQueue.getCurrentSize();
			myMutex.unlock();
			
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier " << consId <<" started transaction with customer "<< item <<" (queue size is " << size2 << "):  " << put_time(ptm,"%X")<<endl;
			coutMutex.unlock();
			this_thread::sleep_for(chrono::seconds(checkout_time)); // simulation for consume

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier " << consId <<" finished transaction with customer "<< item << " " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
		}
		else
		{
			myMutex.unlock();
		}
	}
}
/*end:  taken from and changed in lab12*/

int main(){
	cout << "Please enter the total number of customers: ";
	cin >> total_number_customer;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> treshold;
	int max_arrival, min_arrival, min_checkout_time, max_checkout_time;
	cout <<"Please enter the inter-arrival time range between two customers:" <<endl;
	cout << "Min: ";
	cin >> min_arrival;
	cout << "Max: ";
	cin >> max_arrival;
	cout << "Please enter the inter-arrival time range between two customers:" << endl;
	cout << "Min: ";
	cin >> min_checkout_time;
	cout << "Max: " ;
	cin >> max_checkout_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << "Simulation starts: " << put_time(ptm,"%X")<<endl;

	thread thr2(consumer,min_arrival,max_arrival);
	thread thr0(cashier,1, treshold, min_checkout_time, max_checkout_time);
	thread thr1(cashier2,2, checkout_time, treshold);
	thr2.join();
	thr0.join();
	thr1.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	localtime_s(ptm, &tt); 
	cout << "End of the simulation ends: " << put_time(ptm,"%X")<<endl;

	
	
	
	

	return 0;
}