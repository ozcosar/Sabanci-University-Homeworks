#include <iostream>
#include <string>
using namespace std;

int Permute(unsigned int num, unsigned int loc1, unsigned int loc2) { 
    unsigned int bit1 =  (num >> loc1) & 1;  // move loc1'th to rightmost side 
    unsigned int bit2 =  (num >> loc2) & 1; // move loc2'th to rightmost side
    unsigned int x = (bit1 ^ bit2); 
    x = (x << loc1) | (x << loc2); // put the xor bit back to their original positions
    unsigned int result = num ^ x; // in order to swap to bits 
	return result;
} 

int main(){
	string source, key;
	unsigned char ch, ck;
	unsigned int num, numk;
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: " ;
	getline(cin,key);
	cout << "Please enter the plaintext to be encrypted: " ;
	while (getline(cin,source)){
		int k = 0;
		if (source.length() != 0){
			cout << "Ciphertext: " ;
		}
		for (int i = 0; i < source.length(); i++){
			ch = source[i];
			if (k >= key.length()){ // if index k exceeds or equal the length of the key move to 0 index
				k = 0; 
			}
			ck = key[k];
			k++;
			num = (int) ch;
			numk = (int) ck;
			num = Permute(num,1,3); //change first and third bits, like 01100010 -> 01101000
			num = Permute(num,0,3); //change 0 and third bits, like 01101000 -> 01100001
			num = Permute(num,2,3); //change second and third bits, like 01100001-> 01100001
			num = Permute(num,5,7); //change fifth and seventh bits, like 01100001 -> 11000001
			num = Permute(num,4,7); //change fourth and seventh bits, like 11000001 -> 01010001
			num = Permute(num,6,7); //change sixth and seventh bits, like 01010001 -> 10010001
			num = num ^ numk; //encryption with key
			cout << hex << (int) num;
		}
		cout << endl;
		cout << endl;
		cout << "Please enter the plaintext to be encrypted: " ;
	}
	return 0;
}
