/*
Greimul
Optimal Binary Search Tree
*/

#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<Windows.h>
#define MAX 0x7fffffff

LARGE_INTEGER Frequency;
LARGE_INTEGER Begintime;
LARGE_INTEGER Endtime;

using namespace std;

float p[7];
int R[10][10];
float A[8][7];
string key[7] = { "", "CASE","ELSE","END","IF","OF","THEN" };

//node struct
struct nodetype {
	string key;
	nodetype* left = NULL;
	nodetype* right = NULL;
};
typedef nodetype* node_pointer;

/*Optimal Binary Search Tree*/
void optsearchtree(int n, float& minavg) {
	int j;
	//array initial setting
	for (int i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}
	A[n + 1][n] = 0;
	R[n + 1][n] = 0;
	for (int diagonal = 1; diagonal <= n - 1; diagonal++)
		for (int i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			float sump = 0;
			//sum of p[i]~p[j]
			for (int tmp = i; tmp <= j; tmp++) {
				sump += p[tmp];
			}
			A[i][j] = MAX;
			for (int k = i; k <= j; k++) {
				if (A[i][j] >= A[i][k - 1] + A[k + 1][j]) {
					A[i][j] = A[i][k - 1] + A[k + 1][j];
					R[i][j] = k;
				}
			}
			A[i][j] += sump;
		}
	minavg = A[1][n];
}
//Optimal Binary Search Tree Build
node_pointer tree(int i, int j) {
	int k;
	node_pointer p;
	k = R[i][j];
	if (k == 0) {
		return NULL;
	}
	else {
		p = new nodetype;
		p->key = key[k];
		p->left = tree(i, k - 1);
		p->right = tree(k + 1, j);
		return p;
	}
}
//print Optimal Binary Search Tree (by bfs)
void bfsprint(node_pointer start) {
	queue<node_pointer> q;
	q.push(start);
	while (!q.empty()) {
		node_pointer now = q.front();
		cout << now->key << endl;
		q.pop();
		if (now->left != NULL) {
			q.push(now->left);
		}
		if (now->right != NULL) {
			q.push(now->right);
		}
	}

}
int main() {

	QueryPerformanceFrequency(&Frequency);

	//testcase
	p[1] = 0.05;
	p[2] = 0.15;
	p[3] = 0.05;
	p[4] = 0.35;
	p[5] = 0.05;
	p[6] = 0.35;

	float minavg;

	QueryPerformanceCounter(&Begintime); 

	optsearchtree(6, minavg);

	QueryPerformanceCounter(&Endtime);
	long long elapsed = Endtime.QuadPart - Begintime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "Time: " << duringtime << "(s)" << endl << endl;

	cout << "Minavg: " << minavg << endl;
	cout << "Matrix R\n";
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			cout << R[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Matrix A\n";
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	node_pointer head;
	head = tree(1, 6);

	cout << "Optimal Binary Search Tree (bfs)\n";
	bfsprint(head);
	return 0;
}
