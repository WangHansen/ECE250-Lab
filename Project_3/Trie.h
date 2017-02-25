/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;
		
		std::string lower_input( std:: string const & ) const ;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	root_node->clear();
	// delete this;
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	return trie_size == 0;
}

std::string Trie::lower_input( std::string const &str ) const {
	std::string new_str;
	for( int i = 0; i < str.length(); i++ ){
		char temp = std::tolower( str[i] );
		if( (int)temp - (int)'a' < 0 || (int)temp - (int)'a' > 25 )
			throw illegal_argument();
		new_str += temp;
	}
	return new_str;
}

Trie_node *Trie::root() const {
	return root_node;
}

/*
	Return true if the word represented by the string is in the Trie and false otherwise.
	If the string contains any characters other than those of the English	alphabet (‘A’ 
	through ‘Z’ or ‘a’ through ‘z’), throw an illegal_argument exception. (O(n))
*/
bool Trie::member( std::string const &str ) const {
	// -------------------------------------------------------------------------
	// std::cout << "----------" << "Member '" << str << "'----------" << std::endl;
	// -------------------------------------------------------------------------

	return ( root_node == nullptr ) ? false : root_node->member( lower_input( str ) , 0 );
}

bool Trie::insert( std::string const &str ) {
	// -------------------------------------------------------------------------
	// std::cout << "----------" << "Insert '" << str << "'----------" << std::endl;
	// -------------------------------------------------------------------------

	bool res = false;
	if( root_node == nullptr ){
		root_node = new Trie_node();
	}
	if( root_node->insert( lower_input( str ) , 0 ) ){
		trie_size++;
		res = true;
	}
	return res;
}

/*
	Erase the word represented by str from the tree. If the string contains any 
	characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ 
	through ‘z’), throw an illegal_argument exception; otherwise if the string 
	is not in the tree, return false; otherwise, return true (the erase was 
	successful). If the tree is empty, return false, otherwise this function
	calls erase on the root. If the word erased is the last one in the tree, 
	delete the root node. (O(n))
*/
bool Trie::erase( std::string const &str ) {
	// -------------------------------------------------------------------------
	// std::cout << "----------" << "Erase '" << str << "'----------" << std::endl;
	// -------------------------------------------------------------------------
	
	bool res = false;
	if( root_node == nullptr ){
		return false;
	}
	if( root_node->erase( lower_input(str), 0, root_node ) ){
		trie_size--;
		res = true;
	}
	return res;
}


/*
	Delete all the nodes in the tree. Again, if the tree is not empty, it should just
	call clear on the root and set the appropriate member variables. (O(N) where N is
	the number of	words in the tree)
*/
void Trie::clear() {
	if( root_node!=nullptr )
		// for( int i = 0; i < 26; i++ ){
			// if( root_node != nullptr )
				root_node->clear();
		// }
	root_node = nullptr;
	trie_size = 0;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif