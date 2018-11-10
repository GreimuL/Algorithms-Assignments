/*
Greimul
Quick Sort, Merge Sort and ExchangeSort using Doubly Linked List

input form
Positive Integer n
n numbers
ex)
5
5 4 3 2 1
*/
#include<iostream>
#include<Windows.h>
using namespace std;
LARGE_INTEGER Frequency;
LARGE_INTEGER BeginTime;
LARGE_INTEGER Endtime;

//node
typedef struct d_node {
	//previous node, next node, data
	d_node* prev = NULL;
	d_node* next = NULL;
	int data = NULL;
}d_node;

//Doubly Linked List management
typedef struct d_list {

	//number of node
	int cnt = 0;
	//head and tail
	d_node* head = new d_node();
	d_node* tail = new d_node();


	//list initial setting
	void init_list() {
		cnt = 0;
		head->next = tail;
		head->prev = head;
		tail->next = tail;
		tail->prev = head;
	}
	//return number of node
	int list_cnt() {
		return cnt;
	}
	//insert node in head
	void list_insert_head(int input) {
		cnt++;
		//create new node
		d_node* newnode = new d_node();
		newnode->data = input;
		//insert node
		newnode->next = head->next;
		newnode->prev = head;
		head->next->prev = newnode;
		head->next = newnode;
	}
	//insert node in tail
	void list_insert_tail(int input) {
		cnt++;
		//create new node
		d_node* newnode = new d_node();
		newnode->data = input;
		//insert node
		newnode->next = tail;
		newnode->prev = tail->prev;
		tail->prev->next = newnode;
		tail->prev = newnode;
	}
	//insert node by index
	void list_insert_index(int ind, int input) {
		//exception when index that exceed list range entered
		if (ind > cnt) {
			cout << "insert failed.\n";
		}
		else {
			cnt++;
			//create new node
			d_node* newnode = new d_node();
			newnode->data = input;

			//insert node
			d_node* tmp = head;
			for (int i = 0; i < ind; i++) {
				tmp = tmp->next;
			}
			newnode->prev = tmp;
			newnode->next = tmp->next;
			tmp->next->prev = newnode;
			tmp->next = newnode;
		}

	}
	//list head node
	void list_delete_head() {
		//exception when number of node is zero
		if (cnt == 0) {
			cout << "delete failed.\n";
		}
		else {
			cnt--;
			//delete node
			d_node* tmp = head->next;
			head->next = tmp->next;
			tmp->next->prev = head;
			delete tmp;
		}
	}
	//delete tail node
	void list_delete_tail() {
		//exception when number of node is zero
		if (cnt == 0) {
			cout << "delete failed.\n";
		}
		else {
			cnt--;
			//delete node
			d_node* tmp = tail->prev;
			tail->prev = tmp->prev;
			tmp->prev->next = tail;
			delete tmp;
		}
	}
	//delete node by data
	void list_delete_data(int target) {
		//search list
		d_node* tmp = head->next;
		while (tmp != tail) {
			if (tmp->data == target) {
				//delete node
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
				cnt--;
			}
			tmp = tmp->next;
		}

	}
	//delete node by index
	void list_delete_index(int ind) {
		//exception when index that exceed list range entered
		if (ind > cnt) {
			cout << "delete failed.\n";
		}
		else {
			//search list
			d_node* tmp = head->next;
			for (int i = 0; i < ind; i++) {
				tmp = tmp->next;
			}
			//delete node
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			cnt--;
		}
	}
	//Search node by index (return node)
	d_node* list_search_index(int ind) {
		//exception when index that exceed list range entered
		if (ind >= cnt) {
			cout << "search failed\n";
			return NULL;
		}
		else {
			//search list
			d_node* tmp = head->next;
			for (int i = 0; i < ind; i++) {
				tmp = tmp->next;
			}
			return tmp;
		}
	}
	//Search node by data (return index)
	int list_search_data(int target) {
		d_node* tmp = head->next;
		int tpindex = 0;
		//search list
		while (tmp != tail) {
			if (tmp->data == target) {
				return  tpindex;
			}
			tpindex++;
			tmp = tmp->next;
		}
		return -1;
	}
	//list all clear
	void list_clear() {
		//delete all node
		d_node* tmp = head->next;
		while (tmp != tail) {
			tmp = tmp->next;
			delete tmp->prev;
		}
		//list init setting
		init_list();
	}
	//list copy
	void list_copy(d_list* nlist) {
		//list init setting
		nlist->init_list();
		nlist->cnt = list_cnt();
		//copy existing list to new list
		d_node* tmpiter = head->next; //existing list pointer
		d_node* tmppoint = nlist->head; //new list pointer
		//copy and paste
		while (tmpiter != tail) {
			d_node* tmpnode = new d_node();
			tmpnode->data = tmpiter->data;
			tmpnode->prev = tmppoint;
			tmpnode->next = tmppoint->next;
			tmppoint->next->prev = tmpnode;
			tmppoint->next = tmpnode;
			tmpiter = tmpiter->next;
			tmppoint = tmpnode;
		}
	}
}d_list;

