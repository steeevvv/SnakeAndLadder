#pragma once
//
//  Queue.hpp
//  LQueue
//
//  Created by Ashraf AbdelRaouf on 11/7/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//
/*-- LQueue.h -------------------------------------------------------------

 This header file defines a Queue data type.
 Basic operations:
 constructor:  Constructs an empty queue
 empty:        Checks if a queue is empty
 enqueue:      Modifies a queue by adding a value at the back
 front:        Accesses the top queue value; leaves queue unchanged
 dequeue:      Modifies queue by removing the value at the front
 display:      Displays all the queue elements
 Note: Execution terminates if memory isn't available for a queue element.
 ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <iostream>
using namespace std;
template <typename QueueElement>

class Queue
{
public:
    /***** Function Members *****/
    /***** Constructors *****/

    Queue();
    /*-----------------------------------------------------------------------
     Construct a Queue object.

     Precondition:  None.
     Postcondition: An empty Queue object has been constructed.
     (myFront and myBack are initialized to null pointers).
     -----------------------------------------------------------------------*/

    Queue(const Queue& original);
    /*-----------------------------------------------------------------------
     Copy Constructor

     Precondition:  original is the queue to be copied and is received
     as a const reference parameter.
     Postcondition: A copy of original has been constructed.
     -----------------------------------------------------------------------*/

     /***** Destructor *****/
    ~Queue();
    /*-----------------------------------------------------------------------
     Class destructor

     Precondition:  None.
     Postcondition: The linked list in the queue has been deallocated.
     -----------------------------------------------------------------------*/

     /***** Assignment *****/
    const Queue& operator= (const Queue& rightHandSide);
    /*-----------------------------------------------------------------------
     Assignment Operator

     Precondition:  rightHandSide is the queue to be assigned and is
     received as a const reference parameter.
     Postcondition: The current queue becomes a copy of rightHandSide
     and a reference to it is returned.
     -----------------------------------------------------------------------*/

    bool empty() const;
    /*-----------------------------------------------------------------------
     Check if queue is empty.

     Precondition:  None.
     Postcondition: Returns true if queue is empty and false otherwise.
     -----------------------------------------------------------------------*/

    void enqueue(const QueueElement& value);
    /*-----------------------------------------------------------------------
     Add a value to a queue.

     Precondition:  value is to be added to this queue.
     Postcondition: value is added at back of queue.
     -----------------------------------------------------------------------*/

    void display(ostream& out) const;
    /*-----------------------------------------------------------------------
     Display values stored in the queue.

     Precondition:  ostream out is open.
     Postcondition: Queue's contents, from front to back, have been
     output to out.
     -----------------------------------------------------------------------*/

    QueueElement front() const;
    /*-----------------------------------------------------------------------
     Retrieve value at front of queue (if any).

     Precondition:  Queue is nonempty.
     Postcondition: Value at front of queue is returned, unless the queue
     is empty; in that case, an error message is displayed and a
     "garbage value" is returned.
     -----------------------------------------------------------------------*/

    void dequeue();
    /*-----------------------------------------------------------------------
     Remove value at front of queue (if any).

     Precondition:  Queue is nonempty.
     Postcondition: Value at front of queue has been removed, unless
     queue is empty; in that case, an error message is displayed
     and execution allowed to proceed.
     -----------------------------------------------------------------------*/

private:
    /*** Node class ***/
    class Node
    {
    public:
        QueueElement data;
        Node* next;
        //--- Node constructor
        Node(QueueElement value, Node* link = 0)
            /*-------------------------------------------------------------------
             Precondition:  value and link are received
             Postcondition: A Node has been constructed with value in its
             data part and its next part set to link (default 0).
             ------------------------------------------------------------------*/
        {
            data = value; next = link;
        }

    };

    typedef Node* NodePointer;

    /***** Data Members *****/
    NodePointer myFront,      // pointer to front of queue
        myBack;       // pointer to back of queue

}; // end of class declaration

//  Queue.cpp
//  LQueue
//
//  Created by Ashraf AbdelRaouf on 11/7/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//
/*--- Queue.cpp ----------------------------------------------------------
 This file implements LQueue member functions.
 -------------------------------------------------------------------------*/

 //--- Definition of Queue constructor
template <typename QueueElement>
Queue<QueueElement>::Queue()
    : myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
template <typename QueueElement>
Queue<QueueElement>::Queue(const Queue<QueueElement>& original)
{
    myFront = myBack = 0;
    if (!original.empty())
    {
        // Copy first node
        myFront = myBack = new Queue::Node(original.front());

        // Set pointer to run through original's linked list
        Queue::NodePointer origPtr = original.myFront->next;
        while (origPtr != 0)
        {
            myBack->next = new Queue::Node(origPtr->data);
            myBack = myBack->next;
            origPtr = origPtr->next;
        }
    }
}

//--- Definition of Queue destructor
template <typename QueueElement>
Queue<QueueElement>::~Queue()
{
    // Set pointer to run through the queue
    Queue::NodePointer prev = myFront,
        ptr;
    while (prev != 0)
    {
        ptr = prev->next;
        delete prev;
        prev = ptr;
    }
}

//--- Definition of assignment operator
template <typename QueueElement>
const Queue<QueueElement>& Queue<QueueElement>::operator=(const Queue<QueueElement>& rightHandSide)
{
    if (this != &rightHandSide)         // check that not q = q
    {
        this->~Queue();                  // destroy current linked list
        if (rightHandSide.empty())       // empty queue
            myFront = myBack = 0;
        else
        {                                // copy rightHandSide's list
            // Copy first node
            myFront = myBack = new Queue::Node(rightHandSide.front());

            // Set pointer to run through rightHandSide's linked list
            Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
            while (rhsPtr != 0)
            {
                myBack->next = new Queue::Node(rhsPtr->data);
                myBack = myBack->next;
                rhsPtr = rhsPtr->next;
            }
        }
    }
    return *this;
}

//--- Definition of empty()
template <typename QueueElement>
bool Queue<QueueElement>::empty() const
{
    return (myFront == 0);
}

//--- Definition of enqueue()
template <typename QueueElement>
void Queue<QueueElement>::enqueue(const QueueElement& value)
{
    Queue::NodePointer newptr = new Queue::Node(value);
    if (empty())
        myFront = myBack = newptr;
    else
    {
        myBack->next = newptr;
        myBack = newptr;
    }
}

//--- Definition of display()
template <typename QueueElement>
void Queue<QueueElement>::display(ostream& out) const
{
    Queue::NodePointer ptr;
    for (ptr = myFront; ptr != 0; ptr = ptr->next)
        out << ptr->data << "  ";
    out << endl;

}

//--- Definition of front()
template <typename QueueElement>
QueueElement Queue<QueueElement>::front() const
{
    if (!empty())
        return (myFront->data);
    else
    {
        cerr << "*** Queue is empty "
            " -- returning garbage ***\n";
        QueueElement* temp = new(QueueElement);
        QueueElement garbage = *temp;     // "Garbage" value
        delete temp;
        return garbage;
    }
}

//--- Definition of dequeue()
template <typename QueueElement>
void Queue <QueueElement> ::dequeue()
{
    if (!empty())
    {
        Queue::NodePointer ptr = myFront;
        myFront = myFront->next;
        delete ptr;
        if (myFront == 0)     // queue is now empty
            myBack = 0;
    }
    else
        cerr << "*** Queue is empty -- can't remove a value ***\n";
}
