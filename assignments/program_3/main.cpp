/////////////////////////////////////////////////////////////////
// ProgramName: Program-3
// Author: Austin Riddle
// Description:
// 		This program reads in animals from a text file called
// animals.txt.  It places the animals into a doubly linked list
// where the head and tail are connected.  The program will then
// eliminate a given number of animals from the list using an
// algorithm to determine the order of who will be eliminated.
// The algorithm uses a multiplier, which you will also input.
// The program will only print every 11th eliminated animals.
// The final printed animal is the winner.
//
// The program seems to struggle when too high a number is
// entered for 'number of times to eliminate'. Recommend 74
// or lower, with a multiplier of 2.
// Unfortunately, I have been unable to determine the cause.
//
// Course: 1063 Data Structures
// Semester: Spring 2018
// Date: 27 04 2018
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node{
	string animal;
	node *next;
	node *prev;
	node(){
		animal = " ";
		next = prev = NULL;
	}
	node(string a){
		animal = a;
		next = prev = NULL;
	}
};

/**
* class list
*     This is an implementation of a doubly linked list to store
* 	  and remove animals
* Methods:
*  - list()              : Constructor
*  - bool empty()        : Checks to see if the list is empty
*  - string evenTraverse : Moves "current" node to the right
*  - string oddTraverse  : Moves "current" node to the left
*  - string eliminate()  : Takes an item out of the list. Returns that item
*  - void ins_rear()     : Places an item onto the rear of the list
*  - void print()        : Prints all items in list to an output file
*/
class list{
private:
	node *head;
	node *tail;
	node *current;

public:
    //Constructor
	list(){
		head = tail = current = NULL;
	}

	/**
    * Function empty:
    *      Checks to see if the list is empty
    * Params:
    *      None
    * Returns
    *      bool
    */
	bool empty(){
		return (head == NULL);
	}
	
	/**
    * Function eliminate:
    *      Moves the "current" node to the right m times. Eliminates
	* 	   animal at that location, and returns it.
    * Params:
    *      [int] m - The ammount that "current" will be moved
    * Returns
    *      string
    */
	string evenTraverse(int m){
		int count = 0;
		
		while(count <= m){
			current = current->next;
			count++;
		}
		return eliminate();
	}
	
	/**
    * Function eliminate:
    *      Moves the "current" node to the left m times. Eliminates
	* 	   animal at that location, and returns it.
    * Params:
    *      [int] m - The ammount that "current" will be moved
    * Returns
    *      string
    */
	string oddTraverse(int m){
		int count = 0;
		
		while(count <= m){
			current = current->prev;
			count++;
		}
		return eliminate();
	}
	
	/**
    * Function eliminate:
    *      Removes an animal from the list at the position of
	* 	   the node "current". Returns that animal
    * Params:
    *      None
    * Returns
    *      string
    */
	string eliminate(){
		if (!empty()){
			if(current != tail && current != head){
				node *temp = current;
				string a = temp->animal;
				current = temp->next;
				
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				
				delete temp; //Deletes the node
				return a;
			}
			else if(current == tail){
				node *temp = current;
				string a = temp->animal;
				current = temp->next;
				tail = tail->prev;
				delete temp;
				return a;
			}
			else if(current == head){
				node *temp = current;
				string a = temp->animal;
				current = temp->next;
				head = head->next;
				delete temp;
				return a;
			}
		}
		else{ //Displays error if the list is empty
			cout << "error: nobody to eliminate.\n";
			return " ";
		}
		return " ";
	}
	
	/**
    * Function ins_rear:
    *      Places an item onto the rear of the list
    * Params:
    *      [string] a - the string being placed onto the list
    * Returns
    *      void
    */
	void ins_rear(string a){
		node *temp = new node(a);
		
		//Makes sure that tail and head are connected, so that the list
		//loops around.
		if(empty()){
			head = temp;
			tail = temp;
			tail->next = head;
			current = temp;
			head->prev = tail;
		}
		else{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			head->prev = tail;
			tail->next = head;
			current = head;
		}
	}

	/**
    * Function print:
    *      Prints everything in the list to the output file
    * Params:
    *      [ofstream] &ofile - an output file passed by reference
    * Returns
    *      void
    */
	void print(ofstream &ofile){
		node *temp = head;
		while(temp != tail){ //Loops through the whole list
			ofile << temp->animal << '\n'; //Prints out the string value of item
			temp = temp->next;
		}
		delete temp; //Deletes the temporary node
	}
};

int main(){
	ifstream ifile;
	ifile.open("animals.txt");
	ofstream ofile;
	ofile.open("eliminated.txt");
	
	ofile << "/////////////////////////////////////////////////////////////////"
		<< "\n// ProgramName: Program-3\n"
		<< "// Author: Austin Riddle\n"
		<< "// Description:\n"
		<< "// 		This program reads in animals from a text file called\n"
		<< "// animals.txt.  It places the animals into a doubly linked list\n"
		<< "// where the head and tail are connected.  The program will then\n"
		<< "// eliminate a given number of animals from the list using an\n"
		<< "// algorithm to determine the order of who will be eliminated.\n"
		<< "// The algorithm uses a multiplier, which you will also input.\n"
		<< "// The program will only print every 11th eliminated animals.\n"
		<< "// The final printed animal is the winner.\n"
		<< "//\n"
		<< "// The program seems to struggle when too high a number is\n"
		<< "// entered for 'number of times to eliminate'. Recommend 74\n"
		<< "// or lower, with a multiplier of 2.\n"
		<< "// Unfortunately, I have been unable to determine the cause.\n"
		<< "//\n"
		<< "// Course: 1063 Data Structures\n"
		<< "// Semester: Spring 2018\n"
		<< "// Date: 27 04 2018\n"
		<< "/////////////////////////////////////////////////////////////////"
		<< "\n\nFirst: ";
	
	list A;
	string animal;
	int size = 0;
	
	do{
		ifile >> animal;
		A.ins_rear(animal);
		size++;
	}while(!ifile.eof());
	
	//Resets ifile back to the start
	ifile.clear();
	ifile.seekg(0);
	
	int multiplier, length, eliminations;
	cout << "Please enter a number for use as a multiplier: ";
	cin >> multiplier;
	if(multiplier > 13)
		multiplier = 13;
	else if(multiplier < 1)
		multiplier = 1;
	
	cout << "The multiplier will be " << multiplier << ".\n\n";
	cout << "Please enter how many times you would like to eliminate" <<
		" an animal: ";
	cin >> eliminations;
	cout << eliminations << " animals will be eliminated.\n";
	int count = 1;
	
	for(int i = eliminations; i > 1; i--){
		ifile >> animal; //Gets next animal from ifile
		length = animal.length() * multiplier; //Calculates "m"
		if(count % 11 == 0){ //Prints every 11th eliminated animal
			if(count >= eliminations - 11){
				if(length % 2 == 0)
					ofile << "Winner: " << A.evenTraverse(length) << " !!\n";
				else
					ofile << "Winner: " << A.oddTraverse(length) << " !!\n";
			}
			else{
				if(length % 2 == 0)
					ofile << A.evenTraverse(length) << '\n';
				else
					ofile << A.oddTraverse(length) << '\n';
			}
		}
		else{ //The rest are not printed
			if(length % 2 == 0)
				A.evenTraverse(length);
			else
				A.oddTraverse(length);
		}
		count++;
	}
	ofile << "\n\n";
}
