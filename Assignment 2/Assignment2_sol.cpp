

/*
**PLEASE REBUILD SOLUTION BETWEEN EACH EXECUTION
**SOMETIMES PROGRAM STOPS AT THE BEGINING
**IT MAY BE RELATED TO THE COMMAND
**THAT GULSEN HOCA SENT US 
**#pragma comment(linker, "/STACK:2000000")
**
*/




#include <iostream>
#include <string>
#include <fstream>
#include "AVLSearchTree.h"
#include "AVLSearchTree.cpp"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include <chrono>
#pragma comment(linker, "/STACK:2000000")
using namespace std;


struct itemNode{
	string item_name;
	string item_info;

	itemNode(string name, string info): item_name(name), item_info(info){}

	bool operator==(const itemNode &rhs){
		return(item_name == rhs.item_name );
	}
};
bool operator>(const itemNode &a, const itemNode &b)
{
	return (a.item_name > b.item_name);
}
bool operator>=(const itemNode &a, const itemNode &b)
{
	return (a.item_name >= b.item_name);
}
bool operator<(const itemNode &a, const itemNode &b)
{
	return (a.item_name < b.item_name);
}
bool operator<=(const itemNode &a, const itemNode &b)
{
	return (a.item_name <= b.item_name);
}
ostream& operator<<(ostream& os, const itemNode& node)
{
	return os << node.item_name <<endl;
}


struct BSTTreeNode{
	BinarySearchTree<itemNode> tree;
	string section_name;

	BSTTreeNode(BinarySearchTree<itemNode> & _tree, string name): tree(_tree), section_name(name){}

	bool operator==(const BSTTreeNode &rhs){
		return(section_name == rhs.section_name );
	}
};
bool operator>(const BSTTreeNode &a, const BSTTreeNode &b)
{
	return (a.section_name > b.section_name);
}
bool operator>=(const BSTTreeNode &a, const BSTTreeNode &b)
{
	return (a.section_name >= b.section_name);
}
bool operator<(const BSTTreeNode &a, const BSTTreeNode &b)
{
	return (a.section_name < b.section_name);
}
bool operator<=(const BSTTreeNode &a, const BSTTreeNode &b)
{
	return (a.section_name <= b.section_name);
}
ostream& operator<<(ostream& os, const BSTTreeNode& node)
{
	return os << node.section_name <<endl;
}

struct AVLTreeNode{
	AvlTree<itemNode> tree;
	string section_name;

	AVLTreeNode(AvlTree<itemNode> & _tree, string name): tree(_tree), section_name(name){}

	bool operator==(const AVLTreeNode &rhs){
		return(section_name == rhs.section_name );
	}

};
bool operator>(const AVLTreeNode &a, const AVLTreeNode &b)
{
	return (a.section_name > b.section_name);
}
bool operator>=(const AVLTreeNode &a, const AVLTreeNode &b)
{
	return (a.section_name >= b.section_name);
}
bool operator<(const AVLTreeNode &a, const AVLTreeNode &b)
{
	return (a.section_name < b.section_name);
}
bool operator<=(const AVLTreeNode &a, const AVLTreeNode &b)
{
	return (a.section_name <= b.section_name);
}
ostream& operator<<(ostream& os, const AVLTreeNode& node)
{
	return os << node.section_name <<endl;
}




