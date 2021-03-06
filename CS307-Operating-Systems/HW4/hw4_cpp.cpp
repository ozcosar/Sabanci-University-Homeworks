#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
	ifstream input;
	input.open("loremipsum.txt");
	char ch;
	int count;
	while(input.get(ch)){
		if(ch == 'a'){
			count++;
		}
	}
	if(!(input.is_open())){
		cout << "olmadı amk" << endl;
	}
	cout << count << endl;
	
	return 0;
}