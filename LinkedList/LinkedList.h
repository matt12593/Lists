#ifndef LinkedList_LinkedList_h
#define LinkedList_LinkedList_h

#include <iostream>
#include "Node.h"
#include "BadIndexException.h"

/*
This is my Linked List.
It contains a pointer to the head of the list and
pointers for navigating the list in addition to the
various methods of implementation for linked list.

Its overall function is to dynamically store information
of a templated type for organization purposes
*/

template <typename T>
class LinkedList
{
private:
    mutable Node <T> * head;
    mutable Node <T> * shell;
    mutable Node <T> * current;
    mutable Node <T> * previous;

    mutable int cnt;

public:
    LinkedList ();
    LinkedList (T data);
    LinkedList (const LinkedList< T > &ll);
    const LinkedList< T > &    operator= (const LinkedList< T > &ll);
    void insert (T data);
    void insertAt (T data, int location) throw (BadIndexException);
    T find (T data);
    T itemAt (int location) throw (BadIndexException);
    T operator[](int location);
    const T operator[](int location) const;
    T remove (T data);
    T removeAt (int location) throw (BadIndexException);
    void display (ostream &out);
    void clear ();
    int count ();
};

// This is a default constructor that sets head to null and count to zero.
template <typename T>
LinkedList < T > :: LinkedList()
{
    head = NULL;
    cnt = 0;
}


// This is a constructor that receives an initial piece of data, setting head
// to contain this data and setting its next as a null pointer.
template <typename T>
LinkedList < T > :: LinkedList( T data )
{
    // Creates the first node and sets head to it.
    shell = new Node <T>;
    head = shell;

    // Fills the first node with data and set count to 1 
    head->setData( data ); 
    head->setNext( NULL );
    cnt=1;
}

// This is a copy constructor that receives a linked list and copies it.
template <typename T>
LinkedList <T> :: LinkedList( const LinkedList <T> &ll)
{
    cnt = ll.cnt;
    head = new Node<T>;
    head->setData( (ll.head)->getData() );

    Node <T> * old; 
    old = ll.head;

    current  = head;
    for (int i = 1; i < cnt; i++)
    {
        old = old->getNext();

        shell = new Node<T>;
        current->setNext(shell);
        current = current->getNext();
        current->setData(old->getData());
    }

}


// This function inserts a piece of data at the very end of the list.
// If cnt is zero this needs to be initialized as the head.
template <typename T>
void LinkedList < T > :: insert ( T data )
{
    if (cnt == 0)
    {
        shell = new Node <T>;
        shell->setData( data );
        shell->setNext( NULL );
        head = shell;
        cnt = 1;
        return;
    }
    // Goes to the cnt - 1
    current = head;
    for (int i = 0; i < cnt-1; i++)
        current = current -> getNext();

    // Fills the shell and increments count
    shell = new Node <T>;
    shell->setData( data );
    shell->setNext( NULL );
    current->setNext( shell );
    cnt++;

}

// This inserts a piece of data at the requested location in the list.
// If this location is greater than count or less than zero, throw an error.
template <typename T>
void LinkedList < T > :: insertAt ( T data, int location ) throw (BadIndexException)
{
    // edge checking.
    if (location >= cnt)
        return insert( data );
    if (location > cnt || location < 0)
        throw BadIndexException(); 
    if (location == 0)
    {
        shell = new Node<T>;
        shell->setNext( head );
        shell->setData( data );
        cnt++;
        head = shell;
        return;
    }   
    // puts the current pointer to location-1.
    current = head;
    for (int i = 0; i < location-1; i++)
        current = current -> getNext();

    // Creates a new shell and fills it with the data.
    shell = new Node <T>;
    shell->setData( data );

    // takes on the location-1 pointer and has that point to it. 
    shell->setNext( current->getNext() );
    current->setNext( shell );
    cnt++;
}

// This function finds a piece of data and returns it if found.
// If not, a default T piece of data is returned.
template <typename T>
T LinkedList < T > :: find ( T data ) 
{
    T temp = T();
    current = head;

    for (int i = 0; i < cnt; i++)
    {
        if (current->getData() == data)
            return data;
        else if (i == cnt-1)
            return temp;
        current = current->getNext();
    }

    return temp;
}

