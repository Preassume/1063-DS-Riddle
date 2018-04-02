////////////////////////////////////////////////////////////////////////////////
//
// Title:            Linked List Priority Queue
// Files:            priority_queue.cpp ,  input_data.txt ,  priority_out.txt
// Semester:         CMPS 1063 Data Structures Spring 2018
//
// Author:           Austin Riddle
// Email:            aweraa29@gmail.com
// Description:
//       This program will accept commands from an input file and arrange them
// in a priority queue.  This program is used with the names of animals, where
// the shortest names have the highest priority, and the longest names have
// the lowest priority.  Names of equal length are prioritized in alphabetical
// order.  It can accept 'push' and 'pop' commands from the input file, with the
// 'push' command being followed by an animal name.  Each time the 'push'
// command is used, the following animal is placed into the queue.  The 'pop'
// command will take an animal off the queue and print it into a text file.
// At the end of the program, all animals still in the queue will be printed.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node{
	string val;
	node *next; //Points to next item
	int len; //Length of the string
	node(){
		val = " ";
		next = NULL;
	}
	node(string v){
		len = v.length();
		val = v;
		next = NULL;
	}
};

/**
* class queue
*     This is an implementation of a priority queue using a linked list to
*     store items
* Methods:
*  - Queue()           : constructor
*  - string pop()      : Takes an item out of the queue. Returns that item
*  - void push()       : Places an item onto the queue
*  - bool empty()      : Checks if the queue is empty
*  - void print()      : Prints all items in queue to an output file
*  - bool pop()        : Takes an item out of the queue
*  - bool shouldSwap() : Compares two strings to check alphabetical order
*  - void sort()       : Sorts the queue
*/
class queue{
private:
	node *front;
	node *rear;

public:
    //Constructor
	queue(){
		front = rear = NULL;
	}

	/**
    * Function pop:
    *      Takes an item out of the queue. Returns that item
    *
    * Params:
    *      None
    * Returns
    *      string
    */
	string pop(){
		if (!empty()){
			node *temp = front; //Temporary node
			string v = temp->val;
			front = front->next; //Moves the front node into correct position
			delete temp; //Deletes the temporary node
			return v;
		}
		else{ //Displays error if the queue is empty
			cout << "error: cannot pop off empty queue.\n";
			return " ";
		}
	}

	/**
    * Function push:
    *      Places an item onto the queue
    *
    * Params:
    *      [string] v - the string being placed onto the queue
    * Returns
    *      void
    */
	void push(string v){
		node *n = new node(v);

		if(empty()){
			front = n;
			rear = n;
		}
		else{
			rear->next = n;
			rear = n;
		}
		sort(); //Calls sort method to ensure correct order in queue
	}

	/**
    * Function empty:
    *      Checks to see if the queue is empty
    *
    * Params:
    *      None
    * Returns
    *      bool
    */
	bool empty(){
		return (front == NULL);
	}

	/**
    * Function print:
    *      Prints everything in the queue to the output file
    *
    * Params:
    *      [ofstream] &ofile - an output file passed by reference
    * Returns
    *      void
    */
	void print(ofstream &ofile){
		node *temp = front;
		while(temp){ //Loops through the whole queue
			ofile << temp->val << '\n'; //Prints out the string value of item
			temp = temp->next;
		}
		ofile << '\n';
		delete temp; //Deletes the temporary node
	}

	/**
    * Function pop:
    *      Another pop method. Removes an item from the queue, and places
    *      it into a string passed by reference.
    *
    * Params:
    *      [string] &v - a string passed in by reference
    * Returns
    *      bool
    */
	bool pop(string &v){
		if(!empty()){
			node *temp = front;
			string t = temp->val;
			front = front->next;
			delete temp;
			v = t;
			return true; //The pop was successful
		}
		else{ //Prints this error if the queue is empty
			cout << "error: cannot pop off empty queue.\n";
			return false; //Returns falls to tell that the pop failed
		}
	}

	/**
    * Function shouldSwap:
    *      Compares two strings to see what order they should be in
    *      based on alphabetical order.  Determines if they should
    *      be swapped or not.
    *
    * Params:
    *      [int] len  - the length of the strings
    *      [string] a - the first string
    *      [string] b - the second string
    * Returns
    *      bool
    */
	bool shouldSwap(int len, string a, string b){
		for(int i = 0; i < len; i++){ //Can compare every letter in the two strings
			if(*(a.begin() + i) > *(b.begin() + i)){
				return true;
			}
			else if(*(a.begin() + i) < *(b.begin() + i))
				return false;
		}
		return false; //Returns false here if all letters in strings were equal
	}

	/**
    * Function sort:
    *      Sorts the queue. The queue is sorted by length, while
    *      strings of equal length are sorted in alphabetical order.
    *
    * Params:
    *      None
    * Returns
    *      void
    */
	void sort(){
        //Initializes two temporary nodes to use for comparison
		node *n1 = front;
		node *n2 = front;

		//A string and integer used for swapping
		string tempS;
		int tempI;

		n2 = n2->next;

		while(n1){
			n2 = n1->next;
			while(n2){
				if(n1->len > n2->len){
                    //Swaps the string values of the items
					tempS = n1->val;
					n1->val = n2->val;
					n2->val = tempS;

					//Swaps the length values of the items
					tempI = n1->len;
					n1->len = n2->len;
					n2->len = tempI;
				}
				//Sorts strings of equal length alphabetically
				else if(n1->len == n2->len){
					if(shouldSwap(n1->len, n1->val, n2->val)){
                        //Swaps the string values of the items
						tempS = n1->val;
						n1->val = n2->val;
						n2->val = tempS;

                        //Swaps the length values of the items
						tempI = n1->len;
						n1->len = n2->len;
						n2->len = tempI;
					}
				}
				n2 = n2->next;
			}
			n1 = n1->next;
		}
    //Deletes the temporary nodes
    delete n1;
	delete n2;
	}
};

int main(){
	ifstream ifile;
	ifile.open("input_data.txt");
	ofstream ofile;
	ofile.open("priority_out.txt");

	queue Q;

	string animal;
	string command;

	do{
		ifile >> command; //Grabs the next command
		if(command == "push"){
			ifile >> animal; //Gets the animal
			Q.push(animal); //Places the animal on the queue
		}
		else if(command == "pop"){
			if(!Q.empty()){
				Q.pop(animal); //Gets an animal from the queue
				ofile << animal << '\n'; //Prints it to the output file
			}
			else
				Q.pop(animal); //This will display an error message
		}
		else{
			ofile << "error: invalid command from file.\n";
			break;
		}
	}while(!ifile.eof()); //Runs until everything in the input file has been done

	if(!Q.empty()){
		ofile << "\n\nAnimals Remaining on the Queue (in order of priority):\n\n";
		Q.print(ofile); //Prints remaining animals on queue
	}
	else{
		ofile << "\n\nThere are no more animals on the queue.\n\n";
	}
}
