/*
Greimul
Sum of Subsets problem by Bactracking
Analayze Sum of subsets problem by MonteCarlo
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<ctime>
#define NSIZE 6	//Size of Numbers
using namespace std;

int inputarr[NSIZE];//INPUT
bool include[NSIZE];//Check inclusion
int W;//Target Sum
int node = 0;//SumofSubsets, Number of nodes searched
int node2 = 0;//modifiedAlgorithm, Number of nodes searched
//Promising check
bool promising(int ind, int weight, int total) {
	return (weight + total >= W) && (weight == W || weight + inputarr[ind + 1] <= W);
}
//Sum of Subsets Algorithm
void sumofsubsets(int ind, int weight, int total) {
	node++;
	//Promising check
	if (promising(ind, weight, total)) {
		//if current weight is target weight
		if (weight == W) {
			//print current set
			cout << "SubSet: ";
			for (int i = 0; i < NSIZE; i++) {
				if (include[i] != 0) {
					cout << inputarr[i] << " ";
				}
			}
			cout << "\n";
		}
		else {
			//include number
			include[ind + 1] = 1;
			sumofsubsets(ind + 1, weight + inputarr[ind + 1], total - inputarr[ind + 1]);
			//do not include number
			include[ind + 1] = 0;
			sumofsubsets(ind + 1, weight, total - inputarr[ind + 1]);
		}
	}
}

bool finish = false; //finish check value
//ModifiedSubset Algorithm (Exit if you find a set that satisfied target weight)
void ModifiedSubset(int ind, int weight, int total) {
	node2++;
	//Promising check
	if (promising(ind, weight, total)) {
		//if current weight is target weight
		if (weight == W && finish == false) {
			cout << "ModifiedSubset: ";
			for (int i = 0; i < NSIZE; i++) {
				if (include[i] != 0) {
					cout << inputarr[i] << " ";
				}
			}
			cout << "\n";
			finish = true; //check find value
		}
		else {
			//if you haven't found a set yet, continue
			if (finish == false) {
				include[ind + 1] = 1;
				ModifiedSubset(ind + 1, weight + inputarr[ind + 1], total - inputarr[ind + 1]);
				include[ind + 1] = 0;
				ModifiedSubset(ind + 1, weight, total - inputarr[ind + 1]);
			}
		}
	}
}
//MonteCarlo Algorithm
int MonteCarlo(int totalweight) {
	int v;
	int weight = 0;
	int m, mprod, t, numnodes;
	v = 0; //array index
	numnodes = 1;
	m = 1;
	mprod = 1;
	while (m != 0) {
		t = 2;	//each node has 2 children
		mprod *= m;	//
		numnodes += mprod * t;//number of node to search
		m = 0; //init
		//Promising check
		bool left = false;
		bool right = false;
		//leftnode,(if include v)
		if (promising(v+1,weight+inputarr[v],totalweight-inputarr[v])) {
			m++;
			left = true;
		}//rightnode,(if do not include v)
		if (promising(v + 1, weight, totalweight - inputarr[v])) {
			m++;
			right = true;
		}
		
		if (m != 0) {
			if (m == 2) {//if both 2 children are Promising
				int randomselect = rand() %2;//random select one of the two
				if (randomselect==0) {//if leftnode (include v)
					weight += inputarr[v];
					totalweight -= inputarr[v];
				}
				else {//if rightnode (do not include v)
					totalweight -= inputarr[v];
				}
			}
			else {//Only one of them is promising
			//select promising node
				if (left == true) {
					weight += inputarr[v];
					totalweight -= inputarr[v];
				}
				else {
					totalweight -= inputarr[v];
				}
			}
		}
		//next number
		v++;
	}
	return numnodes;
}
int main() {
	srand((unsigned int)time(0));//random seed
	/*
	Input data
	52
	2 10 13 17 22 42
	*/
	int totalweight = 0;
	cin >> W; //Target Weight
	//Input
	for (int i = 0; i < NSIZE; i++) {
		cin >> inputarr[i];
		totalweight += inputarr[i];
	}
	cout << "\n";
	//Sort
	sort(inputarr, inputarr + NSIZE);
	//Sum of subsets algorithm by Bactracking
	sumofsubsets(-1, 0, totalweight);
	cout <<"Number of nodes searched:" << node << "\n\n";

	//Modified Algorithm
	ModifiedSubset(-1, 0, totalweight);
	cout << "Number of nodes searched:" << node2 << "\n\n";

	//MonteCarlo Algorithm 100 times average
	int avg = 0;
	for (int i = 0; i < 100; i++) {
		int value =MonteCarlo(totalweight);
		avg += value;
	}
	cout << "MonteCarlo(100times average): " << avg / 100 << "\n";
	return 0;
}