// Returns the item at the given location.
// Makes sure this is a valid location in the list.
template <typename T>
T LinkedList < T > :: itemAt ( int location ) throw (BadIndexException)
{
    // Checks to make sure this is a valid location
    if (location >= cnt || location < 0)
        throw BadIndexException();

    // Moves from 0 to location
    current = head;
    for (int i = 0; i < location; i++)
        current = current->getNext();

    // Returns the data at location
    return current->getData();
}

// This allows bracket access of elements
template <typename T>
T LinkedList<T>::operator[](int location)
{
    cout << "Returning object\n";
    return itemAt(location);
}

// This is a test function
template <typename T>
const T LinkedList<T>::operator[](int location) const
{

    cout << "Returning constant object\n";

    // Checks to make sure this is a valid location
    if (location >= cnt || location < 0)
        throw BadIndexException();

    // Moves from 0 to location
    current = head;
    for (int i = 0; i < location; i++)
        current = current->getNext();

    // Returns the data at location
    return current->getData();
}

// This is an assignment operator when passed a linked list.
// Creates a deep copy.
template <typename T>
const LinkedList <T>&
LinkedList <T> :: operator= (const LinkedList <T> & ll)
{
    clear();

    Node<T> * traveler;
    traveler = ll.head; 

    for (int i = 0; i < ll.cnt; i++)
    {
        insert(traveler->getData());
        if (i != ll.cnt-1)
            traveler = traveler->getNext();
    }
    cnt = ll.cnt;
    return *this;

}

// This removes a piece of data when found in the list from the list
template <typename T>
T LinkedList < T > :: remove(T data)
{
    if (cnt == 0)
        return T();

    // If data is in the head, move head forward. 
    if (head->getData() == data)
    {
        T val = head->getData();
        previous = head;
        head = head->getNext();

        // Delete the node and decrement
        delete previous;
        cnt--;
        return val;
    }
    
    // If it is elsewhere, scan for it 
    current = head;
    for (int i = 0; i < cnt; i++)
    {
        if (current->getData() == data)
            break;
        previous = current;
        current = current -> getNext();
        if (i == cnt-1)
            return T();
    }
    // Set the previous's next pointer to current's next. Delete current.
    previous->setNext(current->getNext());
    T val = current->getData();
    delete current;
    cnt--;
    return val;
}

// This removes the data at the given location.
template <typename T>
T LinkedList < T > :: removeAt (int location) throw (BadIndexException)
{
    // Checks to make sure a valid location has been requested
    if ( location < 0 || location >= cnt )
        throw BadIndexException();

    if ( cnt == 0 )
        return T();


    if ( location == 0 )
    {
        current = head->getNext();
        T val = head->getData();
        delete head;
        cnt--;
        head = current;
        return val;
    }

    // Moves to location-1
    current = head;
    for (int i = 0; i < location-1; i++)
        current = current->getNext();

    // Moves current to location and stores location-1 in previous
    previous = current;
    current = current->getNext();
    T data = current->getData();

    // Sets previous's next to location+1
    previous->setNext( current->getNext() );

    // deletes location
    delete current;
    cnt--;

    // Returns the data
    return data;

}

// This outputs the contents of the entire list.
template <typename T>
void LinkedList < T > :: display (ostream &out)
{
    out << "Displaying..." << endl;
    current = head;
    for (int i = 0; i < cnt; i++)
        if (i != cnt-1)
            current = current->getNext();
    out << "End of display..." << endl;
}

// This clears the list of all allocated memory, making it newborn
template <typename T>
void LinkedList < T > :: clear ()
{
    current = head;
    previous = NULL;

    // Deletes every filled location from 0 to cnt-2 
    for (int i = 0; i < cnt-1; i++)
    {
        previous = current;
        current = current->getNext();
        delete previous;
    }

    // Deletes the data at cnt-1
    delete current;
    cnt = 0;

}

// This returns the number of items in the list.
template <typename T>
int LinkedList < T > :: count()
{
    return cnt;
}



#endif


