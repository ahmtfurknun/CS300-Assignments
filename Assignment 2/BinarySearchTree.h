#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

using namespace std;

template <class Comparable>
class BinarySearchTree;


template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;
	BinaryNode( const Comparable & theElement,
	BinaryNode *lt, BinaryNode *rt ): element( theElement ), left( lt ), right( rt ) { }
	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Comparable & notFound );//
	BinarySearchTree( const BinarySearchTree & rhs );//
	~BinarySearchTree( );//
	const Comparable & findMin( ) const;//
	const Comparable & findMax( ) const;//
	const Comparable & find( const Comparable & x ) const;//
	bool isEmpty( ) const;//
	void printTree( ) const;//
	void makeEmpty( );//
	void insert( const Comparable & x );//
	void remove( const Comparable & x );//
	const BinarySearchTree & operator=( const BinarySearchTree & rhs ); //
	void updateElement(const Comparable& old, const Comparable& _new);
private:
	BinaryNode<Comparable> *root;
	Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;//
	void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;//
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;//
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;//
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;//
	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;//
	void makeEmpty( BinaryNode<Comparable> * & t ) const;//
	void printTree( BinaryNode<Comparable> *t ) const;//
	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;//
};

#endif 