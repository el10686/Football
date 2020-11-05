// Plenty of code taken from 
// https://www.geeksforgeeks.org/strongly-connected-components/?fbcl
// id=IwAR27zXJGj6rJbI9qg27keX5KOmNFS0UHMjwhbdV5sWdJUJ0J_8V3UFHyUyA

#include <iostream> 
#include <list> 
#include <stack> 
using namespace std;

class Graph 
{ 
	int V;    // No. of vertices 
	list<int> *adj;    // An array of adjacency lists 

	// Fills Stack with vertices (in increasing order of finishing 
	// times). The top element of stack has the maximum finishing  
	// time 
	void fillOrder(int v, bool visited[], stack<int> &Stack); 

	// A recursive function to print DFS starting from v 
	void DFSUtil(int v, bool visited[], int &cnt); 
	public: 
	Graph(int V); 
	void addEdge(int v, int w); 

	// The main function that finds and prints strongly connected 
	// components 
	void printSCCs(); 

	// Function that returns reverse (or transpose) of this graph 
	Graph getTranspose(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	adj = new list<int>[V]; 
} 

// A recursive function to print DFS starting from v 
void Graph::DFSUtil(int v, bool visited[], int &cnt) 
{ 
	// Mark the current node as visited and print it 
	visited[v] = true; 
	cnt++; 

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
		if (!visited[*i]) 
			DFSUtil(*i, visited, cnt); 
} 

Graph Graph::getTranspose() 
{ 
	Graph g(V); 
	for (int v = 0; v < V; v++) 
	{ 
		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i; 
		for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		{ 
			g.adj[*i].push_back(v); 
		} 
	} 
	return g; 
} 

void Graph::addEdge(int v, int w) 
{ 
	adj[v].push_back(w); // Add w to v’s list. 
} 

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) 
{ 
	// Mark the current node as visited and print it 
	visited[v] = true; 

	// Recur for all the vertices adjacent to this vertex 
	list<int>::iterator i; 
	for(i = adj[v].begin(); i != adj[v].end(); ++i) 
		if(!visited[*i]) 
			fillOrder(*i, visited, Stack); 

	// All vertices reachable from v are processed by now, push v  
	Stack.push(v); 
} 

// The main function that finds and prints all strongly connected  
// components 
void Graph::printSCCs() 
{ 
	stack<int> Stack; 

	// Mark all the vertices as not visited (For first DFS) 
	bool *visited = new bool[V]; 
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	// Fill vertices in stack according to their finishing times 
	for(int i = 0; i < V; i++) 
		if(visited[i] == false) 
			fillOrder(i, visited, Stack); 

	// Create a reversed graph 
	Graph gr = getTranspose(); 

	// Mark all the vertices as not visited (For second DFS) 
	for(int i = 0; i < V; i++) 
		visited[i] = false; 

	// Pop a vertex from stack 
	int v = Stack.top(); 
	Stack.pop();
	int flag = 1, temp;
	DFSUtil(v, visited, temp);
	for (int i = 0; i < V; i++)
		//if even one vertex isn't visited we have a disconnected graph
		//thus print 0 teams
		if(visited[i] == false) {
			flag = 0;
			break;
		}

	int cnt = 0;
	if (flag != 0) {
		for(int i = 0; i < V; i++)
			visited[i] = false;
		gr.DFSUtil(v, visited, cnt);
	}

	printf("%d\n", cnt);
} 

int main() 
{ 
	//read input and construct graph
	int N, losing, team;
	scanf("%d", &N);
	Graph g(N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &losing);
		for (int j = 0; j < losing; j++) {
			scanf("%d", &team);
			g.addEdge(team - 1, i);
		}
	}

	//print first SCC of DAG, the answer to our problem
	g.printSCCs(); 

	return 0; 
} 
