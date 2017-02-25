/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  h473wang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2016
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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

/* 
Return a pointer to the n-th child. If the children array is empty,
return nullptr; otherwise, just return children[i]. This member function
will never be called with a value outside 0 to 25. (O(1))
*/
Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

/*
The string being searched for is being passed recursively; however, as we go
deeper into the tree, we must have access to the character corresponding to the
depth. You can assume that the characters are all alphabetical, as the Trie
class should have checked for invalid characters. The trie tree is not case
sensitive, so you must map letters to the range 0 to 25. If we are at the end
of the word, the is_terminal member variable will determine the appropriate
return value; otherwise, we need to call member recursively or return false,
as appropriate. You must return the appropriate values in all cases, including: 
when children are null, when the appropriate child pointer is assigned null, 
and otherwise. (O(n)).
*/
bool Trie_node::member( std::string const &str, int depth ) const {

	// -------------------------------------------------------------------------
	// std::cout << "depth: " << depth << " |str.length: " << str.length() << std::endl;
	// -------------------------------------------------------------------------

	int temp_index = (int)str[depth] - (int)'a';

	if( depth == str.length() ){
		if( is_terminal == true )
			return true;
		return false;
	}

	if( children == nullptr || children[temp_index] == nullptr )
		return false;

	return children[temp_index]->member( str, ++depth );
}

/*
	Like member accessor function, we need to recurse into the tree. If we reach a
	node and we are at the end of the word we are attempting to insert, we need
	only check and possibly modify the member variable is_terminal to determine 
	the appropriate return value. If we are not yet at the end of the word, we must
	recurse through the appropriate sub-tree. This may require first assigning an 
	array of 26 pointers to Trie nodes to children in some cases, and it may 
	require assigning a new Trie node to the kth sub-tree of this array. (O(n))
*/
bool Trie_node::insert( std::string const &str, int depth ) {

	if( depth == str.length() ){
		
		// -------------------------------------------------------------------------
		// if( is_terminal )
			// std::cout << "This word exists before insertion!" << std::endl;
		// else
			// std::cout << "This word doesn't exists before insertion!" << std::endl;
		// -------------------------------------------------------------------------

		if( is_terminal == true )
			return false;
		else{
			is_terminal = true;

			// -------------------------------------------------------------------------
			// if( is_terminal )
				// std::cout << "This word exists after insertion!" << std::endl;
			// else
				// std::cout << "This word doesn't exists after insertion!" << std::endl;
			// -------------------------------------------------------------------------

			return true;
		}

	}

	int temp_index = (int)str[depth] - (int)'a';

	if( depth < str.length() ){
	
	// -------------------------------------------------------------------------
	// std::cout << "char: " << (char)(temp_index+97) << " | depth: " << depth << std::endl;
	// if(children != nullptr)
		// std::cout << "The array containing " << str[depth] << " exists!" << std::endl;
	// -------------------------------------------------------------------------

		if( children == nullptr ){
			children = new Trie_node*[CHARACTERS];
			for( int i = 0; i < 26; i++ ){
				children[i] = nullptr;
			}
		}

		if( children[temp_index] == nullptr ){
			children[temp_index] = new Trie_node();
		}

		// -------------------------------------------------------------------------
		// std::cout << "the inserted char: " << (char)(temp_index+97) << std::endl;
		// -------------------------------------------------------------------------
		
	}
	
	return children[temp_index]->insert( str, ++depth );
}

/* 
Like member accessor function, we need to recurse into the tree. If we reach the
end of branch of the tree before we get to the end of the word, it is clear the
word is not stored in this tree and thus cannot be erased. If we get to a node when 
we are the end of the word, we must choose the appropriate course of action and the
appropriate return value based on the value of is_terminal. If this node is a leaf
node (children is assigned null), we should delete this node. While we are recursing
back, if the children array became entirely unassigned as a result of our erase, the
current node must also be erased.(O(n))
*/
bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {

	// -------------------------------------------------------------------------
	// std::cout << "depth: " << depth << " |str.length: " << str.length() << std::endl;
	// -------------------------------------------------------------------------

	if( depth == str.length() ){

	// -------------------------------------------------------------------------
	// std::cout << "depth equals strlength" << str.length() << std::endl;
	// std::cout << "is_terminal before delete: " << is_terminal << std::endl;
	// -------------------------------------------------------------------------

		if( is_terminal == false ){
			
			// -------------------------------------------------------------------------
			// std::cout << "this word doesn't exist by not having a terminal" << std::endl;
			// -------------------------------------------------------------------------
			
			return false;
		}else{		
				// -------------------------------------------------------------------------
				// std::cout << "there are other words using this node" << std::endl;
				// -------------------------------------------------------------------------
			
			is_terminal = false;
			// -------------------------------------------------------------------------
			// std::cout << "is_terminal after delete: " << is_terminal << std::endl;
			// -------------------------------------------------------------------------
			return true;
		}
	}

	int temp_index = (int)str[depth] - (int)'a';

	// -----------------------------------------------------------------------------------
	// if( children == nullptr || children[temp_index] == nullptr )
		// std::cout << "stop going down: " << depth << std::endl;
	// -----------------------------------------------------------------------------------

	if( children == nullptr || children[temp_index] == nullptr ){
		// -------------------------------------------------------------------------
		// std::cout << "this word doesn't exist because of the letter doesn't exist" << std::endl;
		// -------------------------------------------------------------------------

		return false;
	}

	// -----------------------------------------------------------------------------------
	// std::cout << "going down with depth: " << depth << std::endl;
	// -----------------------------------------------------------------------------------

	if(!children[temp_index]->erase( str, ++depth , children[temp_index] ))
		return false;

	// -----------------------------------------------------------------------------------
	// std::cout << "going up with depth: " << depth << std::endl;
	// std::cout << "the char being deleted: " << (char)(temp_index+97) << std::endl;
	// std::cout << res << std::endl;
	// -----------------------------------------------------------------------------------

	Trie_node *next_node = children[temp_index];
	if( next_node->children == nullptr && !next_node->is_terminal ){
		delete children[temp_index];
		children[temp_index] = nullptr;				
	}

	bool array_empty = true;
	for( int i = 0; i < 26; i++ ){
		if( children[i] != nullptr )
			array_empty = false;
	}

	// -----------------------------------------------------------------------------------
	// if( children==nullptr )
		// std::cout << "deleted an array " << std::endl;
	// if(array_empty)
		// std::cout << "array is empty" << std::endl;
	// -----------------------------------------------------------------------------------

	if( array_empty ){
		delete [] children;
		children = nullptr;
	}

	return true;
}

void Trie_node::clear() {
	if( this == nullptr )
		return;
	if( children == nullptr ){
		delete this;
		return;
	}
	for( int i = 0; i < 26; i++ ){
		if( children[i]!=nullptr ){
			children[i]->clear();
			children[i] = nullptr;
		}
	}
	delete [] children;
	children = nullptr;
	delete this;
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif