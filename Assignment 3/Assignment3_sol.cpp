#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "BinarySearchTree.h"
#include "Hash.h"
using namespace std;

struct DocumentItem {
	string documentName;
	int count;

	DocumentItem(string doc_name, int number_of_occurence): documentName(doc_name), count(number_of_occurence){}
};

struct WordItem {
	string word;
	vector<DocumentItem> list_of_occurence;

	WordItem()
	{
		word = "NOT_FOUND";
		vector<DocumentItem> a;
		list_of_occurence = a;
	}

	WordItem(string w, vector<DocumentItem> list): word(w), list_of_occurence(list)
	{}

	bool operator==(const WordItem &rhs) const
	{
		return (word == rhs.word);
	}

	bool operator!=(const WordItem &rhs) const
	{
		return (word != rhs.word);
	}
};

bool operator>(const WordItem &lhs, const WordItem &rhs)
{
	return (lhs.word > rhs.word);
}
bool operator<(const WordItem &lhs, const WordItem &rhs)
{
	return (lhs.word < rhs.word);
}
bool operator>=(const WordItem &lhs, const WordItem &rhs)
{
	return (lhs.word >= rhs.word);
}
bool operator<=(const WordItem &lhs, const WordItem &rhs)
{
	return (lhs.word <= rhs.word);
}

int hash_f (const WordItem & item, int tableSize)
{ 
    int hashVal = 0;
	string key = item.word;
    for (int i = 0; i < key.length();i++) 
	{
	  hashVal = 37 * hashVal + key[ i ];
	}

    hashVal = hashVal % tableSize;

    while (hashVal < 0) 
	{
	  hashVal = hashVal + tableSize;
	}
   return(hashVal);
}

vector<string> string_converter(string word)
{
	vector<string> result;
	string curr_word = "";
	for(int i =0; i < word.length(); i++)
	{
		if(word[i] <= 'z' && word[i] >='a')
		{
			curr_word += word[i];
		}

		else if(word[i] <= 'Z' && word[i] >='A')
		{
			char lower_char = word[i] + 32;
			curr_word += lower_char;
		}

		else
		{
			if(curr_word != "")
			{
				result.push_back(curr_word);
			}
			curr_word = "";
		}
	}
	if(curr_word != "")
	{
		result.push_back(curr_word);
	}
	return result;
}

bool is_vector_contains(string filename, vector<DocumentItem> v)
{
	for (int i = 0; i<v.size(); i++)
	{
		if(v[i].documentName == filename)
		{
			return true;
		}
	}
	return false;
}

int get_num_occur(string filename, vector<DocumentItem> v)
{
	for (int i = 0; i<v.size(); i++)
	{
		if(v[i].documentName == filename)
		{
			return v[i].count;
		}
	}
	return -1;
}

void bst_query_documents(BinarySearchTree<WordItem> &tree, const vector<string> &filenames, const vector<string>& queried_vector)
{
	vector<DocumentItem> empty;
	vector< vector<DocumentItem> > occurences;
	vector<WordItem> occurences_based_on_files;
	bool is_filename_valid = true;
	for( int i= 0; i<filenames.size(); i++)
	{
		is_filename_valid = true;
		WordItem temp(filenames[i], empty);
		for(int j= 0; j<queried_vector.size(); j++)
		{
			int num_ocur = get_num_occur(filenames[i], tree.find(WordItem(queried_vector[j], empty)).list_of_occurence);
			if(num_ocur == -1)
			{
				is_filename_valid = false;
			}
			temp.list_of_occurence.push_back(DocumentItem(queried_vector[j], num_ocur));
		}
		if(is_filename_valid)
		{
			occurences_based_on_files.push_back(temp);
		}
	}
	if(occurences_based_on_files.size() == 0)
	{
		cout << "No document contains the given query"<<endl;
	}
	else
	{
		for (int i = 0; i<occurences_based_on_files.size(); i++)
		{
			cout << "in Document "<<occurences_based_on_files[i].word<< ", ";
			for (int j = 0; j < occurences_based_on_files[i].list_of_occurence.size(); j++)
			{
				cout << occurences_based_on_files[i].list_of_occurence[j].documentName << " found "<<occurences_based_on_files[i].list_of_occurence[j].count;
				if(j == occurences_based_on_files[i].list_of_occurence.size()-1)
				{
					cout << " times."<<endl;
				}
				else
				{
					cout << " times, ";
				}
			}
		}
	}
}

