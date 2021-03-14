#include "quad.h"
vector<string> visitedCities; 
vector<string> citiesIncircle;

bool found = false;

Quad::Quad()
{
	root = nullptr;
}

void Quad::insert(int x, int y, string name){
	insert(x,y,name,root);
}

void Quad::set_size(int sizex, int sizey){ // set the boundries
	size_x = sizex;
	size_y = sizey;
}

void Quad::insert(int &x, int &y, string &name, quadNode* &ptr)const{
	if (size_x >= x && size_y >= y)
	{
		if (ptr == nullptr)
		{
			ptr = new quadNode();
			ptr->coord_x = x;
			ptr->coord_y = y;
			ptr->name = name;
			ptr->NE = nullptr;
			ptr->NW = nullptr;
			ptr->SE = nullptr;
			ptr->SW= nullptr;
		}
		else if (x == ptr->coord_x && y == ptr->coord_y)
		{
			;
		}
		else if (x >= ptr->coord_x && y >= ptr->coord_y) // if x and y are bigger, it is in the NE
		{
			insert(x,y,name,ptr->NE);
		}
		else if (x <= ptr->coord_x && y >= ptr->coord_y) // if x smaller and y is bigger, NW
		{
			insert(x,y,name,ptr->NW);
		}
		else if (x >= ptr->coord_x && y <= ptr->coord_y) // if x bigger and y is smaller, SE
		{
			insert(x,y,name,ptr->SE);
		}
		else if (x <= ptr->coord_x && y <= ptr->coord_y) // if x and y is smaller, SW
		{
			insert(x,y,name,ptr->SW);
		}
	}
}
void Quad::inBoundry(int x, int y, int rad, quadNode* &t)const{
	if (t!=nullptr)
	{
		float sub_x = t->coord_x - x;
		float sub_y = t->coord_y - y;
		int sub_1 = (int) pow(sub_x,2);
		int sub_2 = (int) pow(sub_y,2);
		int sub = sqrt(sub_1 + sub_2);
		if (rad <= sub) // checks if in the circle or not
		{
			
			inBoundry(x,y,rad,t->SE);
			inBoundry(x,y,rad,t->SW);
			inBoundry(x,y,rad,t->NE);
			inBoundry(x,y,rad,t->NW);
			
		}
		else
		{
			citiesIncircle.push_back(t->name); // insert cities in the circle
			inBoundry(x,y,rad,t->SE);
			inBoundry(x,y,rad,t->SW);
			inBoundry(x,y,rad,t->NE);
			inBoundry(x,y,rad,t->NW);
		}
	}
}
void Quad::search(int x, int y, int rad){
	inBoundry(x,y,rad,root);
	search(x,y,rad,root);
	print_vector(); 
}
void Quad::search(int x, int y, int rad, quadNode* &t)const{
	if (t!=nullptr)
	{
		visitedCities.push_back(t->name); //insert the visiting cities
		if (t->coord_x < x-rad)
		{
			if (t->coord_y >= y+rad)
			{
				search(x,y,rad,t->SE); // 1
			}
			else if (t->coord_y <= y+rad && t->coord_y >= y-rad)
			{
				search(x,y,rad,t->SE);
				search(x,y,rad,t->NE);//4
			}
			else
			{
				search(x,y,rad,t->NE);//6
			}
		}
		else if (t->coord_x > x+rad)
		{
			if (t->coord_y >= y+rad)
			{
				search(x,y,rad,t->SW);//3
			}
			else if (t->coord_y <= y+rad && t->coord_y >= y-rad)
			{
				search(x,y,rad,t->SW);
				search(x,y,rad,t->NW);//5
			}
			else
			{
				search(x,y,rad,t->NW);//8
			}
		}
		else
		{
			if (t->coord_y <= y-rad)
			{
				search(x,y,rad,t->NE);
				search(x,y,rad,t->NW);//7
			}
			else if (t->coord_y >= y+rad)
			{
				search(x,y,rad,t->SE);
				search(x,y,rad,t->SW);//2
			}
			else
			{
				float sub_x = t->coord_x - x;
				float sub_y = t->coord_y - y;
				int sub_1 = (int) pow(sub_x,2);
				int sub_2 = (int) pow(sub_y,2);
				int sub = sqrt(sub_1 + sub_2);

				if (rad < sub)
				{
					if (t->coord_x < x)
					{
						if (t->coord_y > y)
						{
							search(x,y,rad,t->SE);
							search(x,y,rad,t->SW);
							search(x,y,rad,t->NE);//9
						}
						else
						{
							search(x,y,rad,t->SE);
							search(x,y,rad,t->NE);
							search(x,y,rad,t->NW);//11
						}
					}
					else
					{
						if (t->coord_y > y)
						{
							search(x,y,rad,t->SE);
							search(x,y,rad,t->SW);
							search(x,y,rad,t->NW);//10
						}
						else
						{
							search(x,y,rad,t->SW);
							search(x,y,rad,t->NE);
							search(x,y,rad,t->NW);//12
						}
					}
				}
				else
				{
					search(x,y,rad,t->SE);
					search(x,y,rad,t->SW);
					search(x,y,rad,t->NE);
					search(x,y,rad,t->NW);//13
				}
			}
		}
	}
}
void Quad::print_vector(){
	if (citiesIncircle.size() == 0) // if cities in circle size equal 0, it means there is no city in the circle
	{
		cout << "<None>" << endl;
	}
	else
	{
		for (int i = 0; i < citiesIncircle.size(); i++) // first print the citis in the circle
		{
			cout << citiesIncircle.at(i);
			if (i != citiesIncircle.size()-1) // in order to not to print comma at the end
			{
				cout << ", " ;
			}
		}
		cout << endl;
	}
	citiesIncircle.clear();
	for (int i = 0; i < visitedCities.size(); i++) // second line print the cities visited
	{
		cout << visitedCities.at(i);
		if (i != visitedCities.size()-1)
		{
			cout << ", ";
		}
	}
	visitedCities.clear();
}

void Quad::pretty_print(){
	pretty_print(root);
}

void Quad::pretty_print(quadNode* &t)const{
	if (t!=nullptr)
	{
		cout << t->name << endl;
		pretty_print(t->SE);
		pretty_print(t->SW);
		pretty_print(t->NE);
		pretty_print(t->NW);
	}
}

void Quad::makeEmpty(quadNode* &t){
	if (t != nullptr)
	{
		makeEmpty(t->SE);
		makeEmpty(t->SW);
		makeEmpty(t->NE);
		makeEmpty(t->NW);
		delete t;
	}
	t = nullptr;
}

Quad::~Quad()
{
	makeEmpty(root);
}
