#ifndef LIST_H
#define LIST_H
#include <iostream>
using namespace std;

template <class Object>
class List;     // Incomplete declaration.

template <class Object>
class ListItr;     // Incomplete declaration.


template <class Object>
class ListNode
{
    ListNode( const Object & theElement = Object( ), ListNode * n = NULL )
            : element( theElement ), next( n ) { }

    Object   element;
    ListNode *next;

    friend class List<Object>;
    friend class ListItr<Object>;
};

template <class Object>
class ListItr
{
public:
    ListItr( ) : current( NULL ) { }
    bool isPastEnd( ) const
	{
		return current == NULL;
	}
    void advance( )
	{
		if ( ! isPastEnd( ) )
		{
				current = current->next;   
		}
	}

    const Object & retrieve( ) const
    {   
		return current->element;    
	}

private:
    ListNode<Object> *current;    // Current position

    ListItr( ListNode<Object> *theNode )
            : current( theNode ) { }

    friend class List<Object>;    // Grant access to constructor
};


template <class Object>
class List
{
public:
    List( );
    List( const List & rhs );
    ~List( );
    bool isEmpty( ) const;
    void makeEmpty( );
    ListItr<Object> zeroth( ) const;
    ListItr<Object> first( ) const;
    void insert( const Object & x, const ListItr<Object> & p );
    ListItr<Object> find( const Object & x ) const;
    ListItr<Object> findPrevious( const Object & x ) const;
    void remove( const Object & x );

    const List & operator=( const List & rhs );

private:
    ListNode<Object> *header;
};

/**
* Construct the list.
*/
template <class Object>
List<Object>::List( )
{
	header = new ListNode<Object>;
}


/**
* Test if the list is logically empty.
* Return true if empty, false, otherwise.
*/
template <class Object>
bool List<Object>::isEmpty( ) const
{    
	// see if the header points to NULL 
    return header–>next == NULL;
}

/**
* Insert item x after p.
*/
template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p )
{
	if ( p.current != NULL )
	{
		p.current->next = new ListNode<Object>( x, p.current->next );
	}
}

/**
* Return iterator corresponding to the first node containing an item x.
* Iterator isPastEnd if item is not found.
*/
template <class Object>
ListItr<Object> List<Object>::find( const Object & x ) const
{
    ListNode<Object> *itr = header->next; // Initialize

    while ( itr != NULL && itr->element != x )
            itr = itr->next;

    return ListItr<Object>( itr );
}

/**
* Return iterator prior to the first node containing an item x. 
*/
template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const
{
    ListNode<Object> *itr = header;

    while ( itr->next != NULL && itr->next->element != x )
	{
        itr = itr->next;
	}

    return ListItr<Object>( itr );
}

/**
* Remove the first occurrence of an item x.
*/
template <class Object>
void List<Object>::remove( const Object & x )
{
    ListItr<Object> p = findPrevious( x ); // Locate previous of x, if any

    if ( p.current->next != NULL )
    {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next;  // Bypass deleted node
        delete oldNode;
    }
}


/**
* Return an iterator representing the header node.
*/
template <class Object>
ListItr<Object> List<Object>::zeroth( ) const
{
    return ListItr<Object>( header );
}

/**
* Return an iterator representing the first node in the list.
* This operation is invalid for empty lists.
*/
template <class Object>
ListItr<Object> List<Object>::first( ) const
{
    return ListItr<Object>( header->next );
}

/**
* Make the list logically empty.
*/
template <class Object>
void List<Object>::makeEmpty( )
{
    while ( ! isEmpty( ) )
	{
        remove( first( ).retrieve( ) );
	}
}


/**
* Deep copy of linked lists.
*/
template <class Object>
const List<Object> & List<Object>::operator=( const List<Object> & rhs )
{
    if ( this != &rhs )
    {
        makeEmpty( );

        ListItr<Object> ritr = rhs.first( );
        ListItr<Object> itr = zeroth( );
        for (  ;  ! ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
		{
            insert( ritr.retrieve( ), itr );
		}
    }
    return *this;
}


/**
* Copy constructor.
*/
template <class Object>
List<Object>::List( const List<Object> & rhs )
{
    header = new ListNode<Object>;
    *this = rhs;  // Deep Copy
}

/**
* Destructor.
*/
template <class Object>
List<Object>::~List( )
{
    makeEmpty( );  // Get rid of all list nodes
    delete header;  // then get rid of the header
}


#endif // !LIST_H
