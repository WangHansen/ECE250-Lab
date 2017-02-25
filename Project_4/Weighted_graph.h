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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n ) {
	if( n < 0 )
		throw illegal_argument();

	graph = new double*[n];
	for( int i = 0; i < n; i++ ) {
    graph[i] = new double[n];
	}

	num_nodes = n;
	num_edges = 0;
}

Weighted_graph::~Weighted_graph() {

	// std::cout << "called destructor on Weighted_graph" << std::endl;

	for( int i = 0; i < num_nodes; i++ ) {
		delete [] graph[i];
	}
	delete [] graph;
}

int Weighted_graph::degree(int u) const {
	if( u > num_nodes-1 || u < 0)
		throw illegal_argument();

	int count = 0;
	for( int i = 0; i < num_nodes; i++ ){
		if( graph[u][i] )
			count++;
	}
	
	return count;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
	if( i < 0 || i > num_nodes-1 || j < 0 || j > num_nodes-1 )
		throw illegal_argument();

	if( i == j )
		return true;

	if( !graph[i][j] )
		return false;

	graph[i][j] = 0;
	graph[j][i] = 0;

	num_edges--;
	return true;
}

void Weighted_graph::clear_edges() {
	for( int i = 0; i < num_nodes; i++ ){
		for( int j = 0; j < num_nodes; j++ ){
			graph[i][j] = 0;
		}	
	}

	num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	if( i < 0 || i > num_nodes-1 || j < 0 || j > num_nodes-1 || d <= 0 )
		throw illegal_argument();

	if( i == j )
		return false;

	//------------------------------------------------------------------
	// std::cout << "insert into graph from " << i << " to " << j << " with distance of " << d << std::endl;
	//------------------------------------------------------------------

	if( !graph[i][j] )
		num_edges++;

	graph[i][j] = d;
	graph[j][i] = d;
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

	// std::cout << "after call the mst" << std::endl;

	Disjoint_set *ds = new Disjoint_set(num_nodes);
	double total_dis = 0;
	// weights is a 2d array where the first column contains distance
	// from i and j which are stored in second and third column respectively
	double weights[num_edges][3];

	int temp_counter = 0;
	for( int i = 0; i < num_nodes; i++ ){
		for( int j = 0; j < num_nodes; j++ ){
			if( graph[i][j] && i < j ){
				// store the distance in first column
				weights[temp_counter][0] = graph[i][j];
				// store the nodes
				weights[temp_counter][1] = i;
				weights[temp_counter][2] = j;
				temp_counter++;
			}
		}
	}

	// std::cout << "------------weight array---------------" << std::endl;
	// for( int i = 0; i < num_edges; i++ ){
	// 	std::cout << weights[i][1] << "---" << weights[i][2] << " : " << weights[i][0] << std::endl;
	// }
	// std::cout << "---------------------------------------" << std::endl;

	int edge_tested = 0;

	for( int k = 0; k < num_edges; k++ ){
		// find the smallest distance every time
		double temp_distance = INF;
		int temp_index = 0;
		for( int i = 0; i < num_edges; i++ ){
			if( weights[i][0] <= temp_distance ){
				temp_distance = weights[i][0];
				temp_index = i;
			}
		}

		// std::cout << "smallest distance " << weights[temp_index][0] << " from " << weights[temp_index][1] << " to " << weights[temp_index][2] << std::endl;

		if( ds->find_set((int)weights[temp_index][1])!=ds->find_set((int)weights[temp_index][2]) ){
			// std::cout << "union_sets----" << std::endl;
			ds->union_sets((int)weights[temp_index][1], (int)weights[temp_index][2]);
			total_dis += weights[temp_index][0];
		}
		weights[temp_index][0] = INF;

		// std::cout << "number of sets: " << ds->num_sets() << std::endl;

		edge_tested++;

		if( ds->max_size() == num_nodes )
			break;

	}

	delete ds;
	return std::pair<double, int>( total_dis, edge_tested );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif