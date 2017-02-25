#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
 * UW User ID:  h473wang
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;				//keep track of the number of bins filled
		int power;				//array_size = 2 to the power of 'power'
		int array_size;		//the capacity of the hash table
		int original_size;
    int mod;
		T *array;
		state *occupied;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		int memberIndex( T const & ) const; 	// return the index of the element if it is in the array, else return -1
		T bin( int ) const;
		int hash( T const & ) const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):power(m),array_size( 1 << power ){		//1<<power get the 2 of the power of power
	array = new T[array_size];															// initialize two arrays
	occupied = new state[array_size];		

	for(int i=0; i<array_size; i++){												// set the state array full of EMPTY
		occupied[i] = EMPTY;
	}

	count = 0;																							// num of element is 0
	original_size = array_size;
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	delete[] array;
	delete[] occupied;
}

template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
  double load_fac = 1.0 * count / array_size; 
	return load_fac;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
	return count==0 ? true : false;
}

template<typename T >
int LinearHashTable<T >::memberIndex( T const &obj ) const {
	int index = ((int)obj % array_size + array_size) % array_size;											// get the value of h(k)

	while(occupied[index]!=EMPTY){ 
	 		if(array[index]==obj && occupied[index]==OCCUPIED)	// check the next bin until an empty bin found
					break;
			index++;
			if(index==array_size)																// if the pointer reaches the end of the array
				index = 0;
	}
	// std::cout << "==index==" << index << std::endl;

	return (array[index]==obj&&occupied[index]==OCCUPIED)?index:-1;
}

template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
  return memberIndex(obj)==-1?false:true;									// check if the value match
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
int LinearHashTable<T >::hash( T const &obj ) const {
	int index = ((int)obj % array_size + array_size) % array_size;

	while(occupied[index]==OCCUPIED){												// find the next available bin
		index++;
		if(index==array_size)																	// if the pointer is at the end of the array, move it up to the first bin
			index = 0;
	}

	return index;
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {

	if(load_factor()>0.75){
		T *old_array = array;
		state *old_occupied = occupied;

		array = new T[array_size*2];														// double the size of the arrays
		occupied = new state[array_size*2];

		array_size = array_size * 2;

		for(int i=0; i<array_size; i++){
			occupied[i] = EMPTY;			
		}

		//rehash
		for(int i=0; i<array_size/2; i++){
			int temp_count = 0;
			if(old_occupied[i]==OCCUPIED){
				int temp_index = hash(old_array[i]);
				array[temp_index] = old_array[i];
				occupied[temp_index] = OCCUPIED;
				temp_count++;
				if(temp_count==count)															// so we dont need to loop whole array
					break;
			}
		}

		delete[] old_array;																		// deallocate the original arrays
		delete[] old_occupied;
	}

	int index = hash(obj);																	// insert the element
	array[index] = obj;
	occupied[index] = OCCUPIED;
	count++;
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {

	if( !member(obj) )																			// if the element is not a memeber
		return false;

	if(load_factor()<=0.25 && original_size!=array_size){
		T *old_array = array;
		state *old_occupied = occupied;

		array = new T[array_size/2];									// shrink the size of the array to half
		occupied = new state[array_size/2];

		array_size = array_size/2;

		for(int i=0; i<array_size; i++){
			occupied[i] = EMPTY;			
		}

		//rehash
		for(int i=0; i<array_size*2; i++){											// move the elements from old array to the new array
			int temp_count = 0;
			if(old_occupied[i]==OCCUPIED){
				int temp_index = hash(old_array[i]);
				// std::cout << "==temp_index==" << temp_index << "==hashed value==" << old_array[i] << std::endl;
				array[temp_index] = old_array[i];
				occupied[temp_index] = OCCUPIED;
				temp_count++;
				if(temp_count==count)																// check if we have moved all the elements, then stop going forward
					break;
			}
		}
		
		delete[] old_array;
		delete[] old_occupied;
	}

	occupied[memberIndex(obj)] = DELETED;										// remove the element from the array
	count--;
	return true;
}

template<typename T >
void LinearHashTable<T >::clear() {
	for(int i=0; i<array_size; i++){
		occupied[i]==EMPTY;
	}
	count = 0;
}

template<typename T >
void LinearHashTable<T >::print() const{
	std::cout<<std::endl;
	for(int i=0; i<array_size; i++){
		std::cout << "| " << occupied[i] << " "; 
	}
	std::cout << "|" << std::endl;
	for(int i=0; i<array_size; i++){
		std::cout << "____" ;
	}	
	std::cout << "_" << std::endl;	
	for(int i=0; i<array_size; i++){
		std::cout << "| " << array[i] << " ";
	}
	std::cout << "|" << std::endl;
}

#endif