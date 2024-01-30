#include "Sort.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

#pragma comment(linker, "/STACK:2000000")

//Struct of contacts
struct phonebookItem
{
	string name;
	string nameSurname;
	string number;
	string location;

	//default constructor
	phonebookItem()
	{
		name="";
		nameSurname="";
		number="";
		location="";
	}

	//constructor
	phonebookItem(string _name, string _surname, string _number, string _location)
	{
		name = _name;
		nameSurname = _name +" " + _surname;
		number = _number;
		location = _location;
	}

	//operator == for full name of the contact
	bool operator == (const phonebookItem& rhs) const
	{
		return nameSurname == rhs.nameSurname;
	}

	//!!! THÝS OPERATOR IS NOT USED AS IT MEANS
	//operator != to compare contacts with partial names
	//rhs name MUST longer or equal
	bool operator != (const phonebookItem& rhs) const
	{
		return (rhs.name == name.substr(0, rhs.name.length()));
	}

	//smaller operator to compare full name of the contacts
	bool operator < (const phonebookItem& rhs) const
	{
		return (nameSurname < rhs.nameSurname);
	}

	//smaller or equal to operator to compare full name of the contacts
	bool operator <= (const phonebookItem& rhs) const
	{
		return (nameSurname <= rhs.nameSurname);
	}

	//greater operator to compare full name of the contacts
	bool operator > (const phonebookItem& rhs) const
	{
		return (nameSurname > rhs.nameSurname);
	}

	//greater or equal to operator to compare full name of the contacts
	bool operator >= (const phonebookItem& rhs) const
	{
		return (nameSurname > rhs.nameSurname);
	}

	//assignment operator to 
	void operator =(const phonebookItem& rhs)
	{
		name = rhs.name;
		nameSurname = rhs.nameSurname;
		number = rhs.number;
		location = rhs.location;
	}
};

//ostream operator to display the info of the contact
ostream& operator <<(ostream & os, const phonebookItem& rhs)
{
	os<<rhs.nameSurname<< " " <<rhs.number<< " " << rhs.location<<endl;
	return os;
}


//this function makes the word (s) uppercase
void toUpper(string &s)
{
	for(int i=0; i<s.length(); i++)
	{
		if(s[i]<='z' && s[i]>='a')
		{
			s[i]+='A'-'a';
		}
	}
}

