#pragma once

#include <iostream>
#include "Tree.h"

using namespace std;


template<class T>
class Set {
private:
	Tree<T> container;
	string name;

public:

	Set(string name = "noname") {
		this->name = name;
	}

	Set(const Set& other) {
		container = other.container;
		name = other.name;
	}

	string get_name() const {
		return this->name;
	}
	
	bool is_empty()
	{
		return container.is_empty();
	}

	int get_element(T& element) {
		try {
			T wanted = container.get_element(element);
			return wanted;
		}
		catch (MyException error) {
			cout << error.get_error_message() << endl;
		}
		
		
	}

	bool find_element(const T& element) {
		return container.find_element(element);
	}

	void erase(T& elem) {
		try {
			container.erase(elem);
		}
		catch (MyException error) {
			throw error;
		}
	}

	void add(const T& elem) { // добавление элемента во множество
		container.append(elem);
	}

	Set& operator+=(const T& elem)
	{
		if (!container.find_element(elem)) {
			container.append(elem);
		}
		
		return *this;
	}

	Set& operator-=(const T& elem)
	{
		try {
			container.erase(elem);
			
		}
		catch (MyException error) {
			cout << error.get_error_message() << endl;
		}
		return *this;
	}

	Set operator/(const Set& other){
		Set temp(*this);

		try {
			temp.container.difference(other.container);
		}
		catch (MyException error) {
			cout << error.get_error_message() << endl;
		}
		
		return temp;


	}

	Set operator || (const Set& other) {
		Set temp(*this);

		try {
			temp.container.set_union(other.container);
		}
		catch (MyException error) {
			cout << error.get_error_message() << endl;
		}
		
		return temp;
	}

	bool operator == (const Set<T>& other) {
		return container == other.container;
	}

	bool operator != (const Set<T>& other) {
		return container != other.container;
	}

	friend ostream& operator << (ostream& os, const Set& set) {
		cout << set.container;
		return os;
	}

	friend istream& operator >> (istream& in, Set& set) {
		int count = 0;
		cout << "Введите кол-во элементов: ";
		cin >> count;

		for (int i = 0; i < count; i++) {
			T elem = T();
			cin >> elem;
			set += elem;
		}

		return in;
	}

};



