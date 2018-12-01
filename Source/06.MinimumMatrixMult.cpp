/*
Greimul

Minimum Matrix Multiplication
*/

#include<iostream>
#include<algorithm>
#include<Windows.h>
#define MAX 0x7fffffff

LARGE_INTEGER Frequency;
LARGE_INTEGER Begintime;
LARGE_INTEGER Endtime;

using namespace std;

int di[6];
int P[5][5];
int M[5][5];

//Minimum Matrix Multiplication
int minmult(int n) {
	//array initial setting
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M[j][j] = 0;
			P[j][j] = 0;
		}
	}
	for (int dia = 1; dia <= n - 1; dia++) {
		for (int i = 1; i <= n - dia; i++) {
			int j = i + dia;
			M[i][j] = MAX;
			for (int k = i; k <= j - 1; k++) {
				if (M[i][j] > M[i][k] + M[k + 1][j] + di[i - 1] * di[k] * di[j]) {
					M[i][j] = M[i][k] + M[k + 1][j] + di[i - 1] * di[k] * di[j];
					P[i][j] = k;
				}
			}
		}
	}
	return M[1][n];
}
//print order
void order(int i, int j) {
	if (i == j) {
		cout << "A" << i;
	}
	else {
		int k = P[i][j];
		cout << "(";
		order(i, k);
		order(k + 1, j);
		cout << ")";
	}
}
int main() {
	QueryPerformanceFrequency(&Frequency);

	di[0] = 10;
	di[1] = 4;
	di[2] = 5;
	di[3] = 20;
	di[4] = 2;
	di[5] = 50;
	QueryPerformanceCounter(&Begintime);

	cout << minmult(5) << endl << endl;

	QueryPerformanceCounter(&Endtime); 
	long long elapsed = Endtime.QuadPart - Begintime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "Time: " << duringtime << "(s)" << endl << endl;

	cout << "Matrix M" << endl;
	//print Matrix M
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matrix P" << endl;
	//print Matrix P
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= 5; j++) {
			cout << P[i][j] << " ";
		}
		cout << endl;
	}
	//print order
	order(1, 5);
	return 0;
}
