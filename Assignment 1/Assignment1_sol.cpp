#include <iostream>
#include <vector>
#include "stack.h"
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct cell
	// A struct that contains the coordinate, the walls and visited information of the cell
{
	int x_coordinate;
	int y_coordinate;
	int left_wall;
	int right_wall;
	int top_wall;
	int bottom_wall;
	bool isVisited;

	//constructor
	cell(int y, int x)
	{
		//all walls exist initially
		x_coordinate = x;
		y_coordinate = y;
		left_wall = 1;
		right_wall= 1;
		top_wall= 1;
		bottom_wall= 1;
		isVisited= false;
	}
};
void maze_generator(vector< vector<cell> > & maze);
void maze_printer(vector< vector< vector<cell> > > & mazes);
bool is_neighbours_visited(int _x, int _y,vector< vector<cell> > & maze);
void path_generator(vector< vector<cell> > & maze, int x_ent, int y_ent, int x_ex, int y_ex, int maze_id);
void reset_visits(vector< vector<cell> > & maze);

int main()
{
	int number_of_maze, rows, columns;
	cout << "Enter the number of mazes: ";
	cin >> number_of_maze;
	cout << "Enter the number of rows and columns (M and N): ";
	cin>> rows>> columns;

	vector< vector< vector<cell> > > mazes;

	//create the mazes with given properties, initially all cells have 4 walls around
	for(int k=0; k<number_of_maze; k++)
	{
		vector< vector <cell> > maze;
		mazes.push_back(maze);
		for(int i=0; i<rows; i++)
		{
			vector<cell> row_vector;
			mazes[k].push_back(row_vector);
			for(int j=0; j<columns; j++)
			{
				mazes[k][i].push_back(cell(i, j));
			}
		}
	}

	//for each maze, generate a random maze pattern
	for(int k=0; k<number_of_maze; k++)
	{
		maze_generator(mazes[k]);
	}
	
	//save the mazes as a txt file
	maze_printer(mazes);
	cout<<"All mazes are generated."<<endl<<endl;

	//inputs for path finder
	int maze_id, x_entry, y_entry, x_exit, y_exit;
	cout << "Enter a maze ID between 1 to "<<number_of_maze<<" inclusive to find a path: ";
	cin >> maze_id;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> x_entry>>y_entry;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin>> x_exit>>y_exit;

	//reset visits in order to generate the path for the maze
	reset_visits(mazes[maze_id-1]);

	//generate and save the path as a txt file
	path_generator(mazes[maze_id-1], x_entry, y_entry, x_exit, y_exit, maze_id);
	return 0;
}

void maze_generator(vector< vector<cell> > & maze)
{
	Stack<cell> cell_stack;
	cell_stack.push(maze[0][0]);
	maze[0][0].isVisited= true;
	int rows = maze.size();
	int columns = maze[0].size();
	int counter=-1;
	int _x = 0;
	int _y = 0;

	while(!cell_stack.isEmpty())
	{
		
		int rand_int = rand() % 4; // 0-> right, 1->left, 2->up, 3->down
		

		//We need to check whether all 4 directions are tried. 
		//If every number between 0-3 inlusive are tried, counter becomes 3
		if(rand_int - 1 == counter)
		{
			counter = rand_int;
		}

		//if we want to go right, the cell should not be the rightmost cell of a row.
		//also the cell that is in the right should not be visited.
		if((rand_int == 0 && _x < columns-1) && !maze[_y][_x+1].isVisited)
		{
			maze[_y][_x].right_wall = 0;
			maze[_y][_x+1].left_wall= 0;
			cell_stack.push(maze[_y][_x+1]);
			maze[_y][_x+1].isVisited= true;
			_x++;
			counter=-1;
		}

		//if we want to go left, the cell should not be the leftmost cell of a row.
		//also the cell that is in the left should not be visited.
		else if((rand_int == 1 && _x > 0) && !maze[_y][_x-1].isVisited)
		{
			maze[_y][_x].left_wall= 0;
			maze[_y][_x-1].right_wall = 0;
			cell_stack.push(maze[_y][_x-1]);
			maze[_y][_x-1].isVisited= true;
			_x--;
			counter=-1;
		}

		//if we want to go up, the cell should not be the upmost cell of a column.
		//also the cell that is in the top should not be visited.
		else if((rand_int == 2 && _y < rows-1) && !maze[_y+1][_x].isVisited)
		{
			maze[_y][_x].top_wall= 0;
			maze[_y+1][_x].bottom_wall = 0;
			cell_stack.push(maze[_y+1][_x]);
			maze[_y+1][_x].isVisited= true;
			_y++;
			counter=-1;
		}

		//if we want to go down, the cell should not be the downmost cell of a column.
		//also the cell that is in the bottom should not be visited.
		else if((rand_int == 3 && _y > 0) && !maze[_y-1][_x].isVisited)
		{
			maze[_y][_x].bottom_wall= 0;
			maze[_y-1][_x].top_wall = 0;
			cell_stack.push(maze[_y-1][_x]);
			maze[_y-1][_x].isVisited= true;
			_y--;
			counter=-1;
		}

		//if four side of the cell is either visited or does not exist
		else if(counter == 3 && !cell_stack.isEmpty())
		{
			//return to the previous cell until it has unvisited cell
			cell_stack.pop();
			if(!cell_stack.isEmpty())
			{
				//update the coordinates
				_x = cell_stack.top().x_coordinate;
				_y = cell_stack.top().y_coordinate;
			}
			counter=-1;
		}
	}
}

