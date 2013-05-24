#ifndef LinkedList_Node_h
#define LinkedList_Node_h

/*
For this project, I have neither given nor receive
unauthorized assistance
Matthew O'Neil 
*/


#include <iostream>
using namespace std;

// This is the Node Class.
// It contains a templated data T and a pointer to the next node.
// This allows you to extract data and set data
template <typename T>
class Node
{ 

private:
T           data;
Node < T > *next;

public:

Node ();
Node (T newData, Node< T > *newNext = NULL);
void setData (T newData );
void setNext (Node< T > *newNext = NULL);
T getData ();
Node < T > * getNext ();
};

// This is a Node constructor when passed data and a node pointer.
// This allows easy linked list construction.
template <typename T>
Node < T > :: Node(T newData, Node <T> *newNext)
{
    next = newNext;
    data = newData;
}

// This is the default constructor for node.
// Essentially the next pointer is simply nulled.
template <typename T>
Node < T > :: Node ()
{
    next = NULL;
}

// This fills the T data in the list with an input parameter.
template <typename T>
void Node < T > :: setData (T newData)
{
    data = newData;
}

// This sets a pointer to another node, perfect for
// making linked lists.
template <typename T>
void Node < T > :: setNext ( Node <T> *newNext )
{
    next = newNext;
}

// This returns the data stored in this node.
template <typename T>
T Node < T > :: getData ()
{
    return data;
}

// This returns the pointer to the next node variable.
template <typename T>
Node < T > * Node < T > :: getNext ()
{
    return next;
}

#endif
