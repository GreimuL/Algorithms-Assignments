/*
Greimul
Stack Calculator
*/

#include<string>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
using namespace std;

//make number by each degits which are in vector
int makenumber(vector<int> &num, bool isMinus) {
	int number = 0;
	int cnt = 1; //cipher
	while (!num.empty()) {
		number += cnt * num.back();
		cnt *= 10;
		num.pop_back();
	}
	if (isMinus) {
		return -number; //if negative number
	}
	else {
		return number;  //if positive number
	}

}

int main() {

	vector<char> stack; //temp stack
	vector<double> answer; //calculate stack
	vector<string> postfix; //save postfix
	string input;  //input string

	while (1) {
		bool error = 0; //check error
		stack.clear();
		answer.clear();
		postfix.clear();
		getline(cin, input);	//input string

		if (input == "q") { //exit if input is 'q'
			break;
		}

		input.erase(remove(input.begin(), input.end(), ' '), input.end()); //erase blanks
		input.erase(remove(input.begin(), input.end(), '\t'), input.end()); //erase tabs

		int length = input.length();  //length of string that erase blanks and tabs

		char pip;
		for (int i = 0; i < length; i++) {
			if (i == 0) {  //error if first character is operations except '-' and '('
				if ((input[i] == '^' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '+')) {
					error = 1;
					cout << "ERROR" << endl;
					break;
				}
				pip = input[i];
			}
			else if(i==1||i==2) {  //error if operations entered in front of operations
				if ((input[i] == '^' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '+')) {
					if ((pip == '^' || pip == '*' || pip == '/' || pip == '%' || pip == '+'||pip=='-')) {
						error = 1;
						cout << "ERROR"<<endl;
						break;
					}
				}
				//error if operations entered behind the brackets
				if ((input[i] == '^' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '+')) {
					if (pip == '(') {
						error = 1;
						cout << "ERROR" << endl;
						break;
					}
				}
				pip = input[i];
			}
			else { //error if operations entered in front of operations
				if ((input[i] == '^' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '+')) {
					if ((pip == '^' || pip == '*' || pip == '/' || pip == '%' || pip == '+' || pip == '-')) {
						error = 1;
						cout << "ERROR" << endl;
						break;
					}
				}
				//error if operations entered behind the brackets
				if ((input[i] == '^' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '+')) {
					if (pip == '(') {
						error = 1;
						cout << "ERROR" << endl;
						break;
					}
				}//---, --),--( error
				if (input[i] == '-') {
					if (input[i - 1] == '-') {
						if (input[i - 2] == '-') {
							error = 1;
							cout << "ERROR" << endl;
							break;
						}
						if (input[i - 2] == '(') {
							error = 1;
							cout << "ERROR" << endl;
							break;
						}
						if (input[i - 2] == ')') {
							error = 1;
							cout << "ERROR" << endl;
							break;
						}
					}
				}//(-- ,)-- error
				if (input[i] == '(') {
					if (input[i - 1] == '-') {
						if (input[i - 2] == '-') {
							error = 1;
							cout << "ERROR" << endl;
							break;
						}
					}
				}
				if (input[i] == ')') {
					if (input[i - 1] == '-') {
						if (input[i - 2] == '-') {
							error = 1;
							cout << "ERROR" << endl;
							break;
						}
					}
				}
				pip = input[i];
			}
		}


		char postchar = '$'; //previous character
		vector<int> numnow; // current reading number
		bool isMinus = 0;

		for (int i = 0; i < length; i++) {
			if (error == 1) {
				break;
			}
			if (isdigit(input[i])) { //read digits
				postchar = input[i];
				numnow.push_back(input[i] - '0');
			}
			else {
				if (!numnow.empty()) {   //transform to number and save postfix when finish reading digits
					string integer = to_string(makenumber(numnow, isMinus));
					postfix.push_back(integer);
					isMinus = 0;
				}
				if (input[i] == '(') {
					stack.push_back(input[i]);
					postchar = input[i];
				}
				else if (input[i] == ')') {//')' 
					if (!stack.empty()) {
						string pointer(1, stack.back());
						while (pointer != "(") {
							postfix.push_back(pointer);
							stack.pop_back();
							if (stack.empty()) {  // error if there is no '('
								cout << "ERROR"<<endl;
								error = 1;
								break;
							}
							pointer = stack.back();
						}
						if (pointer == "(") { //'(' 
							stack.pop_back();
						}
					}
					else { //error if there is no '(' when read ')'
						cout << "ERROR" << endl;
						error = 1;
						break;
					}
					postchar = input[i];
				}
				else if (input[i] == '^') { //'^'
					stack.push_back(input[i]);
					postchar = input[i];
				}//unary
				else if (input[i] == '-' && (postchar == '$' || postchar == '+' || postchar == '-' || postchar == '*' || postchar == '/' || postchar == '%' || postchar == '(' || postchar == '^')) {
					isMinus = 1;
					postchar = input[i];
				}
				else if (input[i] == '*' || input[i] == '/' || input[i] == '%') {   //'*','/','%' decide push or pop at stack by order of priority
					if (!stack.empty()) {
						if (stack.back() == '^' || stack.back() == '*' || stack.back() == '/' || stack.back() == '%') { 
							while (!stack.empty()) {
								string move(1, stack.back());
								if (move == "+" || move == "-") {
									stack.push_back(input[i]);
									break;
								}
								if (move == "(") {
									break;
								}
								postfix.push_back(move);
								stack.pop_back();
							}
							stack.push_back(input[i]);
							postchar = input[i];
						}
						else {
							stack.push_back(input[i]);
							postchar = input[i];
						}
					}
					else {
						stack.push_back(input[i]);
						postchar = input[i];
					}
				}
				else if (input[i] == '+' || input[i] == '-') {   //'+','-' decide push or pop at stack by order of priority
					if (!stack.empty()) {
						while (!stack.empty()) {
							string move(1, stack.back());
							if (move == "(") {
								break;
							}
							postfix.push_back(move);
							stack.pop_back();
						}
						stack.push_back(input[i]);
						postchar = input[i];
					}
					else {
						stack.push_back(input[i]);
						postchar = input[i];
					}
				}
				else {  //error if unsupported symbol entered
					error = 1;
					cout << "ERROR" << endl;
					break;
				}
			}
		}
		if (error == 0) { //there is no error
			if (!numnow.empty()) {
				string integer = to_string(makenumber(numnow, isMinus));
				postfix.push_back(integer);
				isMinus = 0;
			}
			while (!stack.empty()) {
				string move(1, stack.back());
				if (move == "(") { //error if brackets remain in the stack
					cout << "ERROR" << endl;
					error = 1;
					break;
				}
				postfix.push_back(move);
				stack.pop_back();
			}
			if (error == 0) {
				for (auto iter : postfix) {
					cout << iter << " ";	//print postfix
					int tplen = iter.length();
					if (isdigit(iter[tplen-1])) {//is it number? check
						if (iter[0] == '-') {//if negative number
							vector<int> tpvector;
							for (int i = 1; i < tplen; i++) {
								tpvector.push_back(iter[i]-'0');
							}
							answer.push_back(makenumber(tpvector, 1));
						}
						else {//if positive number
							vector<int> tpvector;
							for (int i = 0; i < tplen; i++) {
								tpvector.push_back(iter[i] - '0');
							}
							answer.push_back(makenumber(tpvector, 0));
						}
					}
					else {//if operation
						if (iter[0] == '+') { //plus operation
							double aa = answer.back();
							answer.pop_back();
							double bb = answer.back();
							answer.pop_back();
							double tpres = bb + aa;
							answer.push_back(tpres);
						}
						else if (iter[0] == '-') {  //minus operation
							double aa = answer.back();
							answer.pop_back();
							double bb = answer.back();
							answer.pop_back();
							double tpres = bb - aa;
							answer.push_back(tpres);
						}
						else if (iter[0] == '*') { //multiply operation
							double aa = answer.back();
							answer.pop_back();
							double bb = answer.back();
							answer.pop_back();
							double tpres = bb * aa;
							answer.push_back(tpres);
						}
						else if (iter[0] == '/') {  //divide operation
							double aa = answer.back();
							answer.pop_back();
							double bb = answer.back();
							answer.pop_back();
							double tpres = bb / aa;
							answer.push_back(tpres);
						}
						else if (iter[0] == '^') {//power operation
							double aa = answer.back();
							answer.pop_back();
							double bb = answer.back();
							answer.pop_back();
							double tpres = pow(bb,aa);
							answer.push_back(tpres);
						}
						else if (iter[0] == '%') {//mod operation
							int aa = answer.back();
							answer.pop_back();
							int bb = answer.back();
							answer.pop_back();
							int tpres = bb % aa;
							answer.push_back(tpres);
						}
					}
				}
				
				cout << endl;
				cout << answer.front()<<endl; //print answer
			}
		}
	}

	cout << "program exit";
	return 0;
}