void maze_printer(vector< vector< vector<cell> > > & mazes)
{
	//for every maze that we generate
	for(int k = 0; k < mazes.size(); k++)
	{
		//open the file with the maze id
		ofstream file("maze_"+ to_string(k+1) +".txt");

		//write down the dimensions of the maze
		file << mazes[0].size() << " " << mazes[0][0].size()<<endl;

		//write down the information of every cell
		for(int i=0; i < mazes[0].size(); i++)
		{
			for(int j=0; j < mazes[0][0].size(); j++)
			{
				file << "x="<< j<<" y=" << i<< " l=" << mazes[k][i][j].left_wall<< " r="<< mazes[k][i][j].right_wall
					<< " u="<< mazes[k][i][j].top_wall<< " d=" << mazes[k][i][j].bottom_wall<<endl;
			}
		}
	}
}

void path_generator(vector< vector<cell> > & maze, int x_ent, int y_ent, int x_ex, int y_ex, int maze_id)
{
	Stack<cell> cell_stack;
	cell_stack.push(maze[y_ent][x_ent]);
	maze[y_ent][x_ent].isVisited= true;
	int rows = maze.size();
	int columns = maze[0].size();
	int counter=-1;
	int _x = x_ent;
	int _y = y_ent;
	int visited = 0;

	while(cell_stack.top().x_coordinate != x_ex || cell_stack.top().y_coordinate != y_ex)
	{
		
		int rand_int = rand() % 4; // 0-> right, 1->left, 2->up, 3->down
		
		//We need to check whether all 4 directions are tried. 
		//If every number between 0-3 inlusive are tried, counter becomes 3
		if(rand_int - 1 == counter)
		{
			counter = rand_int;
		}

		//if we want to go right, the cell should not be the rightmost cell of a row.
		//also the cell that is in the right should not be visited and the right wall of the cell should not exist
		if((rand_int == 0 && _x < columns-1) && !maze[_y][_x+1].isVisited && maze[_y][_x].right_wall == 0)
		{
			cell_stack.push(maze[_y][_x+1]);
			maze[_y][_x+1].isVisited= true;
			_x++;
			visited++;
			counter=-1;
		}

		//if we want to go left, the cell should not be the leftmost cell of a row.
		//also the cell that is in the left should not be visited and the left wall of the cell should not exist
		else if((rand_int == 1 && _x > 0) && !maze[_y][_x-1].isVisited && maze[_y][_x].left_wall== 0)
		{
			cell_stack.push(maze[_y][_x-1]);
			maze[_y][_x-1].isVisited= true;
			_x--;
			visited++;
			counter=-1;
		}

		//if we want to go up, the cell should not be the upmost cell of a column.
		//also the cell that is in the top should not be visited and the top wall of the cell should not exist
		else if((rand_int == 2 && _y < rows-1) && !maze[_y+1][_x].isVisited && maze[_y][_x].top_wall== 0)
		{
			cell_stack.push(maze[_y+1][_x]);
			maze[_y+1][_x].isVisited= true;
			_y++;
			visited++;
			counter=-1;
		}

		//if we want to go down, the cell should not be the downmost cell of a column.
		//also the cell that is in the bottom should not be visited and the bottom wall of the cell should not exist
		else if((rand_int == 3 && _y > 0) && !maze[_y-1][_x].isVisited && maze[_y][_x].bottom_wall== 0)
		{
			cell_stack.push(maze[_y-1][_x]);
			maze[_y-1][_x].isVisited= true;
			_y--;
			visited++;
			counter=-1;
		}

		//if all 4 side is tried
		else if(counter == 3 && !cell_stack.isEmpty())
		{
			//return to the previous cell until it has unvisited cell
			cell_stack.pop();
			if(!cell_stack.isEmpty())
			{
				//update the coordinates
				_x = cell_stack.top().x_coordinate;
				_y = cell_stack.top().y_coordinate;
			}
			counter=-1;
		}
	}
	//create the txt file that we are going to write down the solution path
	ofstream file("maze_"+to_string(maze_id)+"_path_"+to_string(x_ent)+"_"+to_string(y_ent)+"_"+to_string(x_ex)+"_"+to_string(y_ex)+".txt");
	Stack<cell> helper;

	//for reversing the stack, put all element into a helper stack
	while(!cell_stack.isEmpty())
	{
		helper.push(cell_stack.topAndPop());
	}

	//while poping from helper stack, write down solution path to the txt file
	while(!helper.isEmpty())
	{
		file<< helper.top().x_coordinate << " "<< helper.top().y_coordinate<<endl;
		helper.pop();
	}

}

void reset_visits(vector< vector<cell> > & maze)
//Reset visits between maze generation and solýtion path generation
{
	for(int i = 0; i< maze.size() ; i++)
	{
		for(int j= 0; j< maze[0].size(); j++)
		{
			maze[i][j].isVisited = false;
		}
	}
}