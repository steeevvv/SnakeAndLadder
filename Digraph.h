//  Snakes and Ladders Problem
//  CSE 331 - Data Structures and Algorithms - Final Project
//  Created by Team 7, Fall 2020.
//  Digraph.h
//
/* Digraph.h contains the declaration of class template Digraph.
 Basic operations:
 Constructor:				Constructs an empty Digraph.
 Destructor:				Destroys a Digraph.
 empty:						Check if a Digraph is empty.
 addVertex:					Insert new Vertex to a created Digraph.
 removeVertex:				Remove an existing Vertex.
 insertEdge:			    Insert an Edge between two Vertices.
 removeEdge:			    Remove an existing Edge between two Vertices.
 BreadthFirstSearch:        Traverse the graph by level from a specified Vertex.
 DepthFirstSearch:			Traverse the graph by depth from a specified Vertex.

 Private utility helper operations:
 search:					Get index of a Vertex from adjacencylists.
 DepthFirstSearchAux:		Recursive function used by DepthFirstSearch.

 Application Operations:
 addLadderorSnake:			Add snake or ladder from a vertex to another.
 getMinDiceThrows:			Calculates minimum dice throws for the application.
 ---------------------------------------------------------------------------*/
#pragma once
#include <iostream>
#include "Queue.h"
using namespace std;

template <typename DataType>
class Digraph {
private:
	/**Private Data Members**/
	class Node {
	public:
		// NODE DATA MEMBERS
		DataType data;
		Node* next;

		// NODE OPERATIONS
		// -Default constrctor: initializes next pointer to 0
		Node() : next(0)
		{}

		// -Explicit-value constructor:  initializes data member to dataValue
		//                               and next pointer to 0
		Node(DataType dataValue)
			: data(dataValue), next(0)
		{}
	}; // end of Node class
	typedef Node* NodePointer;

	class vertex {
		// VERTEX DATA MEMBERS
	public:
		DataType Data;
		NodePointer adjacencylist;		 //first of linked list of a vertex.

		// VERTEX OPERATIONS
		// -Default constrctor: initializes adjacencylist = 0
		vertex() :Data(0), adjacencylist(0)
		{}
	};

	vertex* adjacencylists;		//Array of vertices
	int NumberOfVertex;			//mySize 
	int Mycapacity;				//myCapacity

	/***** Private Function Members *****/
	int search(DataType start) const;
	/*------------------------------------------------------------------------
	 get index of a vertex from adjacencylists

	 Precondition:  graph already exists.
	 Postcondition: returns index of the vertex if found or -1 if not found.
	 ------------------------------------------------------------------------*/

	void DepthFirstSearchAux(DataType start, bool visited[], ostream& out) const;
	/*------------------------------------------------------------------------
	 Recursive depth first search of digraph, starting at vertex start.

	 Precondition:  start is a vertex; visited[i] is false if vertex i has
					not yet been visited, and is true otherwise.
	 Postcondition: visited array is updated.
	 ------------------------------------------------------------------------*/

public:
	/****Function Members*****/
	Digraph(int capacity = 50);
	/*------------------------------------------------------------------------
	 Construct a Digraph object.

	 Precondition:  None.
	 Postcondition: An empty Graph has been constructed.
	 -----------------------------------------------------------------------*/

	~Digraph();
	/*------------------------------------------------------------------------
	 Destructs a Graph object.

	 Precondition:  Digraph lifetime has been over.
	 Postcondition: A Digraph has been destroyed.
	 -----------------------------------------------------------------------*/

	bool empty() const;
	/*------------------------------------------------------------------------
	 Check if Digraph is empty.

	 Precondition:  None.
	 Postcondition: Returns true if Digraph is empty and false otherwise.
	 -----------------------------------------------------------------------*/

	void addVertex(DataType d);
	/*------------------------------------------------------------------------
	 Insert vertex to Digraph.

	 Precondition:  Vertex doesn't exist in the Digraph.
	 Postcondition: Digraph has been modified with inserted vertex if that
					vertex doesn't exist before.
	 -----------------------------------------------------------------------*/

