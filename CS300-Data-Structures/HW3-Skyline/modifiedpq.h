#ifndef MODIFIEDPQ
#define MODIFIEDPQ

#include<iostream>
#include<vector>

using namespace std;

struct Node
{
	int value;
	int label;
	int height;
	bool right;
	Node(){}
	Node(int v, int l, int h, bool r){
		value = v;
		label = l;
		height = h;
		right = r;
	}
	bool operator>(const Node & rhs){ 
        return (value > rhs.value) || ((value == rhs.value) && right == true && rhs.right == false) || ((value == rhs.value) && (right == rhs.right) && (height < rhs.height));
    }
};


template<class Comparable>
class modifiedpq
{
public:
	modifiedpq(){}
	~modifiedpq(){}

	modifiedpq(int size){
		current_size = 0;
		heap.resize(size);
		location.resize(size);
	}
	void insert(Comparable value, int label){  
        
        Heapnode node(value, label);  // node to be inserted in the heap vector
        int hole = ++current_size; // index
		//percolate up
        for( ; hole > 1 && value > heap[hole / 2].height; hole /= 2){
            heap[hole] = heap[hole / 2];  
            location[heap[hole/2].label] = hole; 
        }
        heap[hole] = node;  
        location[label] = hole; 
    }

	Comparable Remove(int label){ // for a given label it will remove and reorganize vector
		Comparable t = heap[location[label]].height;
		heap[location[label]] = heap[current_size--];  
        location[heap[location[label]].label] = location[label];  
        percDown(location[label]);  //reorganize heap order
        return t;
	}
	Comparable GetMax(){ 
        return heap[1].height;
    }
	bool isEmpty() const{
        return current_size == 0;
    }

private:
	struct Heapnode
	{
		int label;
		Comparable height;
		Heapnode(){}
        Heapnode(Comparable a, int b){
            height = a;
            label = b;
        }
        bool operator>(const Heapnode & rhs){
            return height > rhs.height;
        }
	};
	int current_size;
	vector<Heapnode> heap;
	vector<int> location;
	void percDown(int hole){
		int child;
        Heapnode temp = heap[hole];
        
        for( ; hole * 2 <= current_size; hole = child ){
            child = hole * 2;
            if (child != current_size && heap[child + 1] > heap[child]){
            child++;
            }
            if (heap[child] > temp){
                heap[hole] = heap[child];   
                location[heap[child].label] = hole;   
            }
            else
                break;
        }
        heap[hole] = temp;   
        location[temp.label] = hole; 
    }

};
void merge(vector<Node> & buildings,int start, int mid, int end) {

    int left_size, right_size;
    left_size = mid - start + 1; 
    right_size = end - mid;   
    vector<Node> left(left_size), right(right_size);   
    
    for(int i=0; i < left_size; i++) {  //put left side in the buildings to left vector
        left[i] = buildings[start+i];
    }
    
    for(int i = 0; i < right_size; i++) {   // put right side in the buildings to right vector
        right[i] = buildings[mid+i+1];
    }
    
    int x=0, y=0, i;
    for(i = start; x < left_size && y < right_size; i++) {
        if(right[y] > left[x]) {
            buildings[i] = left[x++];  //if left one is smaller than right one first object put the left one first object into a buildings and increment the lef pointer
        }
        else {
            buildings[i] = right[y++];   
        }
    }

    while(x < left_size) {   //put the remainder of left into buildings
        buildings[i++] = left[x++];
    }

    while(y < right_size) {   // out the remander of the right into buildings
        buildings[i++] = right[y++];
    }
}

void mergesort(vector<Node> & A,int start,int end) {
    int mid;
    if(start<end)  //until the size of the partition is 1
    {
        mid=(start+end)/2;
        mergesort(A,start,mid);   //for left side of the vector
        mergesort(A,mid+1,end);  // again for left side 
        merge(A,start,mid,end);  // merge them into a increasing order in the vector
    }
}

void sort(vector<Node> & objects){ // it will call the merge sort
    mergesort(objects, 0, objects.size() - 1);
}

void print(modifiedpq<int> & skyline, vector<Node> & objects){
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].right == false) {   // left side
            if (i == 0 && objects[i].value != 0) {  // no building at 0 cooridnate
                cout << "0 0" << endl;
                 cout << objects[i].value << " " << objects[i].height << endl;
            }
            else if (i == 0) { // buildigt at 0 coordinate  
                cout << objects[i].value << " " << objects[i].height << endl;
            }
            else if (skyline.isEmpty() || skyline.GetMax() < objects[i].height) {  
                cout << objects[i].value << " " << objects[i].height << endl;
            }
            skyline.insert(objects[i].height, objects[i].label);   
        }
        
        else{  

			int max = skyline.GetMax();  
            skyline.Remove(objects[i].label);
            while (i != objects.size()-1 && objects[i+1].right == true && objects[i+1].value == objects[i].value){  // rempve mpdes which has same label at the end of the vector
                skyline.Remove(objects[i+1].label);
                i++;
			}
            if (skyline.isEmpty()) {   
                cout << objects[i].value << " 0" << endl;
            }
            else if (skyline.GetMax() < max) {  // print new max
                cout << objects[i].value << " " << skyline.GetMax() << endl;
            }
        }
    }
}
#endif