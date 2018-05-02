#include <iostream>
#include <string>
using namespace std;

string toupper(string w){
	for(int i = 0; i < w.length(); i++){
		if((int)w[i] >= 97 && (int)w[i] <= 122){
			w[i] = w[i] - 32;
		}
	}
	return w;
}

string tolower(string w){
	for(int i = 0; i < w.length(); i++){
		if((int)w[i] >= 65 && (int)w[i] <= 90){
			w[i] = w[i] + 32;
		}
	}
	return w;
}


int main()
{
	string w = "This is a string";
	cout << w << '\n';
	w = tolower(w);
	cout << w << '\n';
	w = toupper(w);
	cout << w << '\n';
}