	void removeVertex(DataType  d);
	/*------------------------------------------------------------------------
	 Remove vertex to Digraph.

	 Precondition:  Vertex already exists in the Digraph.
	 Postcondition: Digraph has been modified with deleted vertex if that
					vertex exists.
	 -----------------------------------------------------------------------*/

	void insertEdge(DataType  Start, DataType  end);
	/*------------------------------------------------------------------------
	 Insert Edge between two Vertices in a Digraph.

	 Precondition:  Both Vertices (Start and End) exist in the Digraph,
					and no Edge already exists between them.
	 Postcondition: An Edge has been created between these two Vertices.
	 -----------------------------------------------------------------------*/

	void removeEdge(DataType  Start, DataType  end);
	/*------------------------------------------------------------------------
	 Remove Edge between two vertices in a Digraph.

	 Precondition:  Both Vertices (Start and End) exist in the Digraph,
					and an Edge already exists between them.
	 Postcondition: An Edge has been created between these two vertices.
	 -----------------------------------------------------------------------*/

	void BreadthFirstSearch(DataType start, ostream& out) const;
	/*------------------------------------------------------------------------
	 Breadth first search of digraph (By level), starting at vertex start.

	 Precondition:  Start Vertex already exists, ostream out is open.
	 Postcondition: Digraph has been breadth-first searched from start,
					also traverse across any unvisited vertices left.
	 -----------------------------------------------------------------------*/

	void DepthFirstSearch(DataType start, ostream& out) const;
	/*------------------------------------------------------------------------
	 Depth first search of digraph (By depth), starting at vertex start.
	 using DepthFirstSearchAux recursively.

	 Precondition:  Start Vertex already exists, ostream out is open.
	 Postcondition: Digraph has been Depth-first searched from start,
					also traverse across any unvisited vertices left.
	 -----------------------------------------------------------------------*/

	 /****Application Functions*****/
	void addLadderorSnake(DataType  start, DataType  end);
	/*------------------------------------------------------------------------
	 Add Ladder or Snake between Start and End Vertices.

	 Precondition:  Start and End Vertices already exist.
	 Postcondition: A snake or ladder has been added.
	 -----------------------------------------------------------------------*/

	int getMinDiceThrows();
	/*------------------------------------------------------------------------
	 Calculate the minimum number of dice throws required to reach
	 the destination or last cell from source or 1st cell.

	 Precondition:  A Digraph (Board) Already exists.
	 Postcondition: Number of minimum dice throws.
	 -----------------------------------------------------------------------*/

};

template <typename DataType>
inline Digraph< DataType>::Digraph(int capacity)
	: Mycapacity(capacity), NumberOfVertex(0)
{
	adjacencylists = new (nothrow) vertex[Mycapacity];
	if (adjacencylists == 0) {
		cerr << "error" << endl;
		exit(0);
	}
}

template <typename DataType>
inline Digraph< DataType>::~Digraph() {
	NodePointer tempP, prev;
	for (int i = 1; i < NumberOfVertex; i++) {
		prev = adjacencylists[i].adjacencylist;
		while (prev != 0) {
			tempP = prev->next;
			delete prev;
			prev = tempP;
		}
	}
	delete[] adjacencylists;
}

template <typename DataType>
inline bool Digraph< DataType>::empty() const {
	return NumberOfVertex == 0;
}

template <typename DataType>
int Digraph< DataType>::search(DataType start) const {
	for (int i = 0; i < NumberOfVertex; i++) {
		if (adjacencylists[i].Data == start)
			return i;
	}
	return -1;
}

template <typename DataType>
void Digraph< DataType>::addVertex(DataType d)
{
	if (search(d) != -1) {
		cerr << "Vertex already exists" << endl;
		return;
	}

	if (NumberOfVertex == Mycapacity) {
		cerr << "Digraph is full" << endl;
		return;
	}

	vertex v;
	v.Data = d;
	adjacencylists[NumberOfVertex] = v;
	NumberOfVertex++;
}

