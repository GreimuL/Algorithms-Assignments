/*
Knapsack Problem 
Depth-First, Breadth-First, Best-First
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

vector<pair<int, int>> items;	//profit,weight
int n, W; //number of items, Max weight

int searchbfs = 0;	//bfs number of nodes
int searchdfs = 0;	//dfs number of nodes
int searchbest = 0;	//best number of nodes

//Node struct
struct node {
	int profit;
	int weight;
	int level;
	float bound;
};
//overloading for priority_queue
bool operator<(node a, node b) {
	return a.bound < b.bound;
}
//compare function for sorting
int compare(pair<int,int> a, pair<int,int> b) {
	return (double)a.first / (double)a.second > (double)b.first / (double)b.second;
}
//Max profit for Depth First Knapsack 
int dfsmaxprofit = 0;
//promising function for Depth First Knapsack 
bool promising(node v) {
	int j, k;
	int totweight;
	float bound;
	//if current weight is greater than Max weight, v is not promising
	if (v.weight >= W) {
		return 0;
	}
	else {
		j = v.level + 1;
		bound = v.profit;
		totweight = v.weight;
		//if weight is not greater than Max weight, plus next level items
		while ((j <= n) && (totweight + items[j].second <= W)) {
			totweight += items[j].second;
			bound += items[j].first;
			j++;
		}
		k = j;
		//plus remain
		if (k <= n) {
			bound += (W - totweight)*items[k].first / items[k].second;
		}
		//if bound is greater than Max profit, v is promising
		return bound > dfsmaxprofit;
	}
}
//Depth First Knapsack
void dfsKnapsack(node v) {
	searchdfs++;
	//Update Max profit
	if (v.weight <= W && v.profit > dfsmaxprofit) {
		dfsmaxprofit = v.profit;
	}
	//if promising
	if (promising(v)) {
		node u;
		u.weight = v.weight + items[v.level + 1].second;
		u.profit = v.profit + items[v.level + 1].first;
		u.level = v.level + 1;
		v.level++;
		//push item (left child node)
		dfsKnapsack(u);
		//dont push item (right child node)
		dfsKnapsack(v);
	}
}

//bound function for Breadth First Knapsack and Best First Knapsack
float bound(node u) {
	int j, k;
	int totweight;
	float result;
	//if current weight is greater than Max weight, u is not promising
	if (u.weight>= W) {
		return 0;
	}
	else {
		result = u.profit;
		j = u.level + 1;
		totweight = u.weight;
		///if weight is not greater than Max weight, plus next level items
		while ((j <= n) && (totweight + items[j].second <= W)) {
			totweight += items[j].second;
			result += items[j].first;
			j++;
		}
		k = j;
		//plus remain
		if (k <= n) {
			result += (W - totweight)*items[k].first / items[k].second;
		}
		//return bound
		return result;
	}
}

//Breadth First Knapsack
int bfsKnapsack() {
	queue<node>q;
	//init root node
	node v;
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	int maxprofit = 0;
	q.push(v);
	searchbfs++;
	while (!q.empty()) {
		v = q.front(); 
		node u;
		q.pop();
		//left child node
		u.level = v.level + 1;
		u.profit = v.profit + items[u.level].first;
		u.weight = v.weight + items[u.level].second;
		//Update Maxprofit
		if ((u.weight <= W) && (u.profit > maxprofit)) {
			maxprofit = u.profit;
		}
		//if promising, push to queue
		if (bound(u) > maxprofit) {
			q.push(u);
		}
		//right child node
		u.weight = v.weight;
		u.profit = v.profit;
		//if promising, push to queue
		if (bound(u) > maxprofit) {
			q.push(u);
		}
		searchbfs+=2;
	}
	return maxprofit;
}

//Best First Knapsack
int bestKnapsack() {
	//priority_queue by bound size
	priority_queue<node> pq;
	//init root node
	node v;
	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	v.bound = bound(v);
	int maxprofit = 0;
	pq.push(v);
	searchbest++;
	while (!pq.empty()) {
		v = pq.top();
		node u;
		pq.pop();
		if (v.bound > maxprofit) {
			//left child node
			u.level = v.level + 1;
			u.profit = v.profit + items[u.level].first;
			u.weight = v.weight + items[u.level].second;
			//Update Max profit
			if ((u.weight <= W) && (u.profit > maxprofit)) {
				maxprofit = u.profit;
			}
			u.bound = bound(u);
			//if promising, push to priority_queue
			if (bound(u) > maxprofit) {
				pq.push(u);
			}
			//right child node
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u);
			//if promising, push to priority_queue
			if (u.bound > maxprofit) {
				pq.push(u);
			}
			searchbest += 2;
		}
	}
	return maxprofit;
}
int main() {

	/*
	input data
	n :number of items
	W : Max weight
	profit[1] weight[1]
	...
	profit[n] weight[n]

	ex)
	5
	13
	3 1
	12 3
	20 2
	30 5
	35 7
	*/
	items.push_back(make_pair(0x7fffffff, 1)); //dummy item for starting index 1
	cin >> n;	//number of items
	cin >> W;	//Max weight
	for (int i = 0; i < n; i++) {
		int p, w;	//profit, weight
		cin >> p >> w;
		items.push_back(make_pair(p, w));
	}
	//sort
	sort(items.begin(), items.end(), compare);
	//Depth First Knapsack
	cout << "DFS\n";
	node fordfs; // root node for Depth First Knapsack
	fordfs.level = 0;
	fordfs.profit = 0;
	fordfs.weight = 0;
	dfsKnapsack(fordfs);
	cout <<"Max profit: " <<dfsmaxprofit << "\n";
	cout << "Number of nodes: " << searchdfs << "\n\n";
	//Breadth First Knapcack
	cout << "BFS\n";
	cout << "Max profit: "<<bfsKnapsack()<<"\n";
	cout << "Number of nodes: "<<searchbfs << "\n\n";
	//Best First Knapsack
	cout << "BEST\n";
	cout <<"Max profit: " <<bestKnapsack() <<"\n";
	cout <<"Number of nodes: "<< searchbest << "\n\n";

	return 0;
}