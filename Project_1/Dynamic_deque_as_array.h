#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"



class Dynamic_deque_as_array
{

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();

		int *array;
		// the index of the head of the array
		int array_head;
		// the index of the tail of the array
		int array_tail;
		// count how many numbers are in the array
		int count;
		// the capacity of the array
		int array_size;

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
};


Dynamic_deque_as_array::Dynamic_deque_as_array( int n ) {
	int arrSize = (n<1) ? 1: n;
	array = new int[arrSize];
	array_size = arrSize;
	// when initializing, we set head and tail indexs to be -1
	array_head = -1;
	array_tail = -1;
	count = 0;
}
// BTW, my program assumes the regular situation to be head index < tail index



Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	delete [] array;
}





int Dynamic_deque_as_array::size() const {
	return count;
}


int Dynamic_deque_as_array::capacity() const {
	return array_size;
}


bool Dynamic_deque_as_array::empty() const {
	return (size() == 0);
}


int Dynamic_deque_as_array::head() const {
	// if head index is -1, then the array is empty
	if(array_head == -1){
		throw underflow();
	}
	return array[array_head];
}


int Dynamic_deque_as_array::tail() const {
	// if tail index is -1, then the array is empty
	if(array_tail == -1 ){
		throw underflow();
	}
	return array[array_tail];
}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	// first situation: if array is empty
	if(array_head == -1 && array_tail == -1){
		array_head = 0;
		array_tail = 0;
		array[array_head] = obj;
	}else{
		// if array is full
		if(size() == array_size){	
			// create a new array
			int *new_array = new int[array_size*2];
			// if head is to the left of the tail, which means the array is wrapped as a circular array
			// for instance |1|2|3|4|5|6|
			//                   t h
			if(array_head>array_tail){
				int tmp=0;
				// first copy from head to end
				// copy |4|5|6| into the new array
				//       h   end
				for(int i=array_head; i<array_size; i++){
					new_array[tmp] = array[i];
					tmp++;
				}
				// then copy from 0 to tail
				// copy |1|2|3|
				//       0   t
				for(int i=0; i<=array_tail; i++){
					new_array[tmp] = array[i];
					tmp++;
				}
				// reset head and tail index
				array_head = 0;
				array_tail = array_size - 1;
			}else{
				// if head is left to tail, which is normal situation
				// for instance |1|2|3|4|5|6|
				//               h         t
				// then copy the whole array as it is
				for( int i=0; i<array_size; i++ ){
					new_array[i] = array[i];
				}
			}
			delete[] array;
			// point to the new array
			array = new_array;
			// set the capacity
			array_size = array_size*2;
		}
		// add the obj to the head, the queue cannot be full because this condition is checked
		// if the queue is full, it will be extended with double size
		// check if the head index is 0, if yes, then move head to the end of the arry
		array_head = (array_head-1 < 0) ? array_head + array_size - 1 : array_head - 1;
		array[array_head] = obj;
	}
	// since we add an element to array, count increment by 1
	count++;
	return;
}

// enque tail works similar to enque head
void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	// first situation: if array is empty
	if(array_head == -1 && array_tail == -1){
		array_head = 0;
		array_tail = 0;
		array[array_tail] = obj;
	}else{
		// if array is full
		if(size() == array_size){
			int *new_array = new int[array_size*2];
			// if tail is to left of head
			if(array_head>array_tail){
				int tmp=0;
				// copy from head to end
				for(int i=array_head; i<array_size; i++){
					new_array[tmp] = array[i];
					tmp++;
				}
				// copy from 0 to tail
				for(int i=0; i<=array_tail; i++){
					new_array[tmp] = array[i];
					tmp++;
				}
				array_head = 0;
				array_tail = array_size - 1;
			}else{
				// if tail is to the right of head
				// copy as is
				for( int i=0; i<array_size; i++ ){
					new_array[i] = array[i];
				}
			}
			array = new_array;
			array_size = array_size*2;
		}
		// check if the tail is at end, enqueue to the first cell if yes
		array_tail = (array_tail+1 > array_size-1) ? array_tail - array_size + 1 : array_tail + 1;
		array[array_tail] = obj;
	}
	// enqueue an element and count increment
	count++;
	return;
}


int Dynamic_deque_as_array::dequeue_head() {
	int num;	// used to store the element
	// check if the array is empty
	if(array_head == -1 && array_tail == -1){
		throw underflow();
	}else{
		// store the value of this element in num variable
		num = array[array_head];
		// if there is only one element in the array
		if(array_head == array_tail){
			array_head = -1;
			array_tail = -1;
		}else{
			// else check if head is the last element, if yes, move it to the first after enqueue
			array_head = (array_head+1 > array_size - 1) ? array_head - array_size + 1 : array_head + 1;
		}
	}
	// dequeue an element and count decrement
	count--;
	return num;
}

int Dynamic_deque_as_array::dequeue_tail() {
	int num;	// used to store element
	// check if the array is empty
	if(array_head == -1 && array_tail == -1){
		throw underflow();
	}else{
		// store the value of this element in num variable
		num = array[array_tail];
		// if there is only one element in the array
		if(array_head == array_tail){
			array_head = -1;
			array_tail = -1;
		}else{
			// else check if tail is the first element, if yes, move it to the last after enqueue
			array_tail = (array_tail-1 < 0) ? array_tail + array_size - 1 : array_tail - 1;
		}
	}
	// dequeue an element and count decrement
	count--;
	return num;
}


void Dynamic_deque_as_array::clear() {
	// set the head and tail to -1
	array_head = -1;
	array_tail = -1;
	count = 0;
	return;
}

#endif