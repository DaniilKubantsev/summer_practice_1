#pragma once

#include "Set.h"
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <algorithm>



class ConsoleApp {
private:
	vector<Set<string>> sets;
	int count_of_sets = 0;

	static ConsoleApp* instance;

	ConsoleApp() {};
	ConsoleApp(const ConsoleApp& other) = delete;
	ConsoleApp& operator = (const ConsoleApp&) = delete;


	void help() {
		cout << "��� ������ ������ �������� ���������: create <set_name>" << endl;
		cout << " 1) ������� ���������: delete <set_name>" << endl;
		cout << " 2) �������� ������� �� ���������: add <set_name> [element]" << endl;
		cout << " 3) �������� �������� �� ���������: remove <set_name> [element]" << endl;
		cout << " 4) �������� ��������� �� �������: is_empty <set_name>" << endl;
		cout << " 5) ����� �������� �� ���������: find <set_name> [element]" << endl;
		cout << " 6) �������� ��������: difference <set_name_1> <set_name_2>" << endl;
		cout << " 7) ����������� ��������: combine <set_name_1> <set_name_2>" << endl;
		cout << " 8) �������� ��������� �� ���������: are_equal <set_name_1> <set_name_2>" << endl;
		cout << " 9) ������� ������ ���������: print <set_name>" << endl;
		cout << "10) ������ ������ � ���������: enter <set_name>" << endl;
		cout << "11) ������� ����� ��������� ��������: sets" << endl;
		cout << "12) ������� ���� ������: help" << endl;
		cout << "13) ��������� ���� �������: clear" << endl;
		cout << "14) ����� �� ����������: exit" << endl;
	}

	void create_set(const string &set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it == sets.end()) {
			Set<string> set(set_name);
			count_of_sets++;
			sets.push_back(set);
			cout << "==>��������� " << set_name << " �������" << endl;
		}
		else {
			cout << "==>��������� � ����� ������ ��� ����������" << endl;
		}
	}

	void delete_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			cout << "==>��������� " << set_name << " �������" << endl;
			sets.erase(it);
			count_of_sets--;
			
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void add_element(const string& set_name,const string& element) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			it->operator+=(element);
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void remove_element(const string& set_name,const string& element){
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			it->operator-=(element);
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void print_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });
		
		if (it != sets.end()) {
			cout << "==>" << set_name << ": " << *it << endl;
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void is_empty(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			bool f = it->is_empty();

			if (f) {
				cout << "==>��������� " << set_name << " ������" << endl;
			}
			else {
				cout << "==>��������� " << set_name << " �� ������" << endl;
			}
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void find(const string& set_name, const string& element) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			bool f = it->find_element(element);

			if (f) {
				cout << "==>��������� " << set_name << " �������� ������� " << element << endl;
			}
			else {
				cout << "==>��������� " << set_name << " �� �������� ������� " << element << endl;
			}
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}
	
	void difference(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			*it1 = it1->operator/(*it2);
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>��������� " << set_name_1 << " �� ����������" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>��������� " << set_name_2 << " �� ����������" << endl;
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}

	}

	void combine(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			*it1 = it1->operator||(*it2);
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>��������� " << set_name_1 << " �� ����������" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>��������� " << set_name_2 << " �� ����������" << endl;
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void enter_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });


		if (it != sets.end()) {
			cin >> *it;
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void are_equal(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			bool f = it1->operator==(*it2);

			if (f) {
				cout << "==>��������� " << set_name_1 << " ����� ��������� " << set_name_2 << endl;
			}
			else {
				cout << "==>��������� " << set_name_1 << " �� ����� ��������� " << set_name_2 << endl;
			}
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>��������� " << set_name_1 << " �� ����������" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>��������� " << set_name_2 << " �� ����������" << endl;
		}
		else {
			cout << "==>��������� � ����� ������ �� ����������" << endl;
		}
	}

	void get_sets() {
		if (count_of_sets != 0) {
			for_each(sets.begin(), sets.end(), [](const Set<string>& set) {cout << set.get_name() << endl; });
		}
		else {
			cout << "�� �� ������� ���������. ����������� create <set_name>, ����� ������� ���������" << endl;
		}
		
	}

public:
	~ConsoleApp() {
		delete instance;
	}

	static ConsoleApp* Instance() {

		if (instance == nullptr) {
			instance = new ConsoleApp();
			return instance;
		}
		else {
			return nullptr;
		}
	}

	void run() {
		help();

		list<string> command_data;
		string command;
		cout << "������� �������: ";
		getline(cin, command);

		while (command != "exit") {

			if (command.empty()) command = "nothing";
			stringstream ss(command);
			copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(command_data));
			auto it = command_data.begin();

			if (*it == "create" && command_data.size() == 2) {
				it++;
				string name = *it;
				create_set(name);
			}
			else if (*it == "delete" && command_data.size() == 2) {
				it++;
				string name = *it;
				delete_set(name);
			}
			else if (*it == "count" && command_data.size() == 1) {
				cout << "	���������� ��������� ��������: " << count_of_sets << endl;
			}
			else if (*it == "add" && command_data.size() == 3) {
				string name, data;
				it++; name = *it;
				it++; data = *it;
				add_element(name, data);
			}
			else if (*it == "remove" && command_data.size() == 3) {
				string name, data;
				it++; name = *it;
				it++; data = *it;
				remove_element(name, data);
			}
			else if (*it == "print" && command_data.size() == 2) {
				it++;
				string name = *it;
				print_set(name);
			}
			else if (*it == "clear" && command_data.size() == 1) {
				system("cls");
			}
			else if (*it == "is_empty" && command_data.size() == 2) {
				string name;
				it++; name = *it;
				is_empty(name);
			}
			else if (*it == "find" && command_data.size() == 3) {
				string name, data;
				it++; name = *it;
				it++; data = *it;
				find(name, data);
			}
			else if (*it == "difference" && command_data.size() == 3) {
				string name1, name2;
				it++; name1 = *it;
				it++; name2 = *it;
				difference(name1, name2);
			}
			else if (*it == "enter" && command_data.size() == 2) { //��������
				string name;
				it++; name = *it;
				enter_set(name);
				getline(cin, command); //��� ������ ������������ continue
			}
			else if (*it == "combine" && command_data.size() == 3) {
				string name1, name2;
				it++; name1 = *it;
				it++; name2 = *it;
				combine(name1, name2);
			}
			else if (*it == "are_equal" && command_data.size() == 3) {
				string name1, name2;
				it++; name1 = *it;
				it++; name2 = *it;
				are_equal(name1, name2);
			}
			else if (*it == "sets" && command_data.size() == 1) {
				string name;
				name = *it;
				get_sets();
			}
			else {
				cout << "==>����������� �������" << endl;
			}
			
			

			command_data.clear();
			cout << "������� �������: ";
			getline(cin, command);
		}
	}

};

ConsoleApp* ConsoleApp::instance = nullptr;

