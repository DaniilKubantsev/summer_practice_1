#include <iostream>
#include "Set.h"
#include <fstream>
#include "ConsoleApplication.h"


using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");


	ConsoleApp* app = ConsoleApp::Instance();
	app->run();

	return 0;
}


//void test_run() {
//	Tree<int> t1, t2;
//
//	for (int i = 0; i < 10; ++i) {
//		t1.append(i);
//		t2.append(i);
//	}
//
//	for (int i = -10; i < 5; ++i) {
//		t1.append(i);
//		t2.append(i);
//	}
//
//	cout << (t1 == t2) << endl;
//	cout << (t1 != t2) << endl;
//
//}
//
//
//void problem_run() {
//
//	ifstream data1("data1.txt");
//	ifstream data2("data2.txt");
//
//	Set<string> set1, set2, set3;
//
//	while (!data1.eof()) {
//		string word;
//		data1 >> word;
//		set1 += word;
//	}
//
//	while (!data2.eof()) {
//		string word;
//		data2 >> word;
//		set2 += word;
//	}
//
//	cout << endl;
//	cout << "data1.txt: " << endl << set1;
//	cout << "data2.txt: " << endl << set2;
//
//	set3 = set1 / set2;
//
//	cout << set3 << endl;
//
//}