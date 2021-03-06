#include<iostream>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#include<time.h>

using namespace std;

int mat[2][50] = {0};
int count = 0;
int turn = 1;
bool full = false;

void *airline1(void *){
	
	while(count != 100){
		int seat = rand()%100+1; // takes random int range 1 to 100
		while(turn != 0){}
		if(seat <= 50 && mat[0][seat-1] == 0){ // if seat number is smaller than or equal 50 it means row number of seat is 0. Also checks the seat is full or not.
			cout<<"Agency 1 Entered Critical Region" << endl;
			mat[0][seat-1] = 1; // put 1 to the given seat number
			count++; 
			cout<<"Seat Number "<< seat << " reserved by Agency 1"<< endl;
			cout<<"Agency 1 exit critical region" << endl << endl;	
		}
		else if(seat > 50 && mat[1][seat-51] == 0){ // if seat number is grater than 50 it means row number of seat is 1. Also checks the seat is full or not.
			cout<<"Agency 1 Entered Critical Region" << endl;
			mat[1][seat-51] = 1; // put 1 to the given seat number
			count++;
			cout<<"Seat Number "<< seat << " reserved by Agency 1"<< endl;
			cout<<"Agency 1 exit critical region" << endl << endl;
		}
		if( count == 100 && full == true){ // it can be also checks after the all seats are full in order to one of the agency to cout this statement after the cout full return false
			
			cout<<"Agency 1 Entered Critical Region" << endl;
			cout<<"Agency 1 exit critical region" << endl << endl;
			full = false;
		}
		turn = 1;
	}
	full = true; // after the while turn true because it is full
}

void *airline2(void *){
	
	while(count != 100){
		int seat = rand()%100+1;
		while(turn != 1){}
		if(seat <= 50 && mat[0][seat-1] == 0){
			cout<<"Agency 2 Entered Critical Region" << endl;
			mat[0][seat-1] = 2;
			count++;
			cout<<"Seat Number "<< seat << " reserved by Agency 2"<< endl;
			cout<<"Agency 2 exit critical region" << endl << endl;
		}
		else if(seat > 50 && mat[1][seat-51] == 0){
			cout<<"Agency 2 Entered Critical Region" << endl;
			mat[1][seat-51] = 2;
			count++;
			cout<<"Seat Number "<< seat << " reserved by Agency 2"<< endl;
			cout<<"Agency 2 exit critical region" << endl << endl;
		}
		if(count == 100 && full == true){
			cout<<"Agency 2 Entered Critical Region" << endl;
			cout<<"Agency 2 exit critical region" << endl << endl;
			full = false;
		}
		turn = 0;
	}
	full = true;
}


int main(){
	
	srand(time(NULL));
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, airline1, NULL);
	pthread_create(&thread2, NULL, airline2, NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	if(count == 100){          //checks the plane is full or not
		cout << "No seats left" << endl << endl;
		cout << "Plane is full: " << endl<< endl;
		for(int i = 0; i < 2 ; i++){
			for(int j = 0 ; j < 50 ; j++){
				cout << mat[i][j] << " " ;
			}
		}
	}
	return 0;
}