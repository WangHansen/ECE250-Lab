
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include <iostream>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?

// An array of pointers that keeps a pointer to each node entry in the linked lists.
struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
};

// An array of pointers that keeps the information for each set. This information
// includes the pointers to head and tail of the set as well as an integer that keeps the size of the set.
struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
	int max_set_size;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	int max_size() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets
	
	for( int i = 0; i < n; i++ ){
		nodes[i] = new ll_entry;
		sets[i] = new set_info;

		// std::cout << "address of nodes[" << i << "] is "<< &nodes[i] << std::endl;
		// std::cout << "address of sets[" << i << "] is "<< &sets[i] << std::endl;

		nodes[i]->ptr_to_info = sets[i];
		nodes[i]->content = i;
		nodes[i]->next = nullptr;
		sets[i]->head = nodes[i];
		sets[i]->tail = nodes[i];
		sets[i]->size = 1;
	}
	max_set_size = 0;

}

Disjoint_set::~Disjoint_set() {
	// std::cout << "called delete on the Disjoint_sets" << std::endl;
	// deallocate memory
	for( int i = 0; i < initial_num_sets; i++ ){

		delete sets[i];
		delete nodes[i];

		// std::cout << "deleted sets and nodes[" << i <<"]" <<std::endl;
	}
	delete [] nodes;
	delete [] sets;
}

int Disjoint_set::find_set(int item) const{
	// should it be? 
	return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;

	set_info* large_set = nodes[ni1]->ptr_to_info;
	set_info* small_set = nodes[ni2]->ptr_to_info;

	ll_entry* temp_ptr = small_set->head;
	large_set->tail->next = temp_ptr;
	// iterate through the shorter list and modify the pointers
	while ( temp_ptr!=nullptr ) {
		temp_ptr->ptr_to_info = large_set;
		temp_ptr = temp_ptr->next;
	}

	// do we need to modify anything else?
	large_set->tail = small_set->tail;
	large_set->size += small_set->size;
	max_set_size = large_set->size;

	// delete the set_info entry that no longer exists
	small_set->head = nullptr;
	small_set->tail = nullptr;
	small_set->size = 0;
	small_set = nullptr;
	set_counter--;
}

int Disjoint_set::max_size() const {
	return max_set_size;
}

#endif