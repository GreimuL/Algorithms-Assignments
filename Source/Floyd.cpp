/*
Greimul

Floyd Warshall Algorithm
*/
#include<iostream>
#include<vector>
#define MAX 0x3f3f3f3f
using namespace std;

//for problem 3,4
int D[10][10];
int P[10][10];
//for problem 5,6
int D2[10][10];
int P2[10][10];
//Shortest Path
vector<int> v;
vector<int> v2;

//print shortest path for problem 3,4
void path(int q, int r) {
	cout << "path(" << q << "," << r << ")\n";
	if (P[q][r] != 0) {
		path(q, P[q][r]);
		v.push_back(P[q][r]);
		path(P[q][r], r);
	}
}

//print shortest path for problem 5,6
void path2(int q, int r) {
	cout << "path(" << q << "," << r << ")\n";
	if (P2[q][r] != 0) {
		path2(q, P2[q][r]);
		v2.push_back(P2[q][r]);
		path2(P2[q][r], r);
	}
}

int main() {
	//array initial setting
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			D[i][j] = MAX;
			D2[i][j] = MAX;
			if (i == j) {
				D[i][j] = 0;
				D2[i][j] = 0;
			}
			P[i][j] = 0;
			P2[i][j] = 0;
		}
	}

	//problem 3,4 graph
	D[1][2] = 4;
	D[1][6] = 10;
	D[2][1] = 3;
	D[2][4] = 18;
	D[3][2] = 6;
	D[4][2] = 5;
	D[4][3] = 15;
	D[4][5] = 2;
	D[4][6] = 19;
	D[4][7] = 5;
	D[5][3] = 12;
	D[5][4] = 1;
	D[6][7] = 10;
	D[7][4] = 8;
	//problem 5,6 graph
	D2[7][6] = 4;
	D2[7][2] = 10;
	D2[6][7] = 3;
	D2[6][4] = 18;
	D2[5][6] = 6;
	D2[4][6] = 5;
	D2[4][5] = 15;
	D2[4][3] = 2;
	D2[4][2] = 19;
	D2[4][1] = 5;
	D2[3][5] = 12;
	D2[3][4] = 1;
	D2[2][1] = 10;
	D2[1][4] = 8;

	//Floyd's algorithm
	cout << "Floyd step by step\n";
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			for (int k = 1; k <= 7; k++) {
				if (D[j][k] > D[j][i] + D[i][k]) {
					D[j][k] = D[j][i] + D[i][k];
					P[j][k] = i;
				}
				if (D2[j][k] > D2[j][i] + D2[i][k]) {
					D2[j][k] = D2[j][i] + D2[i][k];
					P2[j][k] = i;
				}
			}
		}
		//Show Floyd by 7 step
		cout << i << "step" << endl;
		cout << "Matrix D\n";
		for (int i = 1; i <= 7; i++) {
			for (int j = 1; j <= 7; j++) {
				if (D[i][j] != MAX) {
					cout << D[i][j] << " ";
				}
				else {
					cout << 0 << " ";
				}
			}
			cout << "\n";
		}
		cout << "Matrix P\n";
		for (int i = 1; i <= 7; i++) {
			for (int j = 1; j <= 7; j++) {
				cout << P[i][j] << " ";
			}
			cout << "\n";
		}
	}
	cout << "\nProblem 3,4\n";
	//print Problem 3
	cout << "Matrix D\n";
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			if (D[i][j] != MAX) {
				cout << D[i][j] << " ";
			}
			else {
				cout << 0 << " ";
			}
		}
		cout << "\n";
	}
	cout << "Matrix P\n";
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			cout << P[i][j] << " ";
		}
		cout << "\n";
	}
	//print problem 4
	cout << "Shortest path (v7 ~ v3)\n";
	path(7, 3);
	cout << "v7 ";
	for (auto i : v) {
		cout << "v" << i << " ";
	}
	cout << "v3";
	cout << endl;

	cout << "\nProblem 5,6\n";
	//print problem 5
	cout << "Matrix D\n";
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			if (D2[i][j] != MAX) {
				cout << D2[i][j] << " ";
			}
			else {
				cout << 0 << " ";
			}
		}
		cout << "\n";
	}
	cout << "Matrix P\n";
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			cout << P2[i][j] << " ";
		}
		cout << "\n";
	}

	//print problem 6
	cout << "Shortest Path (a1~ a5)\n";
	path2(1, 5);
	cout << "a1 ";
	for (auto i : v2) {
		cout << "a" << i << " ";
	}
	cout << "a5";
	cout << endl;


	return 0;
}