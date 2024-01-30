#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;           // loop over the passes
	for (unsigned int p = 1;  p < a.size(); p++)
	{
		Comparable tmp = a[p];
        // loop over the elements
		for (j = p; j > 0 &&  tmp < a[j-1]; j--){
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}

inline int leftChild( int i )
{
	return 2*i+1;
}


template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() -1; j >0; j--)
	{
  	     swaP(a[0], a[j]);    // swaP max to the last pos.
         percDown(a, 0, j); // re-form the heap
	}
}

// for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
template <class Comparable>  
void percDown( vector<Comparable> & a, int i, int n )
{
	int child;
	Comparable tmp;

	for (tmp=a[i] ; leftChild(i) < n; i = child )
	{
		child = leftChild(i);
		if ( child != n-1 && a[ child  ] < a[ child+1 ] ){
			child++;
		}
		if ( a[child ] > tmp ){
			a[i] = a[ child ];
		}
		else{
			break;
		}
	} 
	a[ i ] = tmp;
}


template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	mergeSort( a, 0, a.size( ) - 1 );
}


template <class Comparable>
void mergeSort( vector<Comparable> & a, int left, int right )
{
    if ( left < right )
    {
        int center = left + (right -left) / 2;
        mergeSort( a, left, center );
        mergeSort( a,center + 1, right );
        merge( a, left, center, right );
    }
}



template <class Comparable>
void merge(vector<Comparable> & a, int start, int mid, int end)
{
    int next = mid + 1;

	if (a[mid] <= a[next]) {
        return;
    }
	while(start <= mid && next<= end)
	{
		if(a[start] > a[next])
		{
			Comparable val = a[next];
			int temp = next;

			while (temp != start) {
                a[temp] = a[temp - 1];
                temp--;
            }
            a[start] = val;

            start++;
            mid++;
            next++;
		}
		else
		{
			start++;
		}
	}
}


/**
* Quicksort algorithm (driver).
*/
template <class Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}

/**
* Internal insertion sort routine for subarrays
* that is used by quicksort.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
	for ( int p = left + 1; p <= right; p++ )
	{
		Comparable tmp = a[ p ];
		int j;
		for ( j = p; j > left && tmp < a[ j - 1 ]; j-- ){
			a[ j ] = a[ j-1 ];
		}
		a[ j ] = tmp;
	}
}


/**
* Standard swaP
*/
template <class Comparable>
inline void swaP( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ] < a[ left ] ){
		swaP( a[ left ], a[ center ] );
	}
    if ( a[ right ] < a[ left ] ){
		swaP( a[ left ], a[ right ] );
	}
    if ( a[ right ] < a[ center ] ){
		swaP( a[ center ], a[ right ] );
	}

    // Place pivot at position right - 1
    swaP( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
* Internal quicksort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );
		// Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                    swaP( a[ i ], a[ j ] );
            else
                    break;
        }
		swaP( a[ i ], a[ right - 1 ] );   // Restore pivot
        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
	}
    else  // Do an insertion sort on the subarray
		insertionSort( a, left, right );
}


//Searches obj1 in the given vector.
//If found, return index.
//If not found, return -1.
template <class Comparable>
int exactSequentialSearch( Comparable & obj1, vector<Comparable> & list )
{
	int _size = list.size();
    for(unsigned int i = 0; i<_size; i++)
	{
		if(obj1 == list[i])
		{
			return i;
		}
	}

	return -1;
}


//IMPORTANT
//in order to use this function
//comperable object shoul have != operator
//which represents partial match
//do not use otherwise!!
template <class Comparable>
vector<int> partialSequentialSearch(Comparable & obj1, vector<Comparable> & list )
{
	vector<int> indexList;
	int _size = list.size();

    for(unsigned int i = 0; i<_size; i++)
	{
		if(list[i] != obj1  )
		{
			indexList.push_back(i);
		}
	}
	return indexList;
}

//Searches obj1 in the given vector.
//If found, return index.
//If not found, return -1.
template <class Comparable>
int exactBinarySearch( Comparable & obj1, vector<Comparable> & list )
{
	int lastIndex = list.size()-1;
	int firstIndex = 0;
	while(firstIndex <= lastIndex)
	{
		int middle = firstIndex + (lastIndex - firstIndex) / 2;

		if (list[middle] == obj1){
			return middle;
		}
		
		else if (list[middle] < obj1){
			firstIndex = middle + 1;
		}
		
		else
			lastIndex = middle - 1;
	}

	return -1;
}


//IMPORTANT
//in order to use this function
//comperable object shoul have != operator
//which represents partial match
//do not use otherwise!!
template <class Comparable>
vector<int> partialBinarySearch(Comparable & obj1, const vector<Comparable> & list )
{
	vector<int> indexList;
	int lastIndex = list.size()-1;
	int firstIndex = 0;
	while(firstIndex <= lastIndex)
	{
		int middle = firstIndex + (lastIndex - firstIndex) / 2;

		if (list[middle] != obj1){
			int start, end;
			for(int i = middle+1; i<= lastIndex; i++)
			{
				if(list[i] != obj1)
				{
					end = i;
				}
				else
				{
					break;
				}
			}

			for(int j = middle-1; j>= firstIndex; j--)
			{
				if(list[j] != obj1)
				{
					start = j;
				}
				else
				{
					break;
				}
			}

			for(int k = start; k <= end; k++)
			{
				indexList.push_back(k);
			}
			break;
		}
		
		else if (list[middle] < obj1){
			firstIndex = middle + 1;
		}
		
		else
			lastIndex = middle - 1;
	}

	return indexList;
}

#endif