#include "quad.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>

 using namespace std;

 int main(){
	 Quad tree;
	 ifstream cityFile, queryFile;
	 cityFile.open("cities.txt");

	 string line;
	 int size_x, size_y;

	 getline(cityFile, line); //first line has the boundries
	 istringstream iss(line);
	 iss >> size_x >> size_y;
	 tree.set_size(size_x,size_y); // set boundry

	 string name, city_line;
	 int coord_x, coord_y;
	 while (getline(cityFile, city_line)) // other lines have cities name, x and y of cities
	 {
		 istringstream ss(city_line);
		 ss >> name >> coord_x >> coord_y;
		 tree.insert(coord_x,coord_y,name); // insert he city in the tree
	 }
	 tree.pretty_print();
	 cout << endl;

	 queryFile.open("queries.txt");
	 vector<int> queries;
	 string qline;

	 while (getline(queryFile, qline))
	 {
		 istringstream s(qline);
		 string str1, str2, str3;
		 getline(s,str1, ','); // read the line and apart from the comma
		 queries.push_back(stoi(str1)); // take the element before the first comma and turn into int it will be the x coordinates.
		 getline(s,str2, ','); // same for the other elements before the comma , it will be y coordinates
		 queries.push_back(stoi(str2));
		 getline(s,str3, ','); // it will be radius
		 queries.push_back(stoi(str3));
	 }
	 for (int i = 0; i < queries.size(); i+=3) // search given coordinates in the tree
	 {
		 tree.search(queries[i],queries[i+1],queries[i+2]); // take 3 element in the vector, first one is x , second y, third radius, and incremetn i by 3.
		 cout << endl << endl;
	 }

	 return 0;
 }
