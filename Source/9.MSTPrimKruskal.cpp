/*
Minimum Spanning Tree
Prim algorithm and Kruskal Algorithm
Greimul
*/

#include<iostream>
#include<vector>
#include<algorithm>

#define NSIZE 10
#define MAX 0x7fffffff
using namespace std;
bool ckprim[NSIZE + 1];   //for Prim algorithm, include check array
vector<int> primset; //for Prim algorithm, set of seleted vertex until now
int kruskal[NSIZE + 1];   //for Kruskal, dis-jointed set
int graph[NSIZE + 1][NSIZE + 1];    //for Prim, graph
vector<pair<int, pair<int, int>>> vectorgraph;    //for Kruskal, graph

//Prim algorithm
int prim(int st) {
	int primcost = 0;
	ckprim[st] = 1; //check start vertex
	int minV = 0;   //nearest vertex
	int vertex;
	primset.push_back(st); //push start vertex
	//repeat until all vertices selected
	while (minV != -1) {
		minV = -1;
		int min = MAX;
		//seleted vertex vector
		for (auto i : primset) {
			for (int j = 1; j <= NSIZE; j++) {
				if (ckprim[j] == 0 && graph[i][j] != 0) {
					//if find nearest vertex, update
					if (min>graph[i][j]) {
						min = graph[i][j];
						minV = j;
						vertex = i;
					}
				}
			}
		}
		//ignore either vertex or minV is -1
		if (vertex == -1 || minV == -1) {
			continue;
		}
		primset.push_back(minV);	//push nearest vertex
		primcost += min;	//plus cost
		ckprim[minV] = 1;	//visit check
		//print selected edge
		cout << vertex << " " << minV << endl;
	}
	//print cost
	return primcost;
}
//Kruskal Algorithm
int krus() {
	int kruskalcost = 0;
	int color = 0;  //set division
	for (auto i : vectorgraph) {
		int cost = i.first;
		int e1 = i.second.first; //vertex1
		int e2 = i.second.second;//vertex2
		//if both vertices are not in the set
		if (kruskal[e1] == 0 && kruskal[e2] == 0) {
			//change new set division
			color++;
			//plus cost
			kruskalcost += cost;
			//push both vertices in same set
			kruskal[e1] = color;
			kruskal[e2] = color;
			//print selected edge
			cout << e1 << " " << e2 << endl;
		}
		//one vertex not in any set, but the other vertex in some set
		else if (kruskal[e1] != 0 && kruskal[e2] == 0) {
			//plus cost
			kruskalcost += cost;
			//push vertex that is not in any set to other vertex's set
			kruskal[e2] = kruskal[e1];
			//print selected edge
			cout << e1 << " " << e2 << endl;
		}
		//one vertex not in any set, but the other vertex in some set case2
		else if (kruskal[e1] == 0 && kruskal[e2] != 0) {
			//plus cost
			kruskalcost += cost;
			//push vertex that is not in any set to other vertex's set
			kruskal[e1] = kruskal[e2];
			//print selected edge
			cout << e1 << " " << e2 << endl;
		}
		//each vertex in different set
		else if (kruskal[e1] != kruskal[e2]) {
			//plus cost
			kruskalcost += cost;
			//merge two sets
			int tmp = kruskal[e1];
			for (int j = 1; j <= NSIZE; j++) {
				if (tmp == kruskal[j]) {
					kruskal[j] = kruskal[e2];
				}
			}
			//print selected edge
			cout << e1 << " " << e2 << endl;
		}
	}
	return kruskalcost;
}
int main() {

	/*
	input data
	10 13
	1 2 32
	1 4 17
	2 5 45
	4 5 10
	3 4 18
	5 6 28
	3 7 5
	4 8 3
	5 9 25
	6 10 6
	7 8 59
	8 9 4
	9 10 12
	*/

	int n; //number of vertices
	int m; //number of edges
	cin >> n >> m;

	for (int i = 0; i<m; i++) {
		int e1, e2, c; //vertex1,vertex2,cost (edge)
		cin >> e1 >> e2 >> c;
		//undirected edge
		graph[e1][e2] = c;
		graph[e2][e1] = c;
		//vector graph
		vectorgraph.push_back(make_pair(c, make_pair(e1, e2)));
	}
	//vectorgraph sorting by cost (for Kruskal)
	sort(vectorgraph.begin(), vectorgraph.end());

	cout << "Prim Algorithm\n";
	cout << "Cost: " << prim(1) << endl; //start with number 1 vertex
	cout << "Kruskal Algorithm\n";
	cout << "Cost: " << krus() << endl;
	return 0;
}