#include "modifiedpq.h"
#include<fstream>
#include<sstream>

using namespace std;

int main(){
	vector<Node> objects;
	
	ifstream input;
	input.open("input.txt");
	string line;
	getline(input,line);
	istringstream iss(line);
	int num;
	iss >> num; // number of buildings

	int count = 1;
	while (count <= num)
	{
		int xleft,height,xright;
		getline(input,line);
		istringstream ss(line);
		ss >> xleft >> height >> xright;
		Node left(xleft,count,height,false); // put left x in the left node and right variable will be false
		Node right(xright,count,height,true); // put right x in the right node, right variable will be true
		objects.push_back(left);
		objects.push_back(right);
		count++;
	}
	sort(objects); // sort the buildings vector with merge sort algorithm
	modifiedpq<int> skyline(objects.size());
	print(skyline,objects); // print the wanting order
	return 0;
}
