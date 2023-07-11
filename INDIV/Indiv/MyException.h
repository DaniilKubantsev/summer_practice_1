#pragma once

#include <string>
#include <iostream>

using namespace std;

class MyException {
private:
	string error_message;

public:

	MyException(string error_message = "error") {
		this->error_message = error_message;
	}

	string& get_error_message() {
		return error_message;
	}
};