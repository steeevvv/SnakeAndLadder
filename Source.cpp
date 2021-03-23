#include <iostream>

using namespace std;

#include "Digraph.h"

int main(int argc, const char* argv[]) {

	Digraph<char> chDigraph(9);  
	cout << "Constructing empty Digraph:: \n";
	cout << "The Digraph " << (chDigraph.empty() ? "is" : "is not") << " empty\n";

	cout << "\nAdding Vertices into the Digraph...\n";

	chDigraph.addVertex('A');
	chDigraph.addVertex('B');
	chDigraph.addVertex('C');
	chDigraph.addVertex('D');
	chDigraph.addVertex('E');
	chDigraph.addVertex('F');
	chDigraph.addVertex('G');
	chDigraph.addVertex('H');
	chDigraph.addVertex('I');

	cout << "\nThe Digraph " << (chDigraph.empty() ? "is" : "is not") << " empty\n";

	cout << "\nTry to add repeated vertex ::" << endl;
	chDigraph.addVertex('A');

	chDigraph.insertEdge('A', 'B');
	chDigraph.insertEdge('A', 'D');
	chDigraph.insertEdge('A', 'E');
	chDigraph.insertEdge('B', 'F');
	chDigraph.insertEdge('C', 'B');
	chDigraph.insertEdge('C', 'D');
	chDigraph.insertEdge('D', 'C');
	chDigraph.insertEdge('D', 'H');
	chDigraph.insertEdge('E', 'H');
	chDigraph.insertEdge('F', 'G');
	chDigraph.insertEdge('F', 'I');
	chDigraph.insertEdge('G', 'B');
	chDigraph.insertEdge('G', 'C');
	chDigraph.insertEdge('I', 'H');
	chDigraph.insertEdge('H', 'I');


	cout << "\nTest insert edge for data doen't exist ::" << endl;
	chDigraph.insertEdge('p', 'H');
	cout << "\nTest insert edge when there is edge already exist ::" << endl;
	chDigraph.insertEdge('A', 'B');

	chDigraph.removeEdge('H', 'I');

	cout << "\nTest BreadthFirstSearch starting from A::" << endl;
	chDigraph.BreadthFirstSearch('A', cout);
	cout << "\n\nTest BreadthFirstSearch starting from G ::" << endl;
	chDigraph.BreadthFirstSearch('G', cout);
	cout << "\n\nTest DepthFirstSearch starting from A ::" << endl;
	chDigraph.DepthFirstSearch('A', cout);
	cout << "\n\nTest DepthFirstSearch starting from G ::" << endl;
	chDigraph.DepthFirstSearch('G', cout);
	chDigraph.removeVertex('C');
	cout << "\n\nRepeat traverse after remove vertex C " << endl;
	cout << "Test BreadthFirstSearch starting from A ::" << endl;
	chDigraph.BreadthFirstSearch('A', cout);
	cout << "\n\ntest BreadthFirstSearch starting from G ::" << endl;
	chDigraph.BreadthFirstSearch('G', cout);
	cout << "\n\ntest DepthFirstSearch starting from A ::" << endl;
	chDigraph.DepthFirstSearch('A', cout);
	cout << "\n\nTest DepthFirstSearch starting from G ::" << endl;
	chDigraph.DepthFirstSearch('G', cout);
	cout << endl << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Snake and Ladder" << endl;

	// Board 1
	Digraph<int> Board(100);
	for (int i = 1; i <= 100; i++) {
		Board.addVertex(i);
	}
	for (int i = 1; i <=100; i++) {
		for (int j = 1; j <= 6; j++) {
			if (i + j <= 100)
				Board.insertEdge(i, i + j);
		}
	}

	Board.addLadderorSnake(3,  39);
	Board.addLadderorSnake(10, 12);
	Board.addLadderorSnake(27, 53);
	Board.addLadderorSnake(56, 84);
	Board.addLadderorSnake(69, 99);
	Board.addLadderorSnake(72, 90);

	Board.addLadderorSnake(97, 75);
	Board.addLadderorSnake(66, 52);
	Board.addLadderorSnake(47, 25);
	Board.addLadderorSnake(16, 13);
	Board.addLadderorSnake(63, 60);
	Board.addLadderorSnake(72, 90);
	cout << "Min. Dice Throws of Board 1::  " << Board.getMinDiceThrows() << endl;

	// Board 2 
	Digraph<int> Board2(100);

	for (int i = 0; i < 100; i++) {
		Board2.addVertex(i);
	}

	for (int i = 0; i < 100; i++) {
		for (int j = 1; j <= 6; j++) {
			if(i+j < 100)
				Board2.insertEdge(i, i + j);
		}
	}

	Board2.addLadderorSnake(2,  19);
	Board2.addLadderorSnake(5,  13);
	Board2.addLadderorSnake(10, 27);
	Board2.addLadderorSnake(14, 33);
	Board2.addLadderorSnake(16, 73);
	Board2.addLadderorSnake(21, 36);
	Board2.addLadderorSnake(37, 58);
	Board2.addLadderorSnake(48, 66);
	Board2.addLadderorSnake(56, 75);
	Board2.addLadderorSnake(60, 77);
	Board2.addLadderorSnake(72, 85);
	Board2.addLadderorSnake(80, 97);
	Board2.addLadderorSnake(87, 90);

	Board2.addLadderorSnake(17, 0);
	Board2.addLadderorSnake(7,  3);
	Board2.addLadderorSnake(25, 9);
	Board2.addLadderorSnake(38, 4);
	Board2.addLadderorSnake(59,22);
	Board2.addLadderorSnake(55, 0);
	Board2.addLadderorSnake(53,35);
	Board2.addLadderorSnake(50, 5);
	Board2.addLadderorSnake(89,47);
	Board2.addLadderorSnake(74,27);
	Board2.addLadderorSnake(84,58);
	Board2.addLadderorSnake(82,44);
	Board2.addLadderorSnake(98,62);
	Board2.addLadderorSnake(96,86);
	Board2.addLadderorSnake(91, 2);
	cout << "Min. Dice Throws of Board 2::  " << Board2.getMinDiceThrows() << endl;
	

}