int main()
{
	string filename, word;
	cout << "Please enter the contact file name:" <<endl;
	cin >> filename;
	cout << "Please enter the word to be queried:"<<endl;
	cin.ignore();
	getline(cin, word);

	ifstream myfile;
    myfile.open(filename);
	if(!myfile.fail())
	{
		string line; 

		//initialize the vectors to store contact info for each sorting algorithm
		vector<phonebookItem> insertionVector;
		vector<phonebookItem> quickVector;
		vector<phonebookItem> mergeVector;
		vector<phonebookItem> heapVector;

		while (getline(myfile, line))
		{
			//for each line
			istringstream linestream(line);
			string name, surname, number, location;
			//seperate the info of the contact
			linestream >> name>> surname>> number>> location;

			//make name and surname uppercase to search
			toUpper(name);
			toUpper(surname);

			//create new contact with this info
			phonebookItem newContact(name, surname, number, location);

			//add new contact to every vector
			insertionVector.push_back(newContact);
			quickVector.push_back(newContact);
			mergeVector.push_back(newContact);
			heapVector.push_back(newContact);
		}

		cout << "\nSorting the vector copies"<<endl;
		cout << "======================================"<<endl;

		int k = 100;
		int i;

		//measure time for quicksort
		vector<phonebookItem> copy;
		auto start = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			//sort a copy so that nex iterations sorts it exactly the same
			copy = quickVector;
			quicksort(copy);
		}
		auto quick = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start);
		int quickTime = quick.count() / k;
		cout << "Quick Sort Time: " << quickTime << " Nanoseconds\n";


		//measure time for insertion sort
		auto start1 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			//sort a copy so that nex iterations sorts it exactly the same
			vector<phonebookItem> copy2 = insertionVector;
			insertionSort(copy2);
		}
		auto insertion = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start1);
		int insertionTime = insertion.count() / k;
		cout << "Insertion Sort Time: " << insertionTime << " Nanoseconds\n";

	
		//measure time for merge sort
		auto start2 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			//sort a copy so that nex iterations sorts it exactly the same
			vector<phonebookItem> copy3 = mergeVector;
			mergeSort(copy3, 0, mergeVector.size()-1);
		}
		auto merge = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start2);
		int mergeTime = merge.count() / k;
		cout << "Merge Sort Time: " << mergeTime << " Nanoseconds\n";

	
		//measure time for heap sort
		auto start3 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			//sort a copy so that nex iterations sorts it exactly the same
			vector<phonebookItem> copy4 = heapVector;
			heapsort(copy4);
		}
		auto heap = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start3);
		int heapTime = heap.count() / k;
		cout << "Heap Sort Time: " << heapTime << " Nanoseconds\n";
		
		
		//previously we have sorted the copies, now sort real vectors
		quicksort(quickVector);
		insertionSort(insertionVector);
		mergeSort(mergeVector);
		heapsort(heapVector);

		//seperate the word to be queried into name and surname
		istringstream linestream(word);
		string name = "", surname =	"";
		linestream >> name>>surname;

		cout << "\nSearching for "<<name+" "+surname<<endl;
		cout << "======================================"<<endl;

		toUpper(name);
		toUpper(surname);
		phonebookItem toBeSearched = phonebookItem(name, surname, "", "");

		//if surname size is 0, we need to do partial search
		if(surname.size() == 0)
		{
			vector<int> indexList = partialBinarySearch(toBeSearched, quickVector);
			
			//if list of indexes we obtained from partial binary search is empty,
			//query is not found
			if(indexList.size()==0)
			{
				cout <<toBeSearched.nameSurname<<" does NOT exist in the dataset"<<endl;
			}
			else
			{
				//display the info of the each contact from binary search
				for(int i = 0; i<indexList.size(); i++)
				{
					cout << quickVector[indexList[i]];
				}
			}
		}

		//if surname is not empty, we need to do exact search
		else
		{
			int idx = exactBinarySearch(toBeSearched, quickVector);
			//if idx is -1, item is not found
			if(idx == -1)
			{
				cout <<toBeSearched.nameSurname<<" does NOT exist in the dataset"<<endl;
			}
			else
			{
				//if found, display the info of the contact
				cout << quickVector[idx];
			}
		}

		//measure the time for binary search
		auto start4 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			if(surname.size() == 0)
			{
				vector<int> indexList = partialBinarySearch(toBeSearched, quickVector);
			}
			else
			{
				int idx = exactBinarySearch(toBeSearched, quickVector);
			}
		}

		auto binary = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start4);
		int binaryTime = binary.count() / k;
		cout << "Binary Search Time: " << binaryTime << " Nanoseconds\n";

		cout << "\nSearch results for Sequential Search:"<<endl;


		//if surname size is 0, we need to do partial search
		if(surname.size() == 0)
		{
			
			vector<int> indexList = partialSequentialSearch(toBeSearched, quickVector);

			//if list of indexes we obtained from partial sequential search is empty, 
			//query is not found
			if(indexList.size()==0)
			{
				cout <<toBeSearched.nameSurname<<" does NOT exist in the dataset"<<endl;
			}

			//if list is not empty, display the info of each contact
			else
			{
				for(int i = 0; i<indexList.size(); i++)
				{
					cout << quickVector[indexList[i]];
				}
			}
		}

		//if surname is not empty do exact search
		else
		{
			int idx = exactSequentialSearch(toBeSearched, quickVector);
			//if idx is -1, item not found
			if(idx == -1)
			{
				cout <<toBeSearched.nameSurname<<" does NOT exist in the dataset"<<endl;
			}
			else
			{
				cout << quickVector[idx];
			}
		}


		//measure the time for sequential search
		auto start5 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < k; i++)
		{
			if(surname.size() == 0)
			{
				vector<int> indexList = partialSequentialSearch(toBeSearched, quickVector);
			}
			else
			{
				int idx = exactSequentialSearch(toBeSearched, quickVector);
			}
		}
		auto sequential = std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start5);
		int sequentialTime = sequential.count() / k;
		cout << "Sequential Search Time: " << sequentialTime << " Nanoseconds\n";
		cout << "\nSpeedUp between Search Algorithms"<<endl;
		cout << "======================================"<<endl;
		cout << "(Sequential Search/ Binary Search) SpeedUp = " << double(sequentialTime)/binaryTime<<endl;
	

		cout << "\nSpeedUps between Sorting Algorithms"<<endl;
		cout << "======================================"<<endl;
		cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << double(insertionTime)/quickTime<<endl;
		cout << "(Merge Sort / Quick Sort) SpeedUp = "<< double(mergeTime)/quickTime <<endl;
		cout << "(Heap Sort / Quick Sort) SpeedUp = "<< double(heapTime)/quickTime <<endl;
	}
	return 0;
}

