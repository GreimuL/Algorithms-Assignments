/*
Greimul

Binomial Coefficient
by recursion, two dimensions DP, one dimension DP
*/
#include<iostream>
#include<algorithm>
#include<Windows.h>
using namespace std;

LARGE_INTEGER Frequency;
LARGE_INTEGER Begintime;
LARGE_INTEGER Endtime;

//Binomial Coefficient by recursion
int bin(int n, int k) {
	if (k == 0 || n == k) {
		return 1;
	}
	else {
		return bin(n - 1, k - 1) + bin(n - 1, k);
	}
}

//Binomial Coefficient by two dimension DP
int bin2(int n, int k) {
	int **B = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		B[i] = new int[k + 1];
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= min(i, k); j++) {
			if (j == 0 || j == i) {
				B[i][j] = 1;
			}
			else {
				B[i][j] = B[i - 1][j - 1] + B[i - 1][j];
			}
		}
	}
	return B[n][k];
}

//Binomial Coefficient by one dimension DP
int bin3(int n, int k) {
	int *B2 = new int[k + 1];
	for (int i = 0; i < k + 1; i++) {
		B2[i] = 0;
	}
	B2[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = min(i, k); j >= 1; j--) {
			B2[j] += B2[j - 1];
		}
	}
	return B2[k];
}

int main() {

	//testcase
	int n, k;
	int nlist[5] = { 10, 50,100,30,30 };
	int klist[5] = { 2, 5,5,10,12 };

	QueryPerformanceFrequency(&Frequency);

	for (int i = 0; i < 5; i++) {
		n = nlist[i];
		k = klist[i];
		cout << "Case " << n << "C" << k << " \n";
		QueryPerformanceCounter(&Begintime); 

		//Binomial Coefficient by recursion
		cout << bin(n, k) << endl;

		QueryPerformanceCounter(&Endtime); 

		long long elapsed = Endtime.QuadPart - Begintime.QuadPart;
		double duringtime = (double)elapsed / (double)Frequency.QuadPart;
		cout << "Binomial Coefficient by recursion time: " << duringtime << "(s)" << endl;

		QueryPerformanceCounter(&Begintime); 

		//Binomial Coefficient by two dimension DP
		cout << bin2(n, k) << endl;

		QueryPerformanceCounter(&Endtime); 

		elapsed = Endtime.QuadPart - Begintime.QuadPart;
		duringtime = (double)elapsed / (double)Frequency.QuadPart;
		cout << "Binomial Coefficient by two dimensions DP time: " << duringtime << "(s)" << endl << endl;
	}

	cout << "Binomial Coefficient by one dimension DP\nCase 30 C 12\n";
	//Binomial Coefficient by one dimension DP (30C12)
	cout << bin3(n, k) << endl;

	return 0;
}