template <typename DataType>
void Digraph< DataType>::removeVertex(DataType d)
{
	int index = search(d);
	if (empty()) {
		cerr << "Digraph is empty" << endl;
		return;
	}
	if (index == -1) {
		cerr << "Vertex doesn't exist" << endl;
		return;
	}

	for (int i = 0; i < NumberOfVertex; i++) {
		NodePointer tempP, prev;
		int startindex = -1;
		bool endindex = 0;
		prev = adjacencylists[i].adjacencylist;
		if (prev == 0) {
			break;
		}
		tempP = prev->next;
		if (prev->data == d) {
			prev = adjacencylists[i].adjacencylist;
			adjacencylists[i].adjacencylist = prev->next;
			delete prev;
			break;
		}
		while (tempP != 0) {
			if (tempP->data != d) {
				prev = prev->next;
				tempP = tempP->next;
			}
			else {
				prev->next = tempP->next;
				delete tempP;
				break;
			}
		}
	}
	NodePointer prev = adjacencylists[index].adjacencylist, ptr;
	while (prev != 0) {
		ptr = prev->next;
		delete prev;
		prev = ptr;
	}
	for (int i = index; i < NumberOfVertex; i++) {
		adjacencylists[i].Data = adjacencylists[i + 1].Data;
		adjacencylists[i].adjacencylist = adjacencylists[i + 1].adjacencylist;
	}
	NumberOfVertex--;
}

template <typename DataType>
void Digraph<DataType>::insertEdge(DataType  Start, DataType  end) {
	NodePointer tempP;
	int startindex = -1;
	bool endindex = 0;
	for (int i = 0; i < NumberOfVertex; i++) {
		if (adjacencylists[i].Data == Start)
			startindex = i;
		if (adjacencylists[i].Data == end) {
			endindex = true;
		}
		if (startindex != -1 && endindex == true)
			break;
	}
	if (startindex == -1 || endindex == false) {
		cerr << "These vertices don't exists" << endl;
		return;
	}
	tempP = adjacencylists[startindex].adjacencylist;
	while (tempP != 0) {
		if (tempP->data != end) {
			tempP = tempP->next;
		}
		else {
			cerr << "An edge already exists" << endl;
			return;
		}
	}
	tempP = adjacencylists[startindex].adjacencylist;
	NodePointer ptr = new Node(end);
	if (tempP == 0) {
		adjacencylists[startindex].adjacencylist = ptr;
		return;
	}
	ptr->next = adjacencylists[startindex].adjacencylist;
	adjacencylists[startindex].adjacencylist = ptr;
	return;
}

template <typename DataType>
void Digraph<DataType>::removeEdge(DataType  Start, DataType  end) {
	NodePointer tempP, prev;
	int startindex = -1;
	bool endindex = 0;
	for (int i = 0; i < NumberOfVertex; i++) {
		if (adjacencylists[i].Data == Start)
			startindex = i;
		if (adjacencylists[i].Data == end) {
			endindex = true;
		}
		if (startindex != -1 && endindex == true)
			break;
	}
	if (startindex == -1 || endindex == false) {
		cerr << "These vertices don't exists" << endl;
		return;
	}
	prev = adjacencylists[startindex].adjacencylist;
	if (prev == 0) {
		cerr << "No relatives to this start vertex" << endl;
		return;
	}
	tempP = prev->next;
	if (prev->data == end) {
		prev = adjacencylists[startindex].adjacencylist;
		adjacencylists[startindex].adjacencylist = prev->next;
		delete prev;
		return;
	}
	while (tempP != 0) {
		if (tempP->data != end) {
			prev = prev->next;
			tempP = tempP->next;
		}
		else {
			prev->next = tempP->next;
			delete tempP;
			return;
		}
	}
	cerr << "There is no edge between these vertices" << endl;
	return;
}

