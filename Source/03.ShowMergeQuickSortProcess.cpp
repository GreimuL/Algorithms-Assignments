/*
Greimul
Show Merge Sort and Quick Sort Process
*/

#include<iostream>
#include<algorithm>
using namespace std;

//array initial setting
int arr1[8] = { 123,34,189,56,150,12,9,240 };
int arr2[8] = { 123,34,189,56,150,12,9,240 };

//print current array
void printcurrentarr(int* arr) {
	for (int i = 0; i < 8; i++) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}

//copy b to a
void copyarr(int st, int fi, int* a, int* b) {
	for (int i = st; i <= fi; i++) {
		a[i] = b[i];
	}
}

//MergeSort merge function
void merge(int st, int mid, int fi, int* arr) {

	
	int i = st;
	int j = mid + 1;
	int k = st;
	//temp array
	int temparr[8];
	//compare size and save to temp array
	while (i <= mid && j <= fi) {
		if (arr[i] < arr[j]) {
			temparr[k] = arr[i];
			i++;
		}
		else {
			temparr[k] = arr[j];
			j++;
		}
		k++;
	}
	//remain elements
	if (i > mid) {
		for (int L = j; L <= fi; L++) {
			temparr[k] = arr[L];
			k++;
		}
	}
	else {
		for (int L = i; L <= mid; L++) {
			temparr[k] = arr[L];
			k++;
		}
	}
	//copy temp array to origin array
	copyarr(st, fi, arr, temparr);

	//print current array
	printcurrentarr(arr1);

}
//MergeSort
void mergesort(int st, int fi, int* arr) {

	if (st < fi) {
		int mid = (st + fi) / 2;
		//divide array
		mergesort(st, mid, arr);
		mergesort(mid + 1, fi, arr);
		//Merge
		merge(st, mid, fi, arr);
	}
}

//QuickSort
void quicksort(int st, int fi, int* arr) {

	//function exit if final index is larger than start index
	if (fi <= st) {
		return;
	}
	
	int i = st;
	int j = fi;
	int pivot = st; //make pivot by start index

	while (i < j) {
		//search number that is smaller than pivot
		while (arr[j] > arr[pivot]) {
			j--;
		}
		//search number that is larger than pivot
		while (arr[i] <= arr[pivot]) {
			if (i >= j) {
				break;
			}
			i++;
		}
		//swap
		swap(arr[i], arr[j]);
	}
	//swap
	swap(arr[i], arr[pivot]);

	//print current array
	printcurrentarr(arr2);

	quicksort(st, i - 1, arr); //피벗을 기준으로 왼쪽
	quicksort(i + 1, fi, arr); //피벗을 기준으로 오른쪽

}

int main() {
	cout << "MergeSort\n";
	printcurrentarr(arr1);
	cout << "\n";
	mergesort(0, 7, arr1); //MergeSort start

	cout << "\nQuickSort\n";
	printcurrentarr(arr2);
	cout << "\n";
	quicksort(0, 7, arr2); //QuickSort start
	return 0;
}