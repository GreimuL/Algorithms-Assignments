/*
Traveling Salesperson Problem Dynamic Programming with Bitmask
GreimuL
*/

#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 0x3f3f3f3f
#define NSIZE 5	//Graph size
using namespace std;

//Graph
int W[NSIZE][NSIZE] =
{ 0,8,13,18,20,
3,0,7,8,10,
4,11,0,10,7,
6,6,7,0,11,
10,6,2,1,0 };
//DP array
int D[NSIZE][32];   //2^5 = 32
//TSP function
int tsp(int now, int vis) {
	//if visited all
	if (vis == (1 << NSIZE) - 1) {
		if (W[now][0] != 0) {
			//if can go, return distance
			return W[now][0];
		}
		else {
			//if cant go, return cant
			return MAX;
		}
	}
	//if dp array has value, return value
	if (D[now][vis] != MAX) {
		return D[now][vis];
	}
	D[now][vis] = MAX;
	for (int i = 0; i < NSIZE; i++) {
		//if already visited, skip
		if (vis & (1 << i)) {
			continue;
		}
		//if cant go, skip
		if (W[now][i] == 0) {
			continue;
		}
		//update DP array
		D[now][vis] = min(D[now][vis], tsp(i, vis | (1 << i)) + W[now][i]);
	}
	return D[now][vis];
}
//print Path
void printpath(int dis) {
	int st = 0;
	int ck = 1;
	int cnt = 0;
	int *mis = new int[NSIZE];
	//print Start vertex
	cout << "v1 ";
	while (cnt != NSIZE - 2) {
		for (int i = 0; i < NSIZE; i++) {
			if (dis - W[st][i] == D[i][ck + (1 << i)]) {
				cout << "v" << i + 1 << " "; //print vertex
				dis -= W[st][i]; //minus distance
				st = i; //update start vertex
				mis[i] = 1; //if visit, check
				ck += 1 << i; //update ck value
				cnt++;
			}
		}
	}
	//print last vertex
	for (int i = 1; i < NSIZE; i++) {
		if (mis[i] != 1) {
			cout << "v" << i + 1 << " ";
		}
	}
	delete mis;
	//print destination
	cout << "v1";
}
int main() {
	for (int i = 0; i < NSIZE; i++) {
		for (int j = 0; j < 32; j++) {
			D[i][j] = MAX;
		}
	}
	int distance = tsp(0, 1);
	cout <<"distance : "<< distance << endl;
	printpath(distance);
	return 0;
}