template <typename DataType>
void Digraph< DataType>::BreadthFirstSearch(DataType start, ostream& out) const {
	Queue<DataType> Q;
	NodePointer prev;

	bool* visited;
	visited = new (nothrow) bool[NumberOfVertex] {false};
	int i = search(start);
	if (i == -1) {
		cerr << "This vertex is Empty" << endl;
		return;
	}
	Q.enqueue(adjacencylists[i].Data);
	visited[i] = true;
	int counter = 1;
	while (!Q.empty()) {
		prev = adjacencylists[i].adjacencylist;
		out << adjacencylists[i].Data << " ---> ";
		Q.dequeue();
		while (prev != 0) {
			i = search(prev->data);
			if (visited[i] == 0) {
				Q.enqueue(prev->data);
				visited[i] = true;
				counter++;
			}
			prev = prev->next;
		}
		if (Q.empty()) {
			if (counter < NumberOfVertex) {
				for (int j = 0; j < NumberOfVertex; j++) {
					if (visited[j] == false) {
						i = j;
						Q.enqueue(adjacencylists[i].Data);
						visited[i] = true;
						counter++;
						break;
					}
				}
			}
			else
				return;
		}
		else {
			i = search(Q.front());
		}
	}
	delete[] visited;
}

template <typename DataType>
void Digraph< DataType>::DepthFirstSearch(DataType start, ostream& out) const {
	bool* visited;
	visited = new (nothrow) bool[NumberOfVertex] {false};
	if (search(start) == -1) {
		cerr << "This vertex doesn't exist" << endl;
		return;
	}
	DepthFirstSearchAux(start, visited, out);
	for (int i = 0; i < NumberOfVertex; i++) {
		if (visited[i] == 0)
			DepthFirstSearchAux(adjacencylists[i].Data, visited, out);
	}
}

template <typename DataType>
void Digraph<DataType>::DepthFirstSearchAux(DataType start, bool visited[], ostream& out)const {
	out << start << " ---> ";
	int i = search(start);
	visited[i] = true;
	NodePointer ptr = adjacencylists[i].adjacencylist;
	while (ptr != 0) {
		if (visited[search(ptr->data)] == 0) {
			DepthFirstSearchAux(ptr->data, visited, out);
		}
		else {
			ptr = ptr->next;
		}
	}
}

template <typename DataType>
void Digraph<DataType>::addLadderorSnake(DataType start, DataType  end) {
	for (int i = 0; i < NumberOfVertex; i++) {
		NodePointer ptr;
		ptr = adjacencylists[i].adjacencylist;
		while (ptr != 0) {
			if (ptr->data == start)
				ptr->data = end;
			else
				ptr = ptr->next;
		}
		ptr = adjacencylists[i].adjacencylist;
		NodePointer parent = 0;
		bool foundend = false;
		while (ptr != 0) {
			if (ptr->data == end && foundend == false)
				foundend = true;
			else if (ptr->data == end && foundend == true) {
				parent->next = ptr->next;
				delete ptr;
				break;
			}
			parent = ptr;
			ptr = ptr->next;
		}
	}
}

template <typename DataType>
int Digraph< DataType>::getMinDiceThrows() {
	Queue<int> Q;
	NodePointer prev;
	int startindex = 0;
	int end = NumberOfVertex-1;
	int next = 0;

	if (empty()) {
		cerr << "Digraph is empty" << endl;
		return 0;
	}

	bool* visited;
	int* level;
	level = new (nothrow) int[NumberOfVertex] {0};
	visited = new (nothrow) bool[NumberOfVertex] {false};

	Q.enqueue(adjacencylists[startindex].Data);
	visited[startindex] = true;
	level[startindex] = 0;

	while (!Q.empty()) {
		prev = adjacencylists[startindex].adjacencylist;
		Q.dequeue();
		while (prev != 0) {
			if (prev->data == adjacencylists[end].Data) {
				level[end] = level[startindex] + 1;
				return level[end];
			}
			next = search(prev->data);
			if (!visited[next]) {
				Q.enqueue(prev->data);
				visited[next] = true;
				level[next] = level[startindex] + 1;
			}
			prev = prev->next;
		}
		startindex = search(Q.front());
	}
}