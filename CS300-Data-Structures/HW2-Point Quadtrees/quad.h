#ifndef QUAD
#define QUAD

#include <string>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

struct quadNode
{
	int coord_x, coord_y;
	string name;
	quadNode* NW;
	quadNode* NE;
	quadNode* SW;
	quadNode* SE;
};

class Quad
{
public:

	Quad();
	~Quad();
	void insert(int x, int y, string name);
	void search(int x, int y, int rad);
	void pretty_print();
	void set_size(int size_x, int size_y);

private:

	void insert(int &x, int &y, string &name, quadNode* & t)const;
	void search(int x, int y, int rad, quadNode* & t)const;
	void inBoundry(int x, int y, int rad, quadNode* &t)const;
	void makeEmpty(quadNode* &t);
	void pretty_print(quadNode* &t)const;
	void print_vector(); //print founding cities
	quadNode* root;
	int size_x, size_y;
	
};










#endif