void bst_query_documents_without_display(BinarySearchTree<WordItem> &tree, const vector<string>& filenames, const vector<string>& queried_vector)
{
	vector<DocumentItem> empty;
	vector< vector<DocumentItem> > occurences;
	vector<WordItem> occurences_based_on_files;
	bool is_filename_valid = true;
	for( int i= 0; i<filenames.size(); i++)
	{
		is_filename_valid = true;
		WordItem temp(filenames[i], empty);
		for(int j= 0; j<queried_vector.size(); j++)
		{
			int num_ocur = get_num_occur(filenames[i], tree.find(WordItem(queried_vector[j], empty)).list_of_occurence);
			if(num_ocur == -1)
			{
				is_filename_valid = false;
			}
			temp.list_of_occurence.push_back(DocumentItem(queried_vector[j], num_ocur));
		}
		if(is_filename_valid)
		{
			occurences_based_on_files.push_back(temp);
		}
	}
	if(occurences_based_on_files.size() == 0)
	{
		;
	}
	else
	{
		for (int i = 0; i<occurences_based_on_files.size(); i++)
		{
			;
			for (int j = 0; j < occurences_based_on_files[i].list_of_occurence.size(); j++)
			{
				;
				if(j == occurences_based_on_files[i].list_of_occurence.size()-1)
				{
					;
				}
				else
				{
					;
				}
			}
		}
	}
}

void ht_query_documents(HashTable<WordItem> &table, const vector<string> &filenames, const vector<string>& queried_vector)
{
	vector<DocumentItem> empty;
	vector< vector<DocumentItem> > occurences;
	vector<WordItem> occurences_based_on_files;
	bool is_filename_valid = true;
	for( int i= 0; i<filenames.size(); i++)
	{
		is_filename_valid = true;
		WordItem temp(filenames[i], empty);
		for(int j= 0; j<queried_vector.size(); j++)
		{
			int num_ocur = get_num_occur(filenames[i], table.find(WordItem(queried_vector[j], empty)).list_of_occurence);
			if(num_ocur == -1)
			{
				is_filename_valid = false;
			}
			temp.list_of_occurence.push_back(DocumentItem(queried_vector[j], num_ocur));
		}
		if(is_filename_valid)
		{
			occurences_based_on_files.push_back(temp);
		}
	}
	if(occurences_based_on_files.size() == 0)
	{
		cout << "No document contains the given query"<<endl;
	}
	else
	{
		for (int i = 0; i<occurences_based_on_files.size(); i++)
		{
			cout << "in Document "<<occurences_based_on_files[i].word<< ", ";
			for (int j = 0; j < occurences_based_on_files[i].list_of_occurence.size(); j++)
			{
				cout << occurences_based_on_files[i].list_of_occurence[j].documentName << " found "<<occurences_based_on_files[i].list_of_occurence[j].count;
				if(j == occurences_based_on_files[i].list_of_occurence.size()-1)
				{
					cout << " times."<<endl;
				}
				else
				{
					cout << " times, ";
				}
			}
		}
	}
}

void ht_query_documents_without_display(HashTable<WordItem> &table, const vector<string> &filenames, const vector<string>& queried_vector)
{
	vector<DocumentItem> empty;
	vector< vector<DocumentItem> > occurences;
	vector<WordItem> occurences_based_on_files;
	bool is_filename_valid = true;
	for( int i= 0; i<filenames.size(); i++)
	{
		is_filename_valid = false;
		WordItem temp(filenames[i], empty);
		for(int j= 0; j<queried_vector.size(); j++)
		{
			int num_ocur = get_num_occur(filenames[i], table.find(WordItem(queried_vector[j], empty)).list_of_occurence);
			if(num_ocur == -1)
			{
				is_filename_valid = false;
			}
			temp.list_of_occurence.push_back(DocumentItem(queried_vector[j], num_ocur));
		}
		if(is_filename_valid)
		{
			occurences_based_on_files.push_back(temp);
		}
	}
	if(occurences_based_on_files.size() == 0)
	{
		;
	}
	else
	{
		for (int i = 0; i<occurences_based_on_files.size(); i++)
		{
			;
			for (int j = 0; j < occurences_based_on_files[i].list_of_occurence.size(); j++)
			{
				;
				if(j == occurences_based_on_files[i].list_of_occurence.size()-1)
				{
					;
				}
				else
				{
					;
				}
			}
		}
	}
}


int main()
{
	WordItem not_found;
	BinarySearchTree<WordItem> bst(not_found);
	HashTable<WordItem> ht(not_found, 0.7);
	cout << "Enter number of input files: ";
	int num_of_files;
	cin >> num_of_files;
	vector<string> filenames;
	string filename;
	for(int i = 1; i<=num_of_files; i++)
	{
		cout << "Enter "<<i<<". file name: ";
		cin >> filename;
		filenames.push_back(filename);
	}

	ifstream file_stream;
	for(int i = 0; i < num_of_files; i++)
	{
		file_stream.open(filenames[i]);
		string line;
		while(getline(file_stream, line))
		{
			vector<string> words = string_converter(line);
			for(int j = 0; j<words.size(); j++)
			{
				vector<DocumentItem> occurences;
				occurences.push_back(DocumentItem(filenames[i], 1));
				WordItem itemToFind(words[j], occurences);
				if(bst.find(itemToFind).word != words[j])//if not found
				{
					bst.insert(itemToFind);
				}
				else
				{
					WordItem old_item = bst.find(itemToFind);
					vector<DocumentItem> old_occurences = old_item.list_of_occurence;
					bool is_updated = false;
					for(int k = 0; k<old_occurences.size(); k++)
					{
						if(filenames[i] == old_occurences[k].documentName)
						{
							old_occurences[k].count++;
							is_updated = true;
						}
					}
					if(!is_updated)
					{
						old_occurences.push_back(DocumentItem(filenames[i], 1));
					}
					WordItem new_item(words[j], old_occurences);
					bst.updateElement(old_item, new_item);
				}

				string finded_hash_word = ht.find(itemToFind).word;
				if(finded_hash_word != words[j])
				{
					ht.insert(itemToFind);
				}
				else
				{
					WordItem  old_hash_item = ht.find(itemToFind);
					vector<DocumentItem> old_hash_occurences = old_hash_item.list_of_occurence;
					bool is_hash_updated = false;
					for(int k = 0; k<old_hash_occurences.size(); k++)
					{
						if(filenames[i] == old_hash_occurences[k].documentName)
						{
							old_hash_occurences[k].count++;
							is_hash_updated = true;
						}
					}
					if(!is_hash_updated)
					{
						old_hash_occurences.push_back(DocumentItem(filenames[i], 1));
					}
					WordItem new_hash_item(words[j], old_hash_occurences);
					ht.updateElement(old_hash_item, new_hash_item);
				}
			}
		}
		file_stream.close();
	}

	cout <<endl << "After preprocessing, the unique word count is "<<ht.get_size()<<". Current load ratio is "<<ht.get_load()<<endl;
	string query;
	cout <<"Enter queried words in one line: ";
	
	cin.ignore();
	getline(cin, query);

	vector<string> queried_vector = string_converter(query);
	bst_query_documents(bst, filenames, queried_vector);
	ht_query_documents(ht, filenames, queried_vector);
	
	int k = 200;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		// QueryDocuments(with BST);
		bst_query_documents_without_display(bst, filenames, queried_vector);

	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << BSTTime.count() / k << "\n";
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		// QueryDocuments (with hashtable);
		ht_query_documents_without_display(ht, filenames, queried_vector);
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);
	cout << "\nTime: " << HTTime.count() / k << "\n";
	cout << "Speed Up: " << double(BSTTime.count())/HTTime.count()<<endl;
	return 0;
}