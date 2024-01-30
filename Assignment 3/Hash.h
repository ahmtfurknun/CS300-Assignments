#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class HashedObj>
class HashTable
{
public:
    explicit HashTable( const HashedObj & notFound, const double load_f, int size = 53 );//
    HashTable( const HashTable & rhs )
            : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                _array( rhs._array ), currentSize( rhs.currentSize ), load_factor(rhs.load_factor) { }//

    const HashedObj & find( const HashedObj & x ) const;//

    void makeEmpty( );//
    void insert( const HashedObj & x );//
    void remove( const HashedObj & x );//
	int get_size();
	double get_load();
    const HashTable & operator=( const HashTable & rhs );//
	void updateElement(const HashedObj& old, const HashedObj& _new);
    enum EntryType { ACTIVE, EMPTY, DELETED };//
private:
    struct HashEntry
    {
         HashedObj element;
         EntryType info;

         HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
			 : element( e ), info( i ) { }
    };
            
    vector<HashEntry> _array;
    int currentSize;
    const HashedObj ITEM_NOT_FOUND;
	const double load_factor;

    bool isActive( int currentPos ) const;
    int findPos( const HashedObj & x ) const;
    void rehash( );
 };


/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, const double load_f, int size )
	: ITEM_NOT_FOUND( notFound ), _array( nextPrime( size ) ), load_factor(load_f)
{
        makeEmpty( );
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    int collisionNum = 0;
    int currentPos = hash_f(x, _array.size( ) );

    while ( _array[ currentPos ].info != EMPTY && _array[ currentPos ].element != x )
    {
        currentPos += pow(++collisionNum, 2) ;  //add the difference
        while ( currentPos >= _array.size( ) )              // perform the mod
		{
                currentPos -= _array.size( );                // if necessary
		}
    }
    return currentPos;
}

/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
    return _array[ currentPos ].info == ACTIVE;
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
	{
        _array[ currentPos ].info = DELETED;
	}
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
{
    int currentPos = findPos( x );
    if (isActive( currentPos )) 
	{
        return _array[ currentPos ].element; 
	}
    return   ITEM_NOT_FOUND;
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
	{
        return;
	}
    _array[ currentPos ] = HashEntry( x, ACTIVE );

    // enlarge the hash table if necessary 
	if ( ++currentSize >= _array.size( ) / (1/load_factor) )
	{
        rehash( );
	}
}


/**
* Expand the hash table.
*/
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
	vector<HashEntry> old_array = _array;

	// Create new double-sized, empty table
	_array.resize( nextPrime( 2 * old_array.size( ) ) );
	for ( int j = 0; j < _array.size( ); j++ )
	{
        _array[ j ].info = EMPTY;
	}
	// Copy table over
	currentSize = 0;
	for ( int i = 0; i < old_array.size( ); i++ )
	{
		if ( old_array[ i ].info == ACTIVE )
		{
            insert( old_array[ i ].element );
		}
	}
	cout << "rehashed..." << endl;
	cout << "previous table size:" << old_array.size() << ", new table size: " << _array.size() << ", current unique word count: " << currentSize << ", current load factor: " << double(currentSize)/double(_array.size()) << endl;
}


/**
* Internal method to test if a positive number is prime.
* Not an efficient algorithm.
*/
bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
	{
        return true;
	}
    if ( n == 1 || n % 2 == 0 )
	{
        return false;
	}
    for ( int i = 3; i * i <= n; i += 2 )
	{
        if ( n % i == 0 )
		{
            return false;
		}
	}
    return true;
}


/**
* Internal method to return a prime number 
* at least as large as n.  Assumes n > 0.
*/
int nextPrime( int n )
{
    if ( n % 2 == 0 )
	{
        n++;
	}
    for ( ; ! isPrime( n ); n += 2 )
	{;}

    return n;
}

/**
* Make the hash table logically empty.
*/
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
    for(int i = 0; i < _array.size(); i++ )
	{
		_array[i].info = EMPTY;
	}
	currentSize = 0;
}


template <class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>::operator=( const HashTable & rhs )
{
    if (this != &rhs)
	{
		makeEmpty();
		ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
		_array = rhs._array;
		currentSize = rhs.currentSize;
		load_factor = rhs.load_factor
	}
	return *this;
}

template <class HashedObj>
void HashTable<HashedObj>::updateElement(const HashedObj& old, const HashedObj& _new){
	for(int i = 0; i<_array.size(); i++)
	{
		if(_array[i].element.word == old.word)
		{
			_array[i].element = _new;
		}
	}
}

template <class HashedObj>
int HashTable<HashedObj>::get_size(){
	return currentSize;
}

template <class HashedObj>
double HashTable<HashedObj>::get_load(){
	return double(currentSize)/double(_array.size());
}
#endif // !HASH_H
