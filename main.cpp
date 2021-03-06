/******************************************************
 ** FILE: main.cpp
 **
 ** CLASS:
 ** CSE331
 **
 ** Homework 06 / Project 04
 **
 ** AUTHOR:
 ** Yousef Gtat
 **
 ** CREATION DATE:
 ** 04/01/2015
 **
 ** NOTES: I am using a dictionary to save a node with 
 **        its parent. Output 2&3 will be ordered based
 **        based on ASCII value not the flow of the graph.
 **        However, the value of the distance and parent
 **        are correct to each corresponding node.
 *******************************************************/

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<list>
#include<map>

using namespace std; 

class Graph {
	private:
		int v; //v is number of vertices in graph
		list<int> *adj; //pointer to array containing adjacency list
	public:
		Graph(int);
        ~Graph();
		void addEdge(int u, int v); //function to add edge to graph
		void BFS(int); // displays Breadth First Traversal based on starting node
        int getDistance(map<int,int> &, int);
};

//Constructor
Graph::Graph(int v) {
	this->v = v;
	adj = new list<int>[v];
}

//Destructor
Graph::~Graph()
{
    delete [] adj;
}

//add v to u's addjacent list
void Graph::addEdge(int u, int v) {
	adj[u].push_back(v);
}

//Calculates the distance between a node and the starting node
int Graph::getDistance(map<int,int> &dict, int node)
{
    if (dict[node] == -1)
    {
        return 0;
    }
    else
    {
        return (1+getDistance(dict, dict[node]));
    }

}

//Prints three outputs:
    // 1) the ouput list D
    // 2) the parent node of each node
    // 3) the distance of each node to the starting node

void Graph::BFS(int s) {
	bool *visited = new bool[v];
	cout << "BFS" << endl;
	cout << "D = ";
	//mark all vertices as not visited
	for (int i = 0; i <= v; i++)
	{
		visited[i] = false;
	}
    
    //create the BFS queue
	list<int> queue;

	//mark the first node as visited and add to queue
	visited[s] = true;
	queue.push_back(s);
    
    //creating parent dictionary
    map<int, int> parent_dict;

    //mark the first node as visited and add to queue
    int parent = -1;
    parent_dict[s]=parent;

	//i will get all adjacent vertices of a vertex
	list<int>::iterator i;

	while (!queue.empty())
	{
		//dequeue a vertext from queue and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();
        
        parent = s;
		//get all adjacent vertices of the dequeued vertex s
		//if an adjacent has not been visited mark it visited and 
		//add to the queue
		for (i = adj[s].begin(); i != adj[s].end(); i++)
		{
			if(!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
                parent_dict[*i]=parent;

			}
		}
	}
	cout << endl;
    
    //printing the parents of each node
    for ( auto it = parent_dict.begin(); it != parent_dict.end(); it++)
    {
        cout << it->first << ".p=";
        if (it->second==-1)
        {
            cout<< "nil";
        }
        else
        {
            cout << it->second;
        }
        cout << ", ";
    }
    cout<<endl;
    
    //printing the distance of each node
    for ( auto it = parent_dict.begin(); it != parent_dict.end(); it++)
    {
   
        cout << it->first << ".d=" << getDistance(parent_dict, it->first) << ", ";
    }
    cout<<endl;
    
}

//main function, takes and converts the input file
//to ints and then adds edges based on who the parent
//currently is, finally calling the BFS function 
//to display the graph
int main(int argc, char * argv[])
{
	fstream input(argv[1], ios::in);
	char ch;
	string buffer;
	string ch1 = argv[2];
	int nodeStart = atoi(ch1.c_str());
	cout << "starting node: " << nodeStart << endl;
	int parent;
	ch = input.get();
	buffer += ch;
	int numNodes = atoi(buffer.c_str());
	cout << "Number of Nodes: " << numNodes << endl;
	buffer.clear();
	Graph graph(numNodes+1);

	while(!input.eof())
	{
		ch = input.get();
		if (isdigit(ch))
		{
			buffer += ch;
			
		}
		else if (ch == ' ')
		{
			int number = atoi(buffer.c_str());
			buffer.clear();
			graph.addEdge(parent, number);
		}
		else if (ch == ':') 
		{
			parent = atoi(buffer.c_str());
			buffer.clear();
		}
		else if (ch == '\n' && !buffer.empty() )
		{
			int number = atoi(buffer.c_str());
			buffer.clear();
			graph.addEdge(parent, number);
		}

	}
    
    cout<<endl;
	graph.BFS(nodeStart);
    cout<<endl;
    
	return 0;
}


