// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include<vector>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	// static dynamically allocated array, adjustable at will
	tableSize = 150; // M
	table = new XUser *[tableSize];
	for (int i = 0; i < tableSize; i++){
		table[i]=nullptr;
	}
}

XUser* HashTable::createUser(string username, string userBio)
{
	// creates a new XUser struct instance
	XUser *newUser = new XUser;
	newUser->username = username;
	newUser->userBio = userBio;
	newUser->postCount = 0;
	newUser->next = nullptr;
	newUser->bst = new BST;
	return newUser;
}

unsigned int HashTable::hashFunction(string username)
{
	// create a vector of chars for the username, find the ascii value of each character via casting, then add it to a sum
	int sum = 0;
	vector<char> chars(username.begin(),username.end());
	for (int j = 0; j <int(chars.size()); j++){
		sum += int(chars[j]);
	}	
	return sum % tableSize;
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{
	//1 - check if user already exists with that username
	XUser *user = searchUser(username);
	if (user != nullptr){
		cout << "Username already exists..."<< endl;
		return nullptr;
	}

	//2 - hash the username
	int key = hashFunction(username);

	//3 - create a newUser instance
	XUser *newUser = createUser(username, userBio);

	//4ish if bucket is empty insert ezpz
	if (table[key] == nullptr){
		table[key] = newUser;
		return table[key];
	} 
	
	//4-6 if bucket isn't empty, insert at the head of the linked list and increase collision counter
	else if (table[key] != nullptr){
		numCollision+=1;
		newUser->next = table[key];
		table[key] = newUser;
		return table[key];
	}
	return nullptr;
}

XUser* HashTable::searchUser(string username)
{	
	int key = hashFunction(username);
	XUser *current = nullptr;

	//if bucket exists
	if (table[key]){
		//if bucket position 1 = username return it (only one XUser)
		if (table[key]->username == username){
			return table[key];
		} 
		//if linked list traverse is needed, do it until finding the username, if not found then it doesn't exist
		else if (table[key]->username != username){
			current = table[key];
			while (current != nullptr && current->username != username && current->next != nullptr){
				current = current->next;
			}
			if (current->username == username){
				return current;
			} else {
				return nullptr;
			}
		}
	}
	else {
		return nullptr;
	}
	current = nullptr;
	return nullptr;
}

void HashTable::printUsers()
{
	XUser *current = nullptr;
	// iterates through table and prints username if bucket isnt empty/ cout formatting
	for (int i = 0; i< tableSize; i++){
		if (table[i] != nullptr){
			current = table[i];
			cout << i <<  "|" << current->username;
			while (current->next != nullptr){
				current = current->next;
				cout <<"-->"<< current->username;
			}
			cout << "--> NULL" << endl;
		} else {
			cout << i << "|" << "NULL"<< endl;
		}
	}
	current = nullptr;
	delete current;
}

void HashTable::printAllPostByUser(string username) 
{
	// finds XUser, then calls ->bst->displayPosts which recursively prints every post from the user in order / formatting
	if (searchUser(username) != nullptr){
		XUser *userFound = 	searchUser(username);
		cout << userFound->username << ":" << endl;
		cout << "Most liked post by: "<< userFound->username<< endl;
		cout << "| userbio: " << userFound->userBio<< endl;
		cout << "| post count: "<< userFound->postCount<< endl;
		cout << "| Post: " << endl;
		userFound->bst->displayPosts();
	} else {
		cout << "User does not exit, try again..." << endl;
	}
}

void HashTable::printMostLikedPost() 
{
	// creates two XUsers, one to iterate with, one with the greatest liked post
	XUser *itr = nullptr;
	XUser *mostLiked = nullptr;
	//itr iterates through every XUser
	for (int i = 0 ; i<tableSize; i++){
		itr = table[i];
		while (itr != nullptr){
			// compares if itr->bst->mostPopular() is greater than the current mostLiked->bst->mostPopular() to check if likes are greater on their most liked post
			if (itr->bst->mostPopular()){
				if (mostLiked == nullptr || mostLiked->bst->mostPopular()->likes < itr->bst->mostPopular()->likes){
					mostLiked = itr;
				}
			}
			if (itr->next != nullptr){
				itr = itr->next;
			} else{
				break;
			}
		}
	}
	cout << "Most liked post by: "<< mostLiked->username<< endl;
	cout << "| userbio: " << mostLiked->userBio<< endl;
	cout << "| post count: "<< mostLiked->postCount<< endl;
	cout << "| Post: " << endl;
	cout << mostLiked->bst->mostPopular()->postedTime<< ":" << endl;
	cout <<"__| likes: "<< mostLiked->bst->mostPopular()->likes<< endl;
	cout <<"__| "<< mostLiked->bst->mostPopular()->xContents<< endl;
}

int HashTable::longestChain() 
{
	// compares newChain against longest, resets newChain with each index of the table
	int longestChain=0;
	int newChain=0;
	XUser *itr = nullptr;
	for (int i = 0; i<tableSize; i++){
		itr = table[i];
		while (itr != nullptr){
			itr = itr->next;
			newChain += 1;
		}
		if (newChain > longestChain){
			longestChain = newChain;
		}
		newChain = 0;
	}
	return longestChain;
}