//Swap node(not swap just data, swap node itself)
void swap(d_node* first, d_node* second) {

	if (first->next == second) {	//case 1
		first->next = second->next;
		second->prev = first->prev;
		first->prev = second;
		second->next = first;
		first->next->prev = first;
		second->prev->next = second;
	}
	else if (second->next == first) {	//case 2
		second->next = first->next;
		first->prev = second->prev;
		second->prev = first;
		first->next = second;
		second->next->prev = second;
		first->prev->next = first;
	}
	else {	//case 3
		d_node* tmp = first->prev;
		d_node* tmp2 = first->next;

		d_node* tmp3 = second->prev;
		d_node* tmp4 = second->next;

		tmp->next = second;
		tmp2->prev = second;
		second->next = tmp2;
		second->prev = tmp;

		tmp3->next = first;
		tmp4->prev = first;
		first->next = tmp4;
		first->prev = tmp3;
	}

}
//ExchangeSort
void ExchangeSort(d_list* nlist) {
	for (d_node* i = nlist->head->next; i != nlist->tail; i=i->next) {
		for (d_node* j = i->next; j != nlist->tail; j = j->next) {		
			if (i->data > j->data) {
				swap(i, j);
				d_node* ttt = i;
				i = j;
				j = ttt;
			}
		}
	}
}
//MergeSort
d_list* Merge(d_list* leftlist, d_list* rightlist) {

	d_list* ret = new d_list();
	ret->init_list();

	while (leftlist->list_cnt() != 0 && rightlist->list_cnt() != 0) {
		if (leftlist->head->next->data <= rightlist->head->next->data) {
			ret->list_insert_tail(leftlist->head->next->data);
			leftlist->list_delete_head();
		}
		else {
			ret->list_insert_tail(rightlist->head->next->data);
			rightlist->list_delete_head();
		}
	}

	while (leftlist->list_cnt() != 0) {
		ret->list_insert_tail(leftlist->head->next->data);
		leftlist->list_delete_head();
	}
	while (rightlist->list_cnt() != 0) {
		ret->list_insert_tail(rightlist->head->next->data);
		rightlist->list_delete_head();
	}

	return ret;

}
d_list* MergeSort(d_list* nlist) {
	if (nlist->list_cnt() <= 1) {
		return nlist;
	}

	d_list* leftlist = new d_list();
	d_list* rightlist = new d_list();

	leftlist->init_list();
	rightlist->init_list();
	
	int listlen = nlist->list_cnt();
	d_node* listpt = nlist->head;
	for (int i = 0; i < listlen; i++) {
		listpt = listpt->next;
		if (listlen / 2 > i) {
			leftlist->list_insert_tail(listpt->data);
		}
		else {
			rightlist->list_insert_tail(listpt->data);
		}
	}

	leftlist = MergeSort(leftlist);
	rightlist = MergeSort(rightlist);

	return Merge(leftlist, rightlist);
}
void MergeSortStart(d_list* nlist) {
	d_list* newlist;
	newlist = MergeSort(nlist);
	nlist->list_clear();
	newlist->list_copy(nlist);
}

//Quick Sort
void QuickSort(d_list* nlist, d_node* left, d_node* right, int leftind, int rightind) {
	d_node* i = left;
	d_node* j = right;
	int iind = leftind;
	int jind = rightind;
	int pivot = left->data;
	do {
		while (i->data < pivot) {
			i = i->next;
			iind++;
		}
		while (j->data > pivot) {
			j = j->prev;
			jind--;
		}

		if (iind <= jind) {
			if (iind != jind) {
				swap(i, j);

				if (left == i) {
					left = j;
				}
				if (right == j) {
					right = i;
				}
				d_node* tmp = i;
				i = j;
				j = tmp;

			}
			iind++;
			jind--;
			i = i->next;
			j = j->prev;
		}
	} while (iind <= jind);

	if (leftind < jind) {
		QuickSort(nlist, left, j, leftind, jind);
	}
	if (rightind > iind) {
		QuickSort(nlist, i, right, iind, rightind);
	}
}
//Sort Validity check
bool SortingCheck(d_list* nlist) {
	int cnt = nlist->list_cnt();
	d_node* node = nlist->head->next;
	int preval = node->data;
	for (int i = 1; i < cnt; i++) {
		int curval = node->data;
		if (curval<preval) {
			return false;
		}
		preval = curval;
		node = node->next;
	}
	return  true;
}

int main() {
	QueryPerformanceFrequency(&Frequency);

	d_list linked;
	d_list linked2;
	d_list linked3;
	linked.init_list();
	linked2.init_list();
	linked3.init_list();
	int input;
	cin >> input;
	for (int i = 0; i < input; i++) {
		int nu;
		cin >> nu;
		linked.list_insert_tail(nu);
		linked2.list_insert_tail(nu);
		linked3.list_insert_tail(nu);
	}
	cout << "Exchange Sort Start" << endl;
	QueryPerformanceCounter(&BeginTime);

	ExchangeSort(&linked);

	QueryPerformanceCounter(&Endtime);
	long long elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout <<"Exchange Sort time : "<< duringtime<<endl;
	cout << "Sort validity check..." << endl;
	if (SortingCheck(&linked) == true) {
		cout << "Sort Success!" << endl;;
	}
	else {
		cout << "Sort Failed!"<<endl;
	}

	cout << "Merge Sort Start" << endl;
	QueryPerformanceCounter(&BeginTime);

	MergeSortStart(&linked2);

	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "Merge Sort time : " << duringtime << endl;
	cout << "Sort validity check..." << endl;
	if (SortingCheck(&linked2) == true) {
		cout << "Sort Success!" << endl;;
	}
	else {
		cout << "Sort Failed!" << endl;
	}

	cout << "Quick Sort Start" << endl;
	QueryPerformanceCounter(&BeginTime);

	QuickSort(&linked3, linked3.list_search_index(0), linked3.list_search_index(linked3.list_cnt() - 1), 0, linked3.list_cnt() - 1);

	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	cout << "Quick Sort time : " << duringtime << endl;
	cout << "Sort validity check..." << endl;
	if (SortingCheck(&linked3) == true) {
		cout << "Sort Success!" << endl;;
	}
	else {
		cout << "Sort Failed!" << endl;
	}
	return 0;
}