int main()
{
	cout << "Welcome to the Notebook! \n"<<endl;
	string fileName = "data.txt";

	AvlTree<AVLTreeNode> AvlParent(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), "NF"));
	BinarySearchTree<BSTTreeNode> BstParent(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), "NF"));

	long long avl_time=0, bst_time=0;
	ifstream myfile;
    myfile.open(fileName);
    string line; 
	getline(myfile, line);
	string title = line;
	while (getline(myfile, line))
    {
		AVLTreeNode a = AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title);
		BSTTreeNode b = BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), title);
		
		line= line.substr(1);
		string _title = "";
		string info;
		for(int i = 0; line[i] != '-'; i++)
		{
			_title += line[i];
			info = line.substr(i+2);
		}

		//
		auto start_1 = chrono::high_resolution_clock::now();
		a.tree.insert(itemNode(_title, info));
		auto end_1 = chrono::high_resolution_clock::now();
		avl_time += (end_1 - start_1).count() / 1000.0;

		auto start_2 = chrono::high_resolution_clock::now();
		b.tree.insert(itemNode(_title, info));
		auto end_2 = chrono::high_resolution_clock::now();
		bst_time += (end_2 - start_2).count() / 1000.0;
        while (getline(myfile, line) && line[0] == '-')
		{
			line= line.substr(1);
			_title = "";
			for(int i = 0; line[i] != '-'; i++)
			{
				_title += line[i];
				info = line.substr(i+2);
			}
			auto start_3 = chrono::high_resolution_clock::now();
			a.tree.insert(itemNode(_title, info));
			auto end_3 = chrono::high_resolution_clock::now();
			avl_time += (end_3 - start_3).count() / 1000.0;

			auto start_4 = chrono::high_resolution_clock::now();
			b.tree.insert(itemNode(_title, info));
			auto end_4 = chrono::high_resolution_clock::now();
			bst_time += (end_4 - start_4).count() / 1000.0;
		}
		auto start = chrono::high_resolution_clock::now();
		AvlParent.insert(a);
		auto end = chrono::high_resolution_clock::now();
		avl_time +=(end - start).count() / 1000.0;
		cout << "Section \""<<title<<"\" has been inserted into the AVL notebook."<<endl;
		cout << "[AVL] Elapsed time: "<< avl_time << " microseconds"<<endl;
		avl_time = 0;
		auto start_b = chrono::high_resolution_clock::now();
		BstParent.insert(b);
		auto end_b = chrono::high_resolution_clock::now();
		bst_time +=(end_b - start_b).count() / 1000.0;

		cout << "Section \""<<title<<"\" has been inserted into the BST notebook."<<endl;
		cout << "[BST] Elapsed time: "<< bst_time << " microseconds"<<endl;
		bst_time = 0;
		title = line;
    }


	cout<< "\nMENU"<<endl;
	cout<<"Please enter an input between [1 - 6]:"<<endl;
    cout<<"1- Display the sections [AVL]"<<endl;
    cout<<"2- Display the sections [BST]"<<endl;
    cout<<"3- Select a section"<<endl;
    cout<<"4- Add new section"<<endl;
	cout<<"5- Delete a section"<<endl;
    cout<<"6- Exit\n"<<endl;
	
	int option;
	cout<<"Input: ";
    cin>>option;
	

	while (option!=6)
    {

        if (option==1)
        {
			cout << "\n*****"<<endl;
			AvlParent.printTree();
			cout << "*****\n" <<endl;
        }
        else if (option==2)
        {
			cout << "\n*****"<<endl;
			BstParent.printTree();
			cout << "*****\n" <<endl;
        }
        else if (option==3)
        {
			string section;
			cout << "Enter the title of the section: ";
			cin.ignore();
			getline(cin, section);
			AVLTreeNode curr_section_avl = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section));
			BSTTreeNode curr_section_bst = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), section));
			if(AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section)).section_name == section)
			{
				cout << "Selected section -> "<<section<<endl;
				int choice;
				cout<< "Please enter an input between [1 - 7]:"<<endl;
				cout<<"1- Display the items [AVL]"<<endl;
				cout<<"2- Display the items [BST]"<<endl;
				cout<<"3- Display the information of a item"<<endl;
				cout<<"4- Add new item"<<endl;
				cout<<"5- Update the information of a item"<<endl;
				cout<<"6- Delete an item"<<endl;
				cout<<"7- Return to main menu"<<endl;
				cout<<"Input: ";
				cin >> choice;
				while (choice !=7)
				{
					if(choice == 1)
					{
						cout << "\n*****"<<endl;
						curr_section_avl.tree.printTree();
						cout << "*****\n"<<endl;
					}
					else if(choice ==2)
					{
						cout << "\n*****"<<endl;
						curr_section_bst.tree.printTree();
						cout << "\n*****"<<endl;
					}
					else if(choice ==3)
					{
						string title_find;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin, title_find);

						auto start = chrono::high_resolution_clock::now();
						AVLTreeNode curr_section_avl_ = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _a =curr_section_avl.tree.find(itemNode(title_find, "")); 
						auto end = chrono::high_resolution_clock::now();
						long long avl = (end - start).count() / 1000.0;
						cout << "[AVL] Elapsed time: "<< avl << " microseconds"<<endl;

						auto start_b = chrono::high_resolution_clock::now();
						BSTTreeNode curr_section_bst_ = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _b =curr_section_bst.tree.find(itemNode(title_find, "")); 
						auto end_b = chrono::high_resolution_clock::now();
						long long bst = (end_b - start_b).count() / 1000.0;
						cout << "[BST] Elapsed time: "<< bst << " microseconds"<<endl;
						if(_a.item_name != title_find)
						{
							cout << "Invalid title." <<endl;
						}
						else
						{
							cout << _a.item_info <<endl <<endl;
						}
					}
					else if(choice ==4)
					{
						string title_find;
						cout << "Enter a title for the item: ";
						cin.ignore();
						getline(cin, title_find);

						long long avl=0, bst=0;
						auto start_1 = chrono::high_resolution_clock::now();
						AVLTreeNode curr_section_avl_ = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _a =curr_section_avl.tree.find(itemNode(title_find, "")); 
						auto end_1 = chrono::high_resolution_clock::now();

						avl += (end_1 - start_1).count() / 1000.0;

						auto start_2 = chrono::high_resolution_clock::now();
						BSTTreeNode curr_section_bst_ = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _b =curr_section_bst.tree.find(itemNode(title_find, "")); 
						auto end_2 = chrono::high_resolution_clock::now();
						bst += (end_2 - start_2).count() / 1000.0;
						if(_a.item_name == title_find)
						{
							cout << "Item \""<<title_find<<"\" already exists in the "<<section<<"." <<endl;
						}
						else
						{
							cin.clear();
							string description;
							cout << "Enter a description for the item: ";
							getline(cin, description);
							auto start = chrono::high_resolution_clock::now();
							curr_section_avl.tree.insert(itemNode(title_find, description));
							AvlParent.updateElement(curr_section_avl, curr_section_avl);
							auto end = chrono::high_resolution_clock::now();
							
							avl += (end - start).count() / 1000.0;
							cout << "[AVL] Elapsed time: "<< avl << " microseconds"<<endl;

							auto start_3 = chrono::high_resolution_clock::now();
							curr_section_bst.tree.insert(itemNode(title_find, description));
							BstParent.updateElement(curr_section_bst, curr_section_bst);
							auto end_3 = chrono::high_resolution_clock::now();

							bst +=(end_3 - start_3).count(); 
							cout << "[BST] Elapsed time: "<< bst << " microseconds"<<endl;
							cout << "The new item \""<<title_find<<"\" has been inserted."<<endl<<endl;
						}
					}
					else if(choice ==5)
					{
						long long avl = 0;
						long long bst = 0;
						string title_find;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin, title_find);
						auto start_1 = chrono::high_resolution_clock::now();
						AVLTreeNode curr_section_avl_ = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _a =curr_section_avl.tree.find(itemNode(title_find, ""));
						auto end_1 = chrono::high_resolution_clock::now();
						avl += (end_1 - start_1).count() / 1000.0;

						auto start_2 = chrono::high_resolution_clock::now();
						BSTTreeNode curr_section_bst_ = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _b =curr_section_bst.tree.find(itemNode(title_find, "")); 
						auto end_2 = chrono::high_resolution_clock::now();
						bst += (end_2 - start_2).count() / 1000.0;
						cout << "[AVL] Elapsed time: "<< avl << " microseconds"<<endl;
						cout << "[BST] Elapsed time: "<< bst << " microseconds"<<endl;

						if(_a.item_name != title_find)
						{
							
							cout << "Item \""<<title_find<<"\" does not exist in the \""<<section<<"\"." <<endl;
						}
						else
						{
							cin.clear();
							string new_info;
							cout << "Enter the new information: ";
							getline(cin, new_info);
							
							curr_section_avl.tree.updateElement(itemNode(title_find, ""), itemNode(title_find, new_info));
							AvlParent.updateElement(curr_section_avl, curr_section_avl);
							curr_section_bst.tree.updateElement(itemNode(title_find, ""), itemNode(title_find, new_info));
							BstParent.updateElement(curr_section_bst, curr_section_bst);
							cout << "The content \""<<title_find<<"\" has been updated."<<endl<<endl;
						}
						
					}
					else if(choice ==6)
					{
						long long bst=0, avl=0;
						string title_find;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin, title_find);
						auto start_1 = chrono::high_resolution_clock::now();
						AVLTreeNode curr_section_avl_ = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _a =curr_section_avl.tree.find(itemNode(title_find, "")); 
						auto end_1 = chrono::high_resolution_clock::now();
						avl+= (end_1 - start_1).count() / 1000.0;

						auto start_2 = chrono::high_resolution_clock::now();
						BSTTreeNode curr_section_bst_ = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), section));
						itemNode _b =curr_section_bst.tree.find(itemNode(title_find, "")); 
						auto end_2 = chrono::high_resolution_clock::now();
						bst+= (end_2 - start_2).count() / 1000.0;

						if(_a.item_name != title_find)
						{
							cout << "Item \""<<title_find<<"\" does not exist in the \""<<section<<"\"." <<endl;
						}
						else
						{
							auto start = chrono::high_resolution_clock::now();
							curr_section_avl.tree.remove(itemNode(title_find, ""));
							AvlParent.updateElement(curr_section_avl, curr_section_avl);
							auto end = chrono::high_resolution_clock::now();
							avl+= (end - start).count() / 1000.0;
							cout << "[AVL] Elapsed time: "<< avl << " microseconds"<<endl;
							
							auto start_3 = chrono::high_resolution_clock::now();
							curr_section_bst.tree.remove(itemNode(title_find, ""));
							BstParent.updateElement(curr_section_bst, curr_section_bst);
							auto end_3 = chrono::high_resolution_clock::now();
							bst+= (end_3 - start_3).count() / 1000.0;

							cout << "[BST] Elapsed time: "<< bst << " microseconds"<<endl;
							cout << "The item \""<<title_find<<"\" has been deleted."<<endl<<endl;
						}
					}
					cout<<"Input: ";
					cin >> choice;
				}
				cout<< "\nMENU"<<endl;
				cout<<"Please enter an input between [1 - 6]:"<<endl;
				cout<<"1- Display the sections [AVL]"<<endl;
				cout<<"2- Display the sections [BST]"<<endl;
				cout<<"3- Select a section"<<endl;
				cout<<"4- Add new section"<<endl;
				cout<<"5- Delete a section"<<endl;
				cout<<"6- Exit\n"<<endl;


			}
			else
			{
				cout << "Invalid title!" <<endl;
			}
        }
        else if (option==4)
        {
			string title_find;
			cout << "Enter a title for the section: ";
			cin.ignore();
			getline(cin, title_find);
			AVLTreeNode curr_section_avl = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find));
			BSTTreeNode curr_section_bst = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), title_find));
			if(curr_section_avl == AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find))
			{
				cout << "Section \""<<title_find<<"\" already exists."<<endl;
			}
			else
			{
				AvlParent.insert(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find));
				BstParent.insert(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), title_find));
				cout << "The new section \""<<title_find<<"\" has been inserted."<<endl<<endl;
			}
        }
        else if (option==5)
        {
            string title_find;
			cout << "Enter the title of the section: ";
			cin.ignore();
			getline(cin, title_find);
			AVLTreeNode curr_section_avl = AvlParent.find(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find));
			BSTTreeNode curr_section_bst = BstParent.find(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), title_find));
			if(!(curr_section_avl == AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find)))
			{
				cout << "Section \""<<title_find<<"\" does not exist."<<endl;
			}
			else
			{
				AvlParent.remove(AVLTreeNode(AvlTree<itemNode>(itemNode("NF", "NF")), title_find));
				BstParent.remove(BSTTreeNode(BinarySearchTree<itemNode>(itemNode("NF", "NF")), title_find));
				cout << "The section has been deleted."<<endl<<endl;
			}
        }
        cout<<"Input: ";
		cin>>option;
    }
	return 0;
}