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
		cout << "Для начала работы создайте множество: create <set_name>" << endl;
		cout << " 1) Удалить множество: delete <set_name>" << endl;
		cout << " 2) Добавить элемент во множество: add <set_name> [element]" << endl;
		cout << " 3) Удаление элемента из множества: remove <set_name> [element]" << endl;
		cout << " 4) Проверка множества на пустоту: is_empty <set_name>" << endl;
		cout << " 5) Поиск элемента во множестве: find <set_name> [element]" << endl;
		cout << " 6) Разность множеств: difference <set_name_1> <set_name_2>" << endl;
		cout << " 7) Объединение множеств: combine <set_name_1> <set_name_2>" << endl;
		cout << " 8) Сравнить множества на равенство: are_equal <set_name_1> <set_name_2>" << endl;
		cout << " 9) Вывести данные множества: print <set_name>" << endl;
		cout << "10) Ввести данные в множество: enter <set_name>" << endl;
		cout << "11) Вывести имена созданных множеств: sets" << endl;
		cout << "12) Вывести меню команд: help" << endl;
		cout << "13) Отчистить окно консоли: clear" << endl;
		cout << "14) Выйти из приложения: exit" << endl;
	}

	void create_set(const string &set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it == sets.end()) {
			Set<string> set(set_name);
			count_of_sets++;
			sets.push_back(set);
			cout << "==>Множество " << set_name << " создано" << endl;
		}
		else {
			cout << "==>Множество с таким именем уже существует" << endl;
		}
	}

	void delete_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			cout << "==>Множество " << set_name << " удалено" << endl;
			sets.erase(it);
			count_of_sets--;
			
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void add_element(const string& set_name,const string& element) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			it->operator+=(element);
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void remove_element(const string& set_name,const string& element){
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			it->operator-=(element);
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void print_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });
		
		if (it != sets.end()) {
			cout << "==>" << set_name << ": " << *it << endl;
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void is_empty(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			bool f = it->is_empty();

			if (f) {
				cout << "==>Множество " << set_name << " пустое" << endl;
			}
			else {
				cout << "==>Множество " << set_name << " не пустое" << endl;
			}
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void find(const string& set_name, const string& element) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });

		if (it != sets.end()) {
			bool f = it->find_element(element);

			if (f) {
				cout << "==>Множество " << set_name << " содержит элемент " << element << endl;
			}
			else {
				cout << "==>Множество " << set_name << " не содержит элемент " << element << endl;
			}
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}
	
	void difference(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			*it1 = it1->operator/(*it2);
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>Множество " << set_name_1 << " не существует" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>Множество " << set_name_2 << " не существует" << endl;
		}
		else {
			cout << "==>Множества с таким именем не существуют" << endl;
		}

	}

	void combine(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			*it1 = it1->operator||(*it2);
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>Множество " << set_name_1 << " не существует" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>Множество " << set_name_2 << " не существует" << endl;
		}
		else {
			cout << "==>Множества с таким именем не существуют" << endl;
		}
	}

	void enter_set(const string& set_name) {
		auto it = find_if(sets.begin(), sets.end(), [&set_name](const Set<string>& set) {return (set.get_name() == set_name); });


		if (it != sets.end()) {
			cin >> *it;
		}
		else {
			cout << "==>Множество с таким именем не существует" << endl;
		}
	}

	void are_equal(const string& set_name_1, const string& set_name_2) {
		auto it1 = find_if(sets.begin(), sets.end(), [&set_name_1](const Set<string>& set) {return (set.get_name() == set_name_1); });
		auto it2 = find_if(sets.begin(), sets.end(), [&set_name_2](const Set<string>& set) {return (set.get_name() == set_name_2); });

		if (it1 != sets.end() && it2 != sets.end()) {
			bool f = it1->operator==(*it2);

			if (f) {
				cout << "==>Множество " << set_name_1 << " равно множеству " << set_name_2 << endl;
			}
			else {
				cout << "==>Множество " << set_name_1 << " не равно множеству " << set_name_2 << endl;
			}
		}
		else if (it1 == sets.end() && it2 != sets.end()) {
			cout << "==>Множество " << set_name_1 << " не существует" << endl;
		}
		else if (it1 != sets.end() && it2 == sets.end()) {
			cout << "==>Множество " << set_name_2 << " не существует" << endl;
		}
		else {
			cout << "==>Множества с таким именем не существуют" << endl;
		}
	}

	void get_sets() {
		if (count_of_sets != 0) {
			for_each(sets.begin(), sets.end(), [](const Set<string>& set) {cout << set.get_name() << endl; });
		}
		else {
			cout << "Вы не создали множества. Используйте create <set_name>, чтобы создать множество" << endl;
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
		cout << "Введите команду: ";
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
				cout << "	Количество созданных множеств: " << count_of_sets << endl;
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
			else if (*it == "enter" && command_data.size() == 2) { //АНОМАЛИЯ
				string name;
				it++; name = *it;
				enter_set(name);
				getline(cin, command); //тут словно отрабатывает continue
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
				cout << "==>Неизвестная команда" << endl;
			}
			
			

			command_data.clear();
			cout << "Введите команду: ";
			getline(cin, command);
		}
	}

};

ConsoleApp* ConsoleApp::instance